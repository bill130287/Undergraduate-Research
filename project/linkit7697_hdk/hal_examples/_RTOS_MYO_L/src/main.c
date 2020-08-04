#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "math.h"
#include "hal_i2c_master.h"
#include "hal_gpio.h"
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "sys_init.h"
#include "wifi_api.h"
#include "wifi_lwip_helper.h"
#include "MQTTClient.h"
#include "mqtt.h"
#include "syslog.h"
#include "task_def.h"
#include "hal_gpt.h"
#include "hal_adc.h"

#define WIFI_SSID                ("My ASUS")
#define WIFI_PASSWORD            ("kevin861016")
#define MQTT_SERVER  "192.168.43.154"
#define MQTT_PORT  "1883"
#define MQTT_TOPIC  "MYTOPIC/left"  // left
#define MQTT_CLIENT_ID "7697_left"

//-----------------------------------
#define SLAVE_ADDR2  0x68

TimerHandle_t my_timer;

int timer_callback = 0;
int index = 0;
static int hand_up = 0;
int16_t my_data[6][250] = 0;

//-----------------------------------
void MQTT_output();


log_create_module(mqtt_client_main, PRINT_LEVEL_INFO);

static void hand_up_Arrived(MessageData *md)
{
    MQTTMessage *message = md->message;

    LOG_I(mqtt_tls, "--------on msg: hand up---------");
    hand_up = 1;
}

void vTimerCallback(TimerHandle_t xTimer)
{
    timer_callback = 1;  
}

void set_reg_data(uint8_t reg_addr, uint8_t data)
{
    uint8_t array[2];
    array[0]=reg_addr; //reg_addr
    array[1]=data;     //scale
    hal_i2c_master_send_polling(HAL_I2C_MASTER_0, SLAVE_ADDR2, array, 2 );
}

uint16_t axis_handle(uint8_t reg_addr)
{
    uint8_t r_data[2];
    int16_t combi_data;
    hal_i2c_master_send_polling(HAL_I2C_MASTER_0, SLAVE_ADDR2, &reg_addr, 1 );
    hal_i2c_master_receive_polling(HAL_I2C_MASTER_0, SLAVE_ADDR2,  r_data, 2);
    combi_data=((0xffff & r_data[0])<<8)+r_data[1];
    return combi_data;
}

void I2C_init(void)
{
    //I2C..........................................
    //initialize the pin
    hal_gpio_init(HAL_GPIO_27);//###CLK
    hal_gpio_init(HAL_GPIO_28);//###DATA
    //function mode
    hal_pinmux_set_function(HAL_GPIO_27,HAL_GPIO_27_I2C1_CLK);//###CLK
    hal_pinmux_set_function(HAL_GPIO_28,HAL_GPIO_28_I2C1_DATA);//###DATA
    //initialize the I2C master  
    hal_i2c_config_t i2c_init;                     //###struct
    i2c_init.frequency = HAL_I2C_FREQUENCY_400K;   //###frequency
    hal_i2c_master_init(HAL_I2C_MASTER_0, &i2c_init); //###struct
}

void GetSensor()
{
    int16_t ACC_X, ACC_Y, ACC_Z = 0;
    int16_t GYRO_X, GYRO_Y, GYRO_Z = 0;
    float Gx, Gy, Gz = 0;
    float Ax, Ay, Az = 0;
 
    ACC_X = axis_handle(0x3b);
    ACC_Y = axis_handle(0x3d);
    ACC_Z = axis_handle(0x3f);  
    Ax = ACC_X/2048.0; Ay = ACC_Y/2048.0; Az = ACC_Z/2048.0;
 
    my_data[0][index] = atan(Ax/(sqrt(Ay*Ay+Az*Az)))*5730;
    my_data[1][index] = atan(Ay/(sqrt(Ax*Ax+Az*Az)))*5730;
    my_data[2][index] = atan(Az/(sqrt(Ax*Ax+Ay*Ay)))*5730;
    //----------------------------------
    GYRO_X = axis_handle(0x43);
    GYRO_Y = axis_handle(0x45);
    GYRO_Z = axis_handle(0x47);
    Gx = GYRO_X /(16.4*57.3); Gy = GYRO_Y /(16.4*57.3); Gz = GYRO_Z /(16.4*57.3);

    my_data[3][index] = Gx*100;
    my_data[4][index] = Gy*100;
    my_data[5][index] = Gz*100;
}

void i2c_send(uint8_t addr, uint8_t ctrl, uint8_t data)
{
    uint8_t D[2] = {ctrl, data};
    hal_i2c_master_send_polling(HAL_I2C_MASTER_0, addr, D, 2);
}

void MPU_init()
{
    i2c_send(SLAVE_ADDR2, 0x6B, 0x80);
    hal_gpt_delay_ms(100);
    i2c_send(SLAVE_ADDR2, 0x6B, 0x00);
    i2c_send(SLAVE_ADDR2, 0x19, 0x07);
    i2c_send(SLAVE_ADDR2, 0x1A, 0x06);
    i2c_send(SLAVE_ADDR2, 0x1B, 0x18);
    i2c_send(SLAVE_ADDR2, 0x1C, 0x18);
}
int main(void)
{
    /* Do system initialization, eg: hardware, nvdm, logging and random seed. */
    system_init();
    I2C_init();
    MPU_init();
 
    log_init(NULL, NULL, NULL);
    LOG_I(mqtt_client_main, "FreeRTOS Running");
    LOG_I(mqtt_client_main, "===================");
 
    wifi_config_t config = {0};
    config.opmode = WIFI_MODE_STA_ONLY;
    strcpy((char *)config.sta_config.ssid, WIFI_SSID);
    strcpy((char *)config.sta_config.password, WIFI_PASSWORD);
    config.sta_config.ssid_length = strlen(WIFI_SSID);
    config.sta_config.password_length = strlen(WIFI_PASSWORD);

    wifi_init(&config, NULL);
  
    /* Tcpip stack and net interface initialization,  dhcp client, dhcp server process initialization. */
    lwip_network_init(config.opmode);
    lwip_net_start(config.opmode);
  
    //ADC = xTimerCreate("ADC_Timer", (1/portTICK_RATE_MS) , pdTRUE, 0,vADCTimerCallback);
    my_timer = xTimerCreate("MY_name", (1/portTICK_RATE_MS)*20, pdTRUE, 0, vTimerCallback); //AutoReload
    xTaskCreate(MQTT_output, "MQTT_OUTPUT", 1024, NULL, 1, NULL);
  
    /* Start the scheduler. */
    vTaskStartScheduler();

    for ( ;; );
}

void MQTT_output()
{
    lwip_net_ready();
 
    unsigned char msg_buf[100];     //Buffer for outgoing messages, such as unsubscribe.
    unsigned char msg_readbuf[100]; //Buffer for incoming messages, such as unsubscribe ACK.
    char buf[200];
 
    Network n;  //TCP network 
    Client c;   //MQTT client
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    char *topic = MQTT_TOPIC;
    MQTTMessage message;
 
    NewNetwork(&n);
 
    LOG_I(mqtt_client_main, "Connect to %s:%s\n", MQTT_SERVER, MQTT_PORT);
    ConnectNetwork(&n, MQTT_SERVER, MQTT_PORT);
 
    MQTTClient(&c, &n, 12000, msg_buf, 1000, msg_readbuf, 1000);
 
    data.willFlag = 0;
    data.MQTTVersion = 3;
    data.clientID.cstring = MQTT_CLIENT_ID;
    data.username.cstring = NULL;
    data.password.cstring = NULL;
    data.keepAliveInterval = 60;
    data.cleansession = 1;
    MQTTConnect(&c, &data);
 
    //hand_up------------------------Before subscribing, We should connect in advance.
    char *topic2 = "hand_up";
    MQTTSubscribe(&c, topic2, QOS1, hand_up_Arrived); //when msg come, execute the "hand_up_Arrived"
 
    // QoS 0 data
    int16_t value = 0;//258;
    message.qos = QOS0;
    message.retained = false;
    message.dup = false;

    while(1)
    {
        //wait mqtt hand up
        while(!hand_up) MQTTYield(&c, 10); //@@@ MQTTYield: used to wait data from MQTT. if arrived, exe MsgArrived()!
        hand_up = 0; //clean
        printf("MQTT_hand_up______________\r\n");

  
        //Sensor task-------------------
        while(index!=250)
        {
            xTimerReset(my_timer, 0);
            while(!timer_callback); //wait timer
            timer_callback = 0;
            GetSensor();
            index++;
        }
        index = 0; //clean
  
  
        //WiFi task-------------------
        for(int j=0; j<6; j++)
        {
            for(int i=0; i<10; i++) //divide in 10 part
            {
                message.payload  = (void *)&my_data[j][250/10*i];
                message.payloadlen = 2*(250/10);
                MQTTPublish(&c, topic, &message);
                printf("i: %d   data: %d\n", i, my_data[j][i]);
            }
        }       
    } 
    LOG_I(mqtt_client_main, "============ok");
    while(1);
}