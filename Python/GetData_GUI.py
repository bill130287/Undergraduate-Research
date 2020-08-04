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
        #self.root_window.config(bg="lightyellow")
        
        # Frame1
        #==================================================================================
        self.Frame1 = tk.Frame(self.root_window, bg="yellow")
        self.Frame1.grid(row=0, column=0)
        
        # Button1
        self.button1 = tk.Button(self.Frame1, text = "用手推擋", width=15, height=2, 
                                 activebackground="steelblue", bg='yellow',
                                 command = self.b1)
        self.button1.grid(row=1, column=0)
        
        # Button2
        self.button2 = tk.Button(self.Frame1, text = "技術犯規", width=15, height=2, 
                                 activebackground="steelblue", bg='lightblue',
                                 command = self.b2)
        self.button2.grid(row=2, column=0)
        
        # Button3
        self.button3 = tk.Button(self.Frame1, text = "兩次運球", width=15, height=2, 
                                 activebackground="steelblue", bg='lightblue',
                                 command = self.b3)
        self.button3.grid(row=3, column=0)
        
        # Button4
        self.button4 = tk.Button(self.Frame1, text = "拉人", width=15, height=2, 
                                 activebackground="steelblue", bg='lightblue',
                                 command = self.b4)
        self.button4.grid(row=4, column=0)
        
        # Button5
        self.button5 = tk.Button(self.Frame1, text = "非法用手", width=15, height=2, 
                                 activebackground="steelblue", bg='lightblue',
                                 command = self.b5)
        self.button5.grid(row=5, column=0)
        
        # Button6
        self.button6 = tk.Button(self.Frame1, text = "非法掩護", width=15, height=2, 
                                 activebackground="steelblue", bg='lightblue',
                                 command = self.b6)
        self.button6.grid(row=6, column=0)
        
        # Button7
        self.button7 = tk.Button(self.Frame1, text = "帶球走步", width=15, height=2, 
                                 activebackground="steelblue", bg='lightblue',
                                 command = self.b7)
        self.button7.grid(row=7, column=0)
        
        # Button8
        self.button8 = tk.Button(self.Frame1, text = "帶球撞人", width=15, height=2, 
                                 activebackground="steelblue", bg='lightblue',
                                 command = self.b8)
        self.button8.grid(row=8, column=0)
        
        # Button9
        self.button9 = tk.Button(self.Frame1, text = "推人或不帶球撞人", width=15, height=2, 
                                 activebackground="steelblue", bg='lightblue',
                                 command = self.b9)
        self.button9.grid(row=9, column=0)
        
        # Button10
        self.button10 = tk.Button(self.Frame1, text = "對手非法接觸", width=15, height=2, 
                                 activebackground="steelblue", bg='lightblue',
                                 command = self.b10)
        self.button10.grid(row=10, column=0)
        

        
        
        #%%
        # Frame2
        #==================================================================================
        self.Frame2 = tk.LabelFrame(self.root_window, text = "Frame2")#, bg="yellow")
        self.Frame2.grid(row=0 , column=1)
        
        # Label1
        self.var_label1 = tk.StringVar()
        self.var_label1.set('Want')   
        self.label1  = tk.Label(self.Frame2, textvariable=self.var_label1, bg='yellow',
                                font=('Arial', 12), width=15, height=2)
        self.label1.grid(row=0, column=0)
        
        # Canvas1
        #------------------------------------------圖1
        self.file1='0.png'
        self.img1 = tk.PhotoImage(file=self.file1)
        #------------------------------------------
        self.canvas1 = tk.Canvas(self.Frame2, bg='black', height=450, width=320)
        self.canvas1.create_image(5, 5, anchor='nw', image=self.img1) #畫布上放圖
        self.canvas1.grid(row=1, column=0)
        
        # Frame3
        #==================================================================================
        self.Frame3 = tk.LabelFrame(self.root_window, text = "Frame3")
        self.Frame3.grid(row=0 , column=2)
        
  # Label2  
        self.label2  = tk.Label(self.Frame3, text='left_hand', #bg='lightblue',
                                font=('Arial', 12), width=10, height=2)
        self.label2.grid(row=0, column=0)
  
        # Canvas2
        #------------------------------------------
        self.canvas2 = tk.Canvas(self.Frame3, bg='azure', width=310, height=50)
        # 填充进度条
        self.fill_line_left = self.canvas2.create_rectangle(0, 10, 7, 40,outline='black',fill="yellow") # 左上 右下
        self.canvas2.grid(row=0, column=1)
       
     # Label_k1 >>> left
        self.var_label_k1 = tk.StringVar()
        self.var_label_k1.set('k_left')   
        self.label_k1  = tk.Label(self.Frame3, textvariable=self.var_label_k1, bg='yellow',
                                font=('Arial', 12), width=10, height=2)
        self.label_k1.grid(row=0, column=2)
  
    # Label3  
        self.label3  = tk.Label(self.Frame3, text='right_hand', #bg='lightblue',
                                font=('Arial', 12), width=10, height=2)
        self.label3.grid(row=1, column=0)
        
        # Label4 
        self.label4  = tk.Label(self.Frame3, text='ing...', bg='lightblue',
                                font=('Arial', 12), width=10, height=2)
        self.label4.grid(row=5, column=1)
        
        # Canvas3
        #------------------------------------------
        self.canvas3 = tk.Canvas(self.Frame3, bg='azure', width=310, height=50)
         # 填充进度条
        self.fill_line_right = self.canvas3.create_rectangle(0, 10, 7, 40,outline='black',fill="gold") # 左上 右下
        self.canvas3.grid(row=1, column=1)
        
        # Label_k2 >>> right
        self.var_label_k2 = tk.StringVar()
        self.var_label_k2.set('k_right')   
        self.label_k2  = tk.Label(self.Frame3, textvariable=self.var_label_k2, bg='yellow',
                                font=('Arial', 12), width=10, height=2)
        self.label_k2.grid(row=1, column=2)
        
        # Button11 >>> close
        self.button11 = tk.Button(self.Frame3, text = "close", width=15, height=2, 
                                 activebackground="steelblue", bg='aqua',
                                 command = close)
        self.button11.grid(row=2, column=2)
        
        # Button12 >>> delete
        self.button12 = tk.Button(self.Frame3, text = "delete", width=15, height=2, 
                                 activebackground="steelblue", bg='lightblue',
                                 command = self.delete)
        self.button12.grid(row=3, column=2)
        
        # Button13 >>> save
        self.button13 = tk.Button(self.Frame3, text = "save", width=15, height=2, 
                                 activebackground="steelblue", bg='lightblue',
                                 command = self.save)
        self.button13.grid(row=4, column=2)
        self.button13.config(state="disabled") # i.e. self.button12['state'] = "disabled"
        
        
        
      
    def rst_button(self):
        self.button1['bg'] = "lightblue"
        self.button2['bg'] = "lightblue"
        self.button3['bg'] = "lightblue"
        self.button4['bg'] = "lightblue"
        self.button5['bg'] = "lightblue"
        self.button6['bg'] = "lightblue"
        self.button7['bg'] = "lightblue"
        self.button8['bg'] = "lightblue"
        self.button9['bg'] = "lightblue"
        self.button10['bg'] = "lightblue"
        
       
        
    def b1(self):
        global label
        label = np.array([0])
        file = "rule圖/"+"0.png"
        self.img1.config(file=file)
        self.rst_button()
        self.button1['bg'] = "yellow"
        self.var_label1.set(rule[0])   
    
    def b2(self):
        global label
        label = np.array([1])
        file = "rule圖/"+"1.png"
        self.img1.config(file=file)
        self.rst_button()
        self.button2['bg'] = "yellow"
        self.var_label1.set(rule[1])  
 
    def b3(self):
        global label
        label = np.array([2])
        file = "rule圖/"+"2.png"
        self.img1.config(file=file)
        self.rst_button()
        self.button3['bg'] = "yellow"
        self.var_label1.set(rule[2])  
    
    def b4(self):
        global label
        label = np.array([3])
        file = "rule圖/"+"3.png"
        self.img1.config(file=file)  
        self.rst_button()
        self.button4['bg'] = "yellow"
        self.var_label1.set(rule[3])  
        
    def b5(self):
        global label
        label = np.array([4])
        file = "rule圖/"+"4.png"
        self.img1.config(file=file)
        self.rst_button()
        self.button5['bg'] = "yellow"
        self.var_label1.set(rule[4])  
    
    def b6(self):
        global label
        label = np.array([5])
        file = "rule圖/"+"5.png"
        self.img1.config(file=file) 
        self.rst_button()
        self.button6['bg'] = "yellow"
        self.var_label1.set(rule[5])  
        
    def b7(self):
        global label
        label = np.array([6])
        file = "rule圖/"+"6.png"
        self.img1.config(file=
