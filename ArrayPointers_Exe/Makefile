
TARGET = ArrayPointers_Exe.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = main.o exercise.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c exercise.h
	$(CC) $(CFLAGS) -c main.c

exercise.o: exercise.c exercise.h
	$(CC) $(CFLAGS) -c exercise.c

clean: 
	rm -f $(TARGET) $(OBJS) 