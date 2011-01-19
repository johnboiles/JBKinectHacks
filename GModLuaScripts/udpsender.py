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
    x += 0.1
    xval = 10 * math.sin(x)
    print "sending x = ", xval
    s.sendto(str(xval), (HOST, PORT))
    time.sleep(.04)