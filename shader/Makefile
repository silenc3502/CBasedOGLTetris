PWD = $(shell pwd)

INC_DIRS = -I$(PWD)/../game
INC_DIRS += -I$(PWD)/../view
INC_DIRS += -I$(PWD)/../constants

LIBS = -lm -lGLEW -lGL -lglut -lGLU

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

all: $(OBJS)

.c.o:
	@echo "*********************************"
	@echo "********** GLSL Module **********"
	@echo "*********************************"
#	$(CC) -c $< -o $@ $(INC_DIRS)
	$(CC) -c $< $(INC_DIRS) -g

clean:
	rm -rf *.o