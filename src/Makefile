.PHONY: all clean

CC=gcc
INCLUDES=-I.
CFLAGS=-std=c99
LIBS=-lraylib -lm -lpthread
MAKE=make
PROJECT_NAME=testinput
ODIR=obj
PLATFORM ?= PLATFORM_DESKTOP

SOURCE_FILES ?= \
	evtinput.c \
	main.c

OBJS = $(patsubst %.c, %.o, $(SOURCE_FILES))

ifeq ($(PLATFORM), PLATFORM_RPI)
	LIBS += -lbrcmGLESv2 -lbrcmEGL -lrt -lbcm_host -ldl -latomic
	INCLUDES+= -I/opt/vc/include -I/opt/vc/include/interface/vmcs_host/linux -I/opt/vc/include/interface/vcos/pthreads -I/usr/local/include -L. -L/home/pi/raylib/src -L/home/pi/raylib/src -L/usr/local/lib -L/opt/vc/lib
endif

all: 
	$(MAKE) $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJS)
	$(CC) -o $(PROJECT_NAME) $(OBJS) $(CFLAGS) $(INCLUDES) $(LIBS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES) $(LIBS)

clean:
	find . -type f -executable -delete
	rm -fv *.o