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
	dechiffrement("96F989FC3DA7B337","test");
	exit(EXIT_SUCCESS);
}