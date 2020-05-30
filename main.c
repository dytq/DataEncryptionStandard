/* Implémentation de DES juste pour le fun de coder ;-) */

/* Bibliothèques */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bloc.h"
#include "interface.h"
#include "cle.h"
#include "feistel.h"

/* ------------- */

int main(int argc, char ** argv) {
	//parsing_terminal(argc,argv);
	chiffrement("testtest","test");
	exit(EXIT_SUCCESS);
} 