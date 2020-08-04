# 參數
#--------------------
IP = "192.168.43.154"
ID = "P0"


import numpy as np
import tkinter as tk
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
from sklearn.neighbors import KNeighborsClassifier
import itertools 
from tkinter import filedialog
import paho.mqtt.client as mqtt
import time


label = np.array([0])
rule = ["用手推擋","技術犯規","兩次運球","拉人","非法用手","非法掩護","帶球走步","帶球撞人","推人或不帶球撞人","對手非法接觸"]

class Directory():
    def __init__(self, root_window):
        self.root_window = root_window
        self.root_window.title("Directory")
        self.root_window.minsize(800, 600)
        self.root_window.config(bg="whitesmoke")
        
        # Frame1
        #==================================================================================
        self.Frame1 = tk.LabelFrame(self.root_window, bg="whitesmoke")
        self.Frame1.grid(row=0, column=0)
        
  # Label1
        self.var_label1 = tk.StringVar()
        self.var_label1.set('prediction')   
        self.label1  = tk.Label(self.Frame1, textvariable=self.var_label1, bg='yellow',
                                font=('Arial', 12), width=15, height=2)
        self.label1.grid(row=0, column=0)
  
  # Canvas1
        #------------------------------------------圖1
        self.file1='0.png'
        self.img1 = tk.PhotoImage(file=self.file1)
        #------------------------------------------
        self.canvas1 = tk.Canvas(self.Frame1, bg='black', height=450, width=320)
        self.canvas1.create_image(5, 5, anchor='nw', image=self.img1) #畫布上放圖
        self.canvas1.grid(row=1, column=0)
  
  # Frame2
        #==================================================================================
        self.Frame2 = tk.LabelFrame(self.root_window, bg="whitesmoke")
        self.Frame2.grid(row=0 , column=1)
  
        self.rd_var = tk.StringVar()
        self.rd_var.set('B')   
        # radiobutton1
        self.r1 = tk.Radiobutton(self.Frame2, text='原', font=('Arial', 20),
                  variable=self.rd_var, # 變數為var
                  value='A',    # 其值為 A
                  bg='tan'
                  )
        self.r1.grid(row=0, column=3)
        # radiobutton2
        self.r2 = tk.Radiobutton(self.Frame2, text='特徵',font=('Arial', 20),
                  variable=self.rd_var, # 變數為var
                  value='B',    # 其值為 B
                  bg='tan'
                  )
        self.r2.grid(row=0, column=4)
        
  # Label2  
        self.label2  = tk.Label(self.Frame2, text='left_hand', bg='aquamarine',
                                font=('Arial', 12), width=10, height=2)
        self.label2.grid(row=0, column=0)
  
  # Canvas2
        #------------------------------------------
        self.canvas2 = tk.Canvas(self.Frame2, bg='lightcyan', width=310, height=50)
        # 填充进度条
        self.fill_line_left = self.canvas2.create_rectangle(0, 10, 7, 40,outline='black',fill="aquamarine") # 左上 右下
        self.canvas2.grid(row=0, column=1)
        
        # Label_k1 >>> left
        self.var_label_k1 = tk.StringVar()
        self.var_label_k1.set('k_left')   
        self.label_k1  = tk.Label(self.Frame2, textvariable=self.var_label_k1, bg='yellow',
                                font=('Arial', 12), width=10, height=2)
        self.label_k1.grid(row=0, column=2)
  
  
  # Label3  
        self.label3  = tk.Label(self.Frame2, text='right_hand', bg='paleturquoise',
                                font=('Arial', 12), width=10, height=2)
        self.label3.grid(row=1, column=0)
        
  # Label4 
        self.label4  = tk.Label(self.Frame2, text='ing...', bg='lightblue',
                                font=('Arial', 12), width=10, height=2)
        self.label4.grid(row=3, column=2)
       
  # Canvas3
        #------------------------------------------
        self.canvas3 = tk.Canvas(self.Frame2, bg='azure', width=310, height=50)
        # 填充进度条
        self.fill_line_right = self.canvas3.create_rectangle(0, 10, 7, 40,outline='black',fill="paleturquoise") # 左上 右下
        self.canvas3.grid(row=1, column=1)
  
        # Label_k2 >>> right
        self.var_label_k2 = tk.StringVar()
        self.var_label_k2.set('k_right')   
        self.label_k2  = tk.Label(self.Frame2, textvariable=self.var_label_k2, bg='yellow',
                                font=('Arial', 12), width=10, height=2)
        self.label_k2.grid(row=1, column=2)
  
        
  # Button1 >>> close
        self.button1 = tk.Button(self.Frame2, text = "close", width=15, height=2, 
                                 activebackground="cornflowerblue", bg='lightskyblue',
                                 command = close)
        self.button1.grid(row=2, column=3)
  
#%%
def MAV(data):
    data = np.mean(data, axis=1)
    data = np.expand_dims(data, axis=1) #增維度
    return data
    
def ZC(data): # 跨過零()
    row = len(data[:,0])
    column = len(data[0,:-1]) # 因兩兩個比較，所以-1(去尾)
    tmp = np.full((row,1), 0, dtype=np.float64)
    for r in range(row):
        for c in range(column):
            if data[r,c]>=0 and data[r,c+1]<=0: #下降
                tmp[r,0] = tmp[r,0]+1
    return tmp
    
def SSC(data): # 有極大值
    row = len(data[:,0])
    column = len(data[0,:-2]) # 因三個比較，所以-2(去頭尾 )
    tmp = np.full((row,1), 0, dtype=np.float64)
    for r in range(row):
        for c in range(column):
            c += 1 # 把頭加回來
            if data[r,c]-data[r,c-1]>0 and data[r,c]-data[r,c+1]>0: # 極大值
                tmp[r,0] = tmp[r,0]+1
    return tmp

def WL(data): # 累積振幅變化
    row = len(data[:,0])
    column = len(data[0,:-1]) # 因兩兩個比較，所以-1(去尾)
    tmp = np.full((row,1), 0, dtype=np.float64)
    for r in range(row):
        for c in range(column):
            tmp[r,0] = tmp[r,0]+abs(data[r,c+1]-data[r,c])
    return tmp

def RMS(data):
    tmp = np.sqrt(np.mean(data**2,axis=1))
    tmp = np.expand_dims(tmp, axis=1) #增維度
    return tmp

def overlap_feature(data):
    column = len(data[0,:])
    window = 250 # 250ms
    slide = 62   # 62ms
    i=0
    while i*slide+window < column:
        index = i*slide
        x = data[:, index:index+window]
        mav = MAV(x)
        zc  = ZC(x)
        ssc = SSC(x)
        wl  = WL(x)
        rms = RMS(x)
        if i==0:
            table_mav = mav
            table_zc  = zc
            table_ssc = ssc
            table_wl  = wl
            table_rms = rms
        else:
            table_mav = np.concatenate((table_mav, mav),axis=1)
            table_zc  = np.concatenate((table_zc,   zc),axis=1)
            table_ssc = np.concatenate((table_ssc, ssc),axis=1)
            table_wl  = np.concatenate((table_wl,   wl),axis=1)
            table_rms = np.concatenate((table_rms, rms),axis=1)
        i +=1
    return table_mav, table_zc, table_ssc, table_wl, table_rms 
#%%
        
k_left = 0
k_right = 0
array_left = np.array([808])
array_right = np.array([808])
payloads_left  = bytearray()
payloads_right = bytearray()

#%%
# MQTT

def close():
    client.loop_stop() # 終止thread (一定要有)
    D.root_window.destroy()
        
def on_connect(client, userdata, flags, rc):
    print("MQTT connected!!")
    client.subscribe("MYTOPIC/left")
    client.subscribe("MYTOPIC/right") 
    client.subscribe("hand_up")

def on_message(client, userdata, msg):
    global k_left
    global k_right
    global array_left
    global array_right
    global payloads_left
    global payloads_right
    #print(msg.topic+" "+str(msg.payload))
    
    
    if msg.topic=="hand_up":
        print("............................")
        D.label4.config(bg="red")
    
    else:
        # left
        #--------------------
        if msg.topic=="MYTOPIC/left":
            print("=================================================Left...",k_left)
            buf = msg.payload
            payloads_left.extend(buf)
            k_left += 1
            x = 60 # 未知变量，可更改
            n = 300 / x  # 300是矩形填充满的次数
            n = n + (300 / x)*k_left
            D.canvas2.coords(D.fill_line_left, (0, 10, n, 40))
            D.var_label_k1.set(k_left)   
            D.root_window.update()
        
        # Right
        #--------------------
        elif msg.topic=="MYTOPIC/right":
            print("-------------------------------------------------Right...",k_right)
            buf = msg.payload
            payloads_right.extend(buf)
            k_right += 1
            x = 60 # 未知变量，可更改
            n = 300 / x  # 300是矩形填充满的次数
            n = n + (300 / x)*k_right
            D.canvas3.coords(D.fill_line_right, (0, 10, n, 40))
            D.var_label_k2.set(k_right) 
            D.root_window.update()
        else:
         print("ERROR")
        
        # 是否收完60筆
        #----------------------
        if k_left<60 or k_right<60:
            print("dataTR...")
        else: #k_left>=60 && k_right>=60
            k_left = 0
            k_right = 0
            D.label4.config(bg="lightblue") # 傳輸完成: 改回原色
            
            # Left >> payloads轉np.array
            #------------------------
            data = payloads_left
            payloads_left = bytearray() # clear payloads_left
            n = len(data)/2
            for i in range(int(n)):
                a_byte = data[i*2:i*2+2]
                a_int = int.from_bytes(a_byte, byteorder="little",signed="True")
                if i==0:
                    array_left = np.array([a_int])
                else:
                    array_left = np.append(array_left, a_int)
            array_left = array_left/100.
            print('array_left.shape: ',array_left.shape)
        
            # Right >> payloads轉np.array
            #------------------------
            data = payloads_right
            payloads_right = bytearray() # clear payloads_left
            n = len(data)/2
            for i in range(int(n)):
                a_byte = data[i*2:i*2+2]
                a_int = int.from_bytes(a_byte, byteorder="little",signed="True")
                if i==0:
                    array_right = np.array([a_int])
                else:
