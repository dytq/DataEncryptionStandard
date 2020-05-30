#ifndef _bloc_h
#define _bloc_h

#include <stdio.h>
#include <stdlib.h>

/* Redéfinition de types pour les opérations binaires */ 
typedef unsigned long int bc64;
typedef unsigned long int bc56;
typedef unsigned long int bc48;
typedef unsigned int bc32;
typedef unsigned int bc28;
typedef unsigned char bc6;
typedef unsigned char bc4;

/**
 * Fonction qui permet de faire des swap selon l'id du tableau à swaper souhaité
 * @param test a swaper (64,48,32,28)
 * @param le pointeur des tableaux
 * @return le texte swaper
 * */
bc64 swap_bloc_64(bc64 text, int * pointeur);
bc64 swap_bloc_48(bc48 text, int * pointeur);
bc64 swap_bloc_32(bc32 text, int * pointeur);
bc64 swap_bloc_28(bc28 text, int * pointeur);

/**
 * Fonction qui init le poiteur des tableaux
 * @param le pointeur qui va pointé sur chaque tableau statique
 * */
void init_pointeur(int ** pointeur);

#endif 