import serial
import time
import xlwt
import numpy
addr  = '/dev/ttyACM0' #bitchy line. Always run /dev to find it.
baud  = 9600

with serial.Serial(addr,baud) as port:
        x = (port.readline())
	    print str(x)[0]
