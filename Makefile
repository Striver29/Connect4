CC = gcc
CFLAGS = -Wall -Werror
SOURCES = main.c createGrid.c print.c checkWin.c place.c easyBot.c mediumBot.c hardBot.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = connect

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)