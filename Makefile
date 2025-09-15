CC		= gcc
CFLAGS	= -g -o
SRC		= *.c
TARGET	= siShell

$(TARGET):
	$(CC) $(SRC) $(CFLAGS) $(TARGET)

clean:
	rm $(TARGET)
