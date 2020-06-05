#ifndef _interface_h
#define _interface_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bloc.h"
#include "feistel.h"
#include "cle.h"

/* structure de donnée pour un blocs de message */
typedef struct {
    bc32 gauche;
    bc32 droite;
} bc_text_s;

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
 * @return une liste de blocs en hexa
 * */
bc64 * convertir_message_64_bits(char * message, int taille_message, int nbr_bloc);

/**
 * convertit un hexa en blocs de 64bits 
 * @param le message a convertir
 * @param le nombre de bloc a former
 * @return la liste de blocs en hexa
 * */
bc64 * convertir_message_en_hexa_64_bits(char * message, int nbr_bloc);
/**
 * chiffrement
 * @param le message à chiffrer
 * @param la clé
 * */
void chiffrement(char * message, char * cle);

/**
 * dechiffrement
 * @param l'inverse de chiffrement de l'application de la cle
 * @param cle
 * */ 
void dechiffrement(char * message, char * cle);

/** 
 * Permet de lire un fichier
 * par défaut renvoie le nom du chemin
 * @param chemin
 * @return le résultat
 * */
char * lire_fichier(char * chemin);
#endif //_interface_h