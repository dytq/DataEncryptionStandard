#ShortCut
CFLAGS = -g -Wall -c
OBJ = $(wildcard *.o)

all:app.out

# Edition de lien du programme principal
app.out: main.o
	gcc -o $@ $^ ${LFLAGS}

# Compilation du programme principal
main.o: main.c
	gcc ${CFLAGS} $*.c

# Compilation des différents.o


# Monsieur Propre
clean:
	@rm *.o; rm app.out
	@echo suppression de ${OBJ} et app.out
