import serial

import time

import locale

import matplotlib.pyplot as plt

import numpy as np

import threading

# XBee setting

serdev = '/dev/ttyUSB0'

s = serial.Serial(serdev, 9600)


s.write("+++".encode())

char = s.read(2)

print("Enter AT mode.")

print(char.decode())


s.write("ATMY 0x140\r\n".encode())

char = s.read(3)

print("Set MY 0x140.")

print(char.decode())


s.write("ATDL 0x240\r\n".encode())

char = s.read(3)

print("Set DL 0x240.")

print(char.decode())


s.write("ATID 0x1\r\n".encode())

char = s.read(3)

print("Set PAN ID 0x1.")

print(char.decode())


s.write("ATWR\r\n".encode())

char = s.read(3)

print("Write config.")

print(char.decode())

s.write('ATWR\r\n'.encode())

char = s.read(3)

print('Write config.')

print(char.decode())


s.write('ATCN\r\n'.encode())

char = s.read(3)

print('Exit AT mode.')

print(char.decode())

print("start sending RPC")

def job(a1,a2):
    while 1:
        line=[]
        time.sleep(1.1)

thread_get = threading.Thread(target = job, args=(line,line1))
thread_get.start()

while True:
    line=s.readline()
    print(line)