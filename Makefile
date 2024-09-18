CC = gcc
CFLAGS = -g
RM = rm -f

SRCS = main.c
OBJS = $(SRCS:.c=.o)

TARGET = a4

# default: all

all: a4

a4: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	$(RM) $(TARGET) $(OBJS)