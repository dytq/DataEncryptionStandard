#ShortCut
CFLAGS = -g -Wall -c
OBJ = $(wildcard *.o)

all:out

# Edition de lien du programme principal
out: main.o
	gcc -o $@ $^ ${LFLAGS}

# Compilation du programme principal
main.o: main.c
	gcc ${CFLAGS} $*.c

# Compilation des différents.o


# Monsieur Propre
clean:
	@rm *.o; rm out
	@echo suppression de ${OBJ} et out
