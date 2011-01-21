# Echo client program
import socket
import time
import math

HOST = '127.0.0.1'    # The remote host
PORT = 50125              # The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#s.connect((HOST, PORT))
#s.send('Hello, world')
#print s.sendto('Hello, from pythonland', (HOST, PORT))
#data = s.recv(1024)
#s.close()
#print 'Received', repr(data)

x = 0;
while True:
    x += 0.05
    xval = 300 * math.sin(x)
    yval = 300 * math.sin(x)
    zval = math.fabs(300 * math.sin(x))
    output = "x%fy%fz%f" % (xval, yval, zval)
    print "sending: %s", output
    s.sendto(output, (HOST, PORT))
    time.sleep(.04)