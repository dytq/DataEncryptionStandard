#ifndef _interface_h
#define _interface_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bloc.h"

/**
 * Permet d'afficher l'aide sur le terminal
 * */
void afficher_aide();

/**
 * Permet de quitter l'application en cas d'erreur de données entré par l'utilisateur
 * */
void error_parsing_terminal_entry();

/**
 * Permet de parser les données entrée par l'utilisateur
 * */
void parsing_terminal(int argc, char ** argv);

/**
 * convertit un message de 64 bits en bloc de 64 bits
 * @param message
 * @return une liste de blocs
 * */
bc64 * convertir_message_64_bits(char * message);

/**
 * Permutation initial du bloc de 64 bits
 * @param le texte
 * @return le texte permuté
 * */
bc64 permutation_initial(bc64 text);
/**
 * Permutation inverse
 * @param le texte
 * @return le texte permuté de l'autre sens
 * */
bc64 permutation_final(bc64 text);

/**
 * chiffrement
 * @param le message à chiffrer
 * @param la clé
 * */
void chiffrement(char * message, char * cle);

/**
 * dechiffrement
 * @param l'inverse de chiffrement
 * @param cle
 * */ 
void dechiffrement(char * message, char * cle);

#endif //_interface_h
