CC = gcc
CFLAGS = -Wall -Werror
OBJECTS = main.c createGrid.c print.c checkWin.c place.c easyBot.c
connect: $(OBJECTS)
	$(CC) $(CFLAGS) -o connect main.c createGrid.c print.c checkWin.c place.c easyBot.c 
