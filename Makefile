#Simple Makefile de compilation en C

#Variables
CFLAGS = -g -Wall -c
OBJ = $(wildcard *.o)
GCH = $(wildcard *.h.gch)

all:des.out

# run 
run:des.out
	./des.out

# Edition de lien du programme principal
des.out: main.o feistel.o interface.o cle.o feistel.o bloc.o
	gcc -o $@ $^ ${LFLAGS}

# Compilation du programme principal
main.o: main.c bloc.h interface.h cle.h feistel.h 
	gcc ${CFLAGS} $*.c

# Compilation des différents .o
bloc.o:bloc.c bloc.h
	gcc ${CFLAGS} $*.c

interface.o: interface.c interface.h bloc.h
	gcc ${CFLAGS} $*.c

cle.o: cle.c *.h
	gcc ${CFLAGS} $*.c cle.h bloc.h

feistel.o: feistel.c feistel.h bloc.h
	gcc ${CFLAGS} $*.c

# Monsieur Propre
clean:
	@rm *.o; rm des.out; rm *.h.gch
	@echo Suppression de:
	@echo _ ${OBJ}
	@echo _ ${GCH}
	@echo _ des.out
	@echo On dit merci à Monsieur Propre !! 
