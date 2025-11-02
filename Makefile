CC = gcc
CFLAGS = -Wall -Werror
OBJECTS = main.c createGrid.c print.c checkWin.c place.c easyBot.c mediumBot.c
connect: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(OBJECTS) 
