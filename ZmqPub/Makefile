OSTYPE := $(shell uname -s)

BIN_DIR = ./Bin

INC_DIRS = /usr/include/ni

SRC_FILES = *.cpp *.c

EXE_NAME = ZMQPub

ifeq ("$(OSTYPE)","Darwin")
	LDFLAGS += -framework OpenGL -framework GLUT -framework ApplicationServices
else
	USED_LIBS += glut
endif

USED_LIBS += OpenNI zmq

LIB_DIRS += /usr/lib
#LIB_DIRS += /usr/local/lib
LIB_DIRS += /usr/local/Cellar/zeromq/2.0.10/lib
include ./CommonMakefile
