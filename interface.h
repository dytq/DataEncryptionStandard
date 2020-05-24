#ifndef _interface_h
#define _interface_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#endif //_interface_h
