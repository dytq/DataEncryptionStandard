#ifndef _cle_h
#define _cle_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bloc.h"
#include "interface.h"

/* Bloc de clé de 56 bits composé de 28 bits pour gauche et droite */ 
typedef struct {
	bc28 gauche;
	bc28 droite;
} bc_cle_s;

/**
 * Permet d'initialiser une paire de clé
 * @param le mot de passe entré par l'utilisateur < 64 bits
 * @param la cle à retourner
 * @param le pointeur vers les tableaux de swapping
 * */
void init_cles(char * mot_de_passe, bc_cle_s * B, int ** pointeur);

/**
 * Permet d'effectuer la première permutation PC-1 pour transformé un 64 bits en 56 bits
 * @param la cle de 64 bits
 * @param le pointeur vers les tableaux de swapping
 * @return la clé de 56 bits
 * */
bc_cle_s permutation_initial_cle(bc64 cle, int ** pointeur);

/**
 * Permet de generer une clé de 48 bits
 * @param la cle des deux branches de 32 bits
 * @param le pointeur vers le tableaux de swapping PC-2
 * @return une clée de 48 bits a xor(er) message
 * */ 
bc48 genere_cle_48_bits(bc_cle_s * B,int * pointeur);

#endif // _cle_h
