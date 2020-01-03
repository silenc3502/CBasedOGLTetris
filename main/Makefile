PWD = $(shell pwd)

INC_DIRS = -I$(PWD)/../game
INC_DIRS += -I$(PWD)/../presenter
INC_DIRS += -I$(PWD)/../view
INC_DIRS += -I$(PWD)/../constants
INC_DIRS += -I$(PWD)/../math
INC_DIRS += -I$(PWD)/../shader

LIBS = -lm -lGLEW -lGL -lglut -lGLU

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

GAME_DIR = $(PWD)/../game
GAME_OBJS = $(shell find $(GAME_DIR) -name '*.o')

VIEW_DIR = $(PWD)/../view
VIEW_OBJS = $(shell find $(VIEW_DIR) -name '*.o')

MATH_DIR = $(PWD)/../math
MATH_OBJS = $(shell find $(MATH_DIR) -name '*.o')

SHADER_DIR = $(PWD)/../shader
SHADER_OBJS = $(shell find $(SHADER_DIR) -name '*.o')

TARGET = main

#all: $(OBJS)
all: $(TARGET)

#$(TARGET): $(OBJS)
main: main.o
	$(CC) -o $@ $< $(MATH_OBJS) $(SHADER_OBJS) $(GAME_OBJS) $(VIEW_OBJS) $(LIBS)

.c.o:
	@echo "**********************************"
	@echo "********** Main Program **********"
	@echo "**********************************"
	$(CC) -c $< -o $@ $(INC_DIRS)

clean:
	rm -rf *.o
	rm -rf $(TARGET)