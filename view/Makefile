PWD = $(shell pwd)

INC_DIRS = -I$(PWD)/../game
INC_DIRS += -I$(PWD)/../view

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

all: $(OBJS)

.c.o:
	@echo "*********************************"
	@echo "********** Game Module **********"
	@echo "*********************************"
	$(CC) -c $< -o $@ $(INC_DIRS)

clean:
	rm -rf *.o