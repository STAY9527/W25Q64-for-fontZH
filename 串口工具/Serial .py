import serial
import time

#运行此文件前最好先将W25Q64芯片里存放数据的位置清空。可以用项目里W25Q64.c里的w25q64_Erase_Chip()函数将整块芯片擦除。

ser = serial.Serial("COM5", 115200)    # 打开COM5，将波特率配置为115200，其余参数使用默认值，使用前需要把COM5修改为实际串口
if ser.isOpen():                        # 判断串口是否成功打开
    print("打开串口成功。")
    with open("fontZH.txt", "r", encoding="utf-8") as f:    #存放的字库，可通过fontZH.h文件对照，每36个16进制数代表一个汉字字模，大小位16*16
        text = f.read()
    text = list(text.split(','))
    num=[]
    for i in text:
        num.append(int(i.strip(),16))
    a=[0,0]                               # 列表a里面存放的是每256个字节在W25Q64中存放的起始地址的地址
    for i in range(0,len(num)-12,256):  

        font=a+num[i:i+256]                 # 由于W25Q64一次只能写入256个字节，所以要将字库数据拆成多个256字节分批次写入
        write_len = ser.write(bytes(font))  
        print(font)
        time.sleep(1)
        a[1]+=1
        if a[1]==256:                       #串口通信每次发送8位数据，a[1]每统计255次后置为0，a[0]加1
            a[0]+=1
            a[1]=0
            
    ser.close()
else:
    print("打开串口失败。")
