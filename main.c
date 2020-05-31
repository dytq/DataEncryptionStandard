/* Bibliothèques */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bloc.h"
#include "interface.h"
#include "cle.h"
#include "feistel.h"

/* ------------- */

int main(int argc, char ** argv) {
	//parsing_terminal(argc,argv);
	chiffrement("testdesd","test");
	exit(EXIT_SUCCESS);
} 