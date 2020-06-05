#ifndef _feistel_h
#define _feistel_h

#include "bloc.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Fonction de F Feistel pour chiffré une moitié
 * @param la moitié d'un bloc qu'il faut développer avant
 * @param la sous clé de 64 bits
 * @return un bloc de 32 bits
 * */
bc32 feistel(bc32 moitie_bloc, bc48 sous_cle, int ** pointeur);

/**
 * thread pour un bloc s (qu'on peut paralleliser)
 * @param s le blocs de 6 bits d'entrée
 * @param le pointeur vers la S boite correspondante
 * @return la blocs de 4 bits de retour
 * */
bc4 thread_fonction_s(bc6 s,int * pointeur);

/**
 * Permet d'appliquer la fonction S 
 * @param un bloc de 48 bits 
 * @return le bloc de 32 bits
 * */
bc32 fonctionS(bc48 text, int ** pointeur);

#endif // _feistel_h
