PWD = $(shell pwd)

INC_DIRS = -I$(PWD)/../presenter
INC_DIRS += -I$(PWD)/../view
INC_DIRS += -I$(PWD)/../game

LIBS = -lm -lGL -lglut -lGLU

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

all: $(OBJS)

.c.o:
	@echo "*********************************"
	@echo "********** Game Module **********"
	@echo "*********************************"
	$(CC) -c $< -o $@ $(INC_DIRS) $(LIBS)

clean:
	rm -rf *.o