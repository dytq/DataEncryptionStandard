#ifndef _feistel_h
#define _feistel_h

#include "bloc.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Fonction de F Feistel pour chiffré une moitié
 * @param la moitié d'un bloc
 * @param la sous clé de 64 bits
 * @return un bloc de 32 bits
 * */
bc32 feistel(bc32 moitie_bloc, bc48 sous_cle);

/**
 * Fonction d'expansion 
 * @param la moitié d'un bloc
 * @return le bloc de 48 bits pour pouvoir le xor avec une clé généré
 * */
bc48 expansion(bc32 moitie_bloc);

/**
 * Permet d'appliquer la fonction S (si possible après de paralléliser mais il faut utiliser une structure de donnée)
 * @param un bloc de 48 bits 
 * @return le bloc de 32 bits
 * */
bc32 fonctionS(bc48 text);

/**
 * Permuation final de la fonction F du shéma de feistel
 * @param un bloc de 32 bits
 * @return le bloc de 32 bits après permutation
 * */
bc32 permutation(bc32 text);

#endif // _feistel_h
