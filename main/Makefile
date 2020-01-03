PWD = $(shell pwd)

INC_DIRS = -I$(PWD)/../game
INC_DIRS += -I$(PWD)/../presenter
INC_DIRS += -I$(PWD)/../view
INC_DIRS += -I$(PWD)/../constants

LIBS = -lm -lGL -lglut -lGLU

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

GAME_DIR = $(PWD)/../game
GAME_OBJS = $(shell find $(GAME_DIR) -name '*.o')

VIEW_DIR = $(PWD)/../view
VIEW_OBJS = $(shell find $(VIEW_DIR) -name '*.o')

TARGET = main

#all: $(OBJS)
all: $(TARGET)

#$(TARGET): $(OBJS)
main: main.o
	$(CC) -o $@ $< $(GAME_OBJS) $(VIEW_OBJS) $(LIBS)

.c.o:
	@echo "**********************************"
	@echo "********** Main Program **********"
	@echo "**********************************"
	@echo $(GAME_OBJS)
	$(CC) -c $< -o $@ $(INC_DIRS)

clean:
	rm -rf *.o
	rm -rf $(TARGET)