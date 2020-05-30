#include "interface.h"

// Pour chiffrer/dechiffrer un bloc de 64 bits
typedef struct {
	bc32 gauche;
	bc32 droite;
} bc_text_s;

#define NBR_TABLEAUX 14

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

bc64 * convertir_message_64_bits(char * message, int taille_message, int nbr_bloc) {
	bc64 * blocs = malloc(sizeof(bc64) * nbr_bloc);
	int k = 0;
	bc64 tmp = 0;
	int bloc_inter = 0;
	while(k < taille_message) {		
		for(int i = 0 ; i < 8 ; i++) {
			if(message[k] == '\0') { // on ne chiffre pas le caractere de fin de chaine
				break;
			}
			tmp = tmp << 8;
			tmp = tmp | message[k]; 
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
	int * (*pointeur) = malloc(sizeof(int *) * NBR_TABLEAUX); // liste de pointeurs pour choisir quel tableau on utilise
    init_pointeur(pointeur);
	unsigned long int taille_message = strlen(message);
	int nbr_bloc = ((taille_message - 1) / 8) + 1;

	bc64 * blocs = convertir_message_64_bits(message, taille_message, nbr_bloc);
	
	// init la liste des 16 clés

	for(int i = 0 ; i < nbr_bloc ; i++) {
		swap_bloc_64(blocs[i], pointeur[0]);
		// algo chiffrement des:
		// init les deux branches 
		for(int j = 0 ; j < 8 ; j++) {
			// on F gauche
			// on xor droite et gauche
			// on F droite
			// on xor droite et gauche
		}
		swap_bloc_64(blocs[i], pointeur[1]);
	}
	
	for(int i = 0 ; i < nbr_bloc ; i++) {
		printf("[%lX]\n",blocs[i]); 
	}
	free(blocs);
	free(pointeur);
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
