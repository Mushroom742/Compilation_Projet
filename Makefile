CC=gcc
CFLAGS=-Wall
EXEC=main

all: $(EXEC)

main: main.o automate_non_deterministe.o automate_deterministe.o
		$(CC) -o main main.o automate_non_deterministe.o automate_deterministe.o
		
main.o: main.c automate_non_deterministe.h automate_deterministe.h
		$(CC) -o main.o -c main.c $(CFLAGS)
		
automate_non_deterministe.o: automate_non_deterministe.c automate_non_deterministe.h automate_deterministe.h
		$(CC) -o automate_non_deterministe.o -c automate_non_deterministe.c $(CFLAGS)
		
automate_deterministe.o: automate_deterministe.c automate_non_deterministe.h automate_deterministe.h
		$(CC) -o automate_deterministe.o -c automate_deterministe.c $(CFLAGS)
		
clean:
		rm -rf *.o
