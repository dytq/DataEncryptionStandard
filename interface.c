#include "interface.h"

// Pour chiffrer/dechiffrer un bloc de 64 bits
typedef struct {
	bc32 gauche;
	bc32 droite;
} bc_text_s;

// Matrice de Permutation
int IP[64] = {
	58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,
	64,56,48,40,32,24,16,8,
	57,49,41,33,25,17,9 ,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7
};

void afficher_aide() {
	printf("AIDE pour DES:\n");
	printf("TAPER ./out {option} {FICHIER A IMPORTER} {MOT_DE_PASSE}\n");
	printf("Les différentes options:\n");
	printf("	'-e': pour encoder\n");
	printf("	'-d': pour decoder\n");
	printf("Bien evidement appliquer une seule option :p\n");
	printf("L'agument {FICHIER A IMPORTER est un fichier à être importer");
	printf("L'argument {MOT_DE_PASSE} ne doit pas contenir d'espace\n");
	printf("	-C'est un fichier (le mot de passe peut contenir des espaces) OU le mot de passe sans espaces si le fichier n'existe pas\n");
}

void error_parsing_terminal_entry() {
	fprintf(stderr,"Option non valide, entrer aide comme option pour en savoir plus\n");
	exit(EXIT_FAILURE);
}

void parsing_terminal(int argc, char ** argv) {
	if(argc < 2 || argc > 4) {
		error_parsing_terminal_entry();
	}	
	if(strcmp(argv[1],"aide") == 0) {
		afficher_aide();
		exit(EXIT_SUCCESS);
	}
	if(argc != 3) {
		error_parsing_terminal_entry();
	}
	if(strcmp(argv[1],"-e") == 0) {
		chiffrement("test","test");
	} else {
		if(strcmp(argv[1],"-d") == 0) {
			dechiffrement("test","test");
		}
		else {
			error_parsing_terminal_entry();
		}
	}
}

// convertit un message en liste de 64 bits
bc64 * convertir_message_64_bits(char * message) {
	return NULL;
}

// permutation initial
bc64 permutation_initial(bc64 text) {
	return 0;
}

// permutation final
bc64 permutation_final(bc64 text) {
	return 0;
}

// permet de chiffrer un message
void chiffrement(char * message, char * cle) {
	
}

//permet de dechiffrer un message
void dechiffrement(char * message, char * cle) {
	
} 
