OSTYPE := $(shell uname -s)

BIN_DIR = ../Bin

INC_DIRS = /usr/include/ni ../Common

SRC_FILES = *.cpp *.c ../Common/*.cpp ../Common/*.c

EXE_NAME = GModBackend

ifeq ("$(OSTYPE)","Darwin")
	LDFLAGS += -framework OpenGL -framework GLUT
else
	USED_LIBS += glut
endif

USED_LIBS += OpenNI

LIB_DIRS += /usr/lib
include ../Common/OpenNICommonMakefile

