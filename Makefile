# try to do some autodetecting
UNAME := $(shell uname -s)

ifeq "$(UNAME)" "Darwin"
	OS=macosx
endif
ifeq "$(OS)" "Windows_NT"
	OS=windows
endif
ifeq "$(UNAME)" "Linux"
	OS=linux
endif

ifeq "$(OS)" "linux"

CC=g++
CFLAGS += -DLINUX

endif
#################  Mac OS X  ##################################################
ifeq "$(OS)" "macosx"

EXE_SUFFIX=

#ARCHS=    -arch x86_64
CFLAGS+= $(ARCHS) -DMACOSX #-DSERIALPORTDEBUG
CFLAGS += -mmacosx-version-min=10.6
CFLAGS_MONGOOSE=  -I./mongoose -pthread -g 
LIBS+=	 $(ARCHS)
CC=g++

endif

#################  Windows  ##################################################
ifeq "$(OS)" "windows"

EXE_SUFFIX=.exe

CFLAGS_MONGOOSE = -I./mongoose -mthreads

endif


#################  Common  ##################################################

CFLAGS += $(INCLUDES) -O -Wall 


all: arduino-serial linux-serial

arduino-serial: arduino-serial.o arduino-serial-lib.o
	$(CC) $(CFLAGS) -o arduino-serial$(EXE_SUFFIX) arduino-serial.o arduino-serial-lib.o $(LIBS)

arduino-serial-server: arduino-serial-lib.o
	$(CC) $(CFLAGS) $(CFLAGS_MONGOOSE) -o arduino-serial-server$(EXE_SUFFIX) arduino-serial-server.c  arduino-serial-lib.o mongoose/mongoose.c $(LIBS)

linux-serial: linux-serial.o arduino-serial-lib.o linux-serial.h linux-serial.c
	$(CC) $(CFLAGS) -o linux-serial$(EXE_SUFFIX) linux-serial.o arduino-serial-lib.o $(LIBS)




.c.o:
	$(CC) $(CFLAGS) -c $*.c -o $*.o


clean:
	rm -f $(OBJ) arduino-serial arduino-serial.exe *.o *.a
	rm -f $(OBJ) arduino-serial-server arduino-serial-server.exe *.o *.a
	rm -f linux-serial
	rm -f mongoose/mongoose.o

