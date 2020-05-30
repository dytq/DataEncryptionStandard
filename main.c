/* Implémentation de DES juste pour le fun de coder ;-) */

/* Bibliothèques */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bloc.h"
#include "interface.h"
#include "cle.h"
#include "feistel.h"
#define NBR_TABLEAUX 14
/* ------------- */

int main(int argc, char ** argv) {
	//~ parsing_terminal(argc,argv);
	int * (*pointeur) = malloc(sizeof(int *) * NBR_TABLEAUX); // liste de pointeurs pour choisir quel tableau on utilise
    init_pointeur(pointeur);
	//bc64 * blocs = convertir_message_64_bits("testtesdtesttest");
	bc64 test = 2;
	bc64 test2 = swap_bloc(test, pointeur[0]);
	printf("\nPermutation initial: %lX\n",test2);
	printf("\nPermutation final: %ld\n",swap_bloc(test2, pointeur[1]));
	//free(blocs);
	free(pointeur);
	exit(EXIT_SUCCESS);
} 