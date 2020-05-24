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

/* Structures de données */

// Pour chiffrer/dechiffrer un bloc de 64 bits
typedef struct {
	bc32 gauche;
	bc32 droite;
} bc_text_s;

/* --------------------- */

/* Les Différentes Matrice utilisé */

// Matrice de Permutation
int IP[64] = {
	58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,
	64,56,48,40,32,24,16,8,
	57,49,41,33,25,17,9 ,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7
};

/* ------------------------------- */

// convertit un message en liste de 64 bits
bc64 * convertir_message_64_bits(char * message) {
	return NULL;
}

// permutation initial
bc64 permutation_initial(bc64 text) {
	return 0;
}

// permutation final
bc64 permutation_final(bc64 text) {
	return 0;
}

// permet de chiffrer un message
void chiffrement(char * message, char * cle) {
	
}

//permet de dechiffrer un message
void dechiffrement(char * message, char * cle) {
	
} 

int main(int argc, char ** argv) {
	//~ parsing_terminal(argc,argv);
	
	exit(EXIT_SUCCESS);
} 
