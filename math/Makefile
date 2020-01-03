PWD = $(shell pwd)

INC_DIRS = -I$(PWD)/../presenter
INC_DIRS += -I$(PWD)/../view
INC_DIRS += -I$(PWD)/../game

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

all: $(OBJS)

.c.o:
	@echo "*********************************"
	@echo "********** Math Module **********"
	@echo "*********************************"
#	$(CC) -c $< -o $@ $(INC_DIRS)
	$(CC) -c $< $(INC_DIRS)

clean:
	rm -rf *.o