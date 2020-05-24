#ifndef _cle_h
#define _cle_h

#include "bloc.h"
#include <stdlib.h>
#include <stdio.h>

// Bloc pour la clé de 48 bits
typedef struct {
	bc28 gauche;
	bc28 droite;
} bc_cle_s;

//~ void hachage() -> c'est pour la fonction de hachage si j'ai envie de la faire...

/**
 * Fonction de permutation PC1
 * @param la clé de 64 bits
 * @return la fonction de retour
 * */ 
bc_cle_s permutation_initial_cle(bc64 cle);

/**
 * Fonction de permutation PC2 qui genere une clé de 48 bits
 * @param la structure de donnée ou contient la partie gauche et droite shifté
 * @return un bloc de 48 bits pour etre xor avec le texte dans le shéma de feistel
 * */
bc48 genere_cle_48_bits(bc_cle_s B);

#endif // _cle_h
