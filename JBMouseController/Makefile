OSTYPE := $(shell uname -s)

BIN_DIR = ./Bin

INC_DIRS = /usr/include/ni

SRC_FILES = *.cpp *.c

EXE_NAME = JBMouseController

ifeq ("$(OSTYPE)","Darwin")
	LDFLAGS += -framework OpenGL -framework GLUT -framework ApplicationServices
else
	USED_LIBS += glut
endif

USED_LIBS += OpenNI

LIB_DIRS += /usr/lib
include ./CommonMakefile
