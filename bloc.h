#ifndef _bloc_h
#define _bloc_h
/* le nombre de tableaux */
#define NBR_TABLEAUX 14

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
 * @param text a swaper 
 * @param le pointeur des tableaux a swap
 * @return le texte swaper selon le format
 * */
bc64 swap_bloc_64(bc64 text, int * pointeur);
bc64 swap_bloc_48(bc48 text, int * pointeur);
bc32 swap_bloc_32(bc32 text, int * pointeur);
bc48 swap_bloc_32_to_48(bc32 text, int * pointeur);
bc56 swap_bloc_64_to_56(bc64 text, int * pointeur);
bc48 swap_bloc_56_to_48(bc56 text, int * pointeur);

/**
 * Fonction qui init le pointeur des tableaux
 * @param le pointeur qui va pointé sur chaque tableau statique
 * */
void init_pointeur(int ** pointeur);

/**
 * Fonction qui inverse le sens d'un binaire
 * @param le binaire à inverser
 * @return le binaire inverser
 * */
bc64 reverse_64_bits(bc64 valeur);
bc56 reverse_56_bits(bc64 valeur);
bc56 reverse_48_bits(bc64 valeur);
bc32 reverse_32_bits(bc32 valeur);

#endif 