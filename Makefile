CC		= gcc
CFLAGS	= -g -o
SRC		= src/*.c
TARGET	= siShell

$(TARGET):
	$(CC) $(SRC) $(CFLAGS) $(TARGET)

clean:
	rm $(TARGET)
