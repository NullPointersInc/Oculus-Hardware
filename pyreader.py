import serial
import time
import xlwt
import numpy
import paho.mqtt.client as mqtt
addr  = '/dev/ttyACM0' #bitchy line. Always run /dev to find it.
baud  = 9600
x = 'z'
brokerAddress = "192.168.0.5"
port = 1883

def mqttPub(msg):
        CLIENT = mqtt.Client("RPi")
        CLIENT.connect(brokerAddress)
        CLIENT.loop_start()
        CLIENT.publish("oculus", msg)
        time.sleep(5)
        CLIENT.loop_stop()

def looper(i):
    if i == '1':
        mqttPub("object")
    if i == '2':
        mqttPub("money")
    if i == '3':
        mqttPub("faces")
    if i == '4':
        mqttPub("light1")
    if i == '5':
        mqttPub("light2")
    if i == '6':
        mqttPub("kitchen")
    if i == '7':
        mqttPub("security")
    if i == '8':
        mqttPub("maa ****")

while x != '#':
    with serial.Serial(addr,baud) as port:
        temp = (port.readline())
        x = str(temp)[0]
        print(x)
        looper(x)
