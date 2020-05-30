#include "interface.h"

// Pour chiffrer/dechiffrer un bloc de 64 bits
typedef struct {
	bc32 gauche;
	bc32 droite;
} bc_text_s;

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
	if(argc < 2 || argc > 5) {
		error_parsing_terminal_entry();
	}	
	if(strcmp(argv[1],"aide") == 0) {
		afficher_aide();
		exit(EXIT_SUCCESS);
	}
	if(argc != 4) {
		error_parsing_terminal_entry();
	}
	if(strcmp(argv[1],"-e") == 0) {
		chiffrement(lire_fichier(argv[2]),lire_fichier(argv[3]));
	} else {
		if(strcmp(argv[1],"-d") == 0) {
			dechiffrement(lire_fichier(argv[2]),lire_fichier(argv[3]));
		}
		else {
			error_parsing_terminal_entry();
		}
	}
}

bc64 * convertir_message_64_bits(char * message) {
	unsigned long int taille_message = strlen(message);
	int nbr_bloc = (taille_message / 8) + 1;
	bc64 * blocs = malloc(sizeof(bc64) * nbr_bloc);
	int k = 0;
	bc64 tmp = 0;
	int bloc_inter = 0;
	while(k < taille_message) {		
		for(int i = 0 ; i < 8 ; i++) {
			tmp = tmp << 8;
			tmp = tmp | message[k]; 
			if(message[k] == EOF) {
				break;
			}
			k++;
		} 
		blocs[bloc_inter] = tmp;
		tmp = 0;
		bloc_inter ++;
	}
	return blocs;
}

// permet de chiffrer un message
void chiffrement(char * message, char * cle) {	
	
}

//permet de dechiffrer un message
void dechiffrement(char * message, char * cle) {
	
} 

char * lire_fichier(char * chemin) {
	FILE * fichier;
	fichier = fopen(chemin,"r");
	if(fichier == NULL) {
		return chemin;
	}
	char * res = malloc(sizeof(char) * 500);
	if(res == NULL) {
		fprintf(stderr,"Erreur d'allocation mémoire pour lire fichier");
		exit(EXIT_FAILURE);
	}
	char c;
	for(int i = 0; (c = fgetc(fichier)) != EOF; i++) {
		res[i] = c;
	}
	return res;
}
