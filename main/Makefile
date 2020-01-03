PWD = $(shell pwd)

INC_DIRS = -I$(PWD)/../game
INC_DIRS += -I$(PWD)/../presenter
INC_DIRS += -I$(PWD)/../view

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

TARGET = main

#all: $(OBJS)
all: $(TARGET)

$(TARGET): $(OBJS)

.c.o:
	@echo "**********************************"
	@echo "********** Main Program **********"
	@echo "**********************************"
	$(CC) -c $< -o $@ $(INC_DIRS)

clean:
	rm -rf *.o