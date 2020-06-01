#ifndef _cle_h
#define _cle_h

#include "bloc.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>

// Bloc pour la clé de 48 bits
typedef struct {
	bc28 gauche;
	bc28 droite;
} bc_cle_s;

//~ void hachage() -> c'est pour la fonction de hachage si j'ai envie de la faire...

void init_cles(char * mot_de_passe, bc_cle_s * B, int ** pointeur);

bc_cle_s permutation_initial_cle(bc64 cle, int ** pointeur);

bc48 genere_cle_48_bits(bc_cle_s * B,int * pointeur);

#endif // _cle_h
