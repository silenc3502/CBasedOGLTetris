PWD = $(shell pwd)

INC_DIRS = -I$(PWD)/../presenter
INC_DIRS += -I$(PWD)/../view
INC_DIRS += -I$(PWD)/../game
INC_DIRS += -I$(PWD)/../constants
INC_DIRS += -I$(PWD)/../math
INC_DIRS += -I$(PWD)/../shader

LIBS = -lm -lGLEW -lGL -lglut -lGLU

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

all: $(OBJS)

.c.o:
	@echo "*********************************"
	@echo "********** Game Module **********"
	@echo "*********************************"
#	$(CC) -c $< -o $@ $(INC_DIRS) $(LIBS)
	$(CC) -c $< $(INC_DIRS) $(LIBS) -g

clean:
	rm -rf *.o