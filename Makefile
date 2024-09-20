CC = gcc
CFLAGS = -g
RM = rm -f
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

SRCS = main.c
OBJS = $(SRCS:.c=.o)

TARGET = a4

# default: all
testmemory: $(TARGET)
	$(VAL) ./$(TARGET)

all: a4

a4: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	$(RM) $(TARGET) $(OBJS) memcheck.txt