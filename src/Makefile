CC = cc -std=c99
WFLAGS = -Wall -Wextra
LDFLAGS =

all : scrabble

scrabble : scrabble.o plateau.o placer_mot.o dico.o recherche_mot_dico.o points.o tirage.o 
	$(CC) -o scrabble scrabble.o plateau.o placer_mot.o dico.o recherche_mot_dico.o points.o tirage.o $(WFLAGS)

scrabble.o : scrabble.c scrabble.h
	$(CC) -o scrabble.o -c scrabble.c $(WFLAGS)

plateau.o : plateau.c scrabble.h 
	$(CC) -o plateau.o -c plateau.c $(WFLAGS)

placer_mot.o : placer_mot.c scrabble.h 
	$(CC) -o placer_mot.o -c placer_mot.c $(WFLAGS)

dico.o : dico.c scrabble.h 
	$(CC) -o dico.o -c dico.c $(WFLAGS)

recherche_mot_dico.o : recherche_mot_dico.c scrabble.h
	$(CC) -o recherche_mot_dico.o -c recherche_mot_dico.c $(WFLAGS)

points.o : points.c scrabble.h
	$(CC) -o points.o -c points.c $(WFLAGS)

tirage.o : tirage.c scrabble.h
	$(CC) -o tirage.o -c tirage.c $(WFLAGS)

clean: 
	rm -f *.o

supraclean: 
	rm scrabble