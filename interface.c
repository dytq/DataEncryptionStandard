#include "interface.h"

void afficher_aide() {
	printf("AIDE pour DES:\n");
	printf("TAPER ./out {option} {MESSAGE} {MOT_DE_PASSE}\n");
	printf("Les différentes options:\n");
	printf("	'-e': pour encoder\n");
	printf("	'-d': pour decoder\n");
	printf("Bien evidement appliquer une seule option et chaque argument est séparé par un espace\n");
	printf("Un argument peut-etre un fichier a importer ou un text. Par defaut le programme prend  le nom du fichier s'il est inexistant\n");
	printf("L'agument {MESSAGE} est le message, soit ascii pour chiffrer soit en hexa pour dechiffrer\n");
	printf("L'argument {MOT_DE_PASSE} est le mot de passe qu'on veut chiffrer\n");
}

void error_parsing_terminal_entry() {
	fprintf(stderr,"Option non valide, entrer aide comme option (`./des.out aide`) pour en savoir plus\n");
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
	if(blocs == NULL) {
		fprintf(stderr,"Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
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

bc_text_s init_bc_text(bc64 text) {
	bc_text_s B;
	B.gauche = text >> 32;
	B.droite = text; 
	return B;
}

bc28 reformate_28_bits(bc28 value) {
	return ((value | 0xF0000000) ^ 0xF0000000);	
}
bc28 double_shift_bc28(bc28 value, int shift) {
	shift = shift % 28;
	value = value << shift | value >> (28 - shift) ;
	return reformate_28_bits(value);
}
bc64 * convertir_message_en_hexa_64_bits(char * message, int nbr_bloc) {
	bc64 * blocs = malloc(sizeof(bc64) * nbr_bloc);
	int k = 0;
	for(int i = 0 ; i < nbr_bloc ; i++) {
		char * buff = malloc(sizeof(char) * 16 + sizeof('\0'));
		for(int j = 0 ; j < 16 ; j++) {
			buff[j] = message[k];
			k++;
		}
		blocs[i] = strtoul(buff,NULL,16);
		free(buff);
	}
	return blocs;
}

void chiffrement(char * message, char * mot_de_passe) {	
	int * (*pointeur) = malloc(sizeof(int *) * NBR_TABLEAUX); // liste de pointeurs pour choisir quel tableau on utilise
	init_pointeur(pointeur);
	
	unsigned long int taille_message = strlen(message);
	int nbr_bloc = ((taille_message - 1) / 8) + 1;

	bc64 * blocs = convertir_message_64_bits(message, taille_message, nbr_bloc);
	
	/* Generation de cles */
	bc48 * sous_cle = malloc(sizeof(bc48) * 16);
	bc_cle_s * cle = malloc(sizeof(bc_cle_s));
	if(sous_cle == NULL || cle == NULL ) {
		fprintf(stderr,"Erreur d'allocation de mémoire\n");
		exit(EXIT_FAILURE);
	}
	init_cles("testtest", cle,  pointeur);
	// generer les 16 clées : 
	for(int i = 0 ; i < 16 ; i++) {
		cle->gauche = double_shift_bc28(cle->gauche, (*(pointeur[14] + i)));
		cle->droite = double_shift_bc28(cle->droite, (*(pointeur[14] + i)));	
		sous_cle[i] = genere_cle_48_bits(cle, pointeur[12]);
	} 

	// Feistel:
	for(int i = 0 ; i < nbr_bloc ; i++) {
		blocs[i] = reverse_64_bits(blocs[i]);
		blocs[i] = swap_bloc_64(blocs[i],pointeur[0]);
		bc_text_s B = init_bc_text(blocs[i]);

		bc32 tmp = 0;
		for(int j = 0 ; j < 16 ; j++) {
			tmp = B.droite;
			B.droite = B.gauche ^ feistel(B.droite,sous_cle[j],pointeur);
			B.gauche =tmp;
		}
	
		blocs[i] = B.droite;
		blocs[i] = ((blocs[i] << 32) | B.gauche);
		blocs[i] = reverse_64_bits(blocs[i]);
		blocs[i] = swap_bloc_64(blocs[i], pointeur[1]);
	}
	
	for(int i = 0 ; i < nbr_bloc ; i++) {
		printf("%lX",blocs[i]); 
	}
	
	free(blocs);
	free(pointeur);
	free(cle);
}

void dechiffrement(char * message, char * mot_de_passe) {
	int * (*pointeur) = malloc(sizeof(int *) * NBR_TABLEAUX); // liste de pointeurs pour choisir quel tableau on utilise
	init_pointeur(pointeur);
	
	unsigned long int taille_message = strlen(message);
	
	int nbr_bloc = (taille_message) / 16;

	bc64 * blocs = convertir_message_en_hexa_64_bits(message, nbr_bloc);
	
	/* Generation de cles */ 
	
	bc48 * sous_cle = malloc(sizeof(bc48) * 16);
	bc_cle_s * cle = malloc(sizeof(bc_cle_s));
	if(sous_cle == NULL || cle == NULL ) {
		fprintf(stderr,"Erreur d'allocation de mémoire\n");
		exit(EXIT_FAILURE);
	}
	init_cles("testtest", cle,  pointeur);
	// generer les 16 clées : 
	for(int i = 0 ; i < 16 ; i++) {
		cle->gauche = double_shift_bc28(cle->gauche, (*(pointeur[14] + i)));
		cle->droite = double_shift_bc28(cle->droite, (*(pointeur[14] + i)));	
		sous_cle[i] = genere_cle_48_bits(cle, pointeur[12]);
	} 

	for(int i = 0 ; i < nbr_bloc ; i++) {
		blocs[i] = reverse_64_bits(blocs[i]);
		blocs[i] = swap_bloc_64(blocs[i],pointeur[0]);
		bc_text_s B = init_bc_text(blocs[i]);

		bc32 tmp = 0;
		for(int j = 15 ; j >= 0 ; j--) {
			tmp = B.droite;
			B.droite = B.gauche ^ feistel(B.droite,sous_cle[j],pointeur);
			B.gauche =tmp;
		}
		
		blocs[i] = B.droite;
		blocs[i] = ((blocs[i] << 32) | B.gauche);
		blocs[i] = reverse_64_bits(blocs[i]);
		blocs[i] = swap_bloc_64(blocs[i], pointeur[1]);
	}
	// il faut juste convertir
	for(int i = 0 ; i < nbr_bloc ; i++) {
		printf("%lX",blocs[i]); 
	}
	
	free(blocs);
	free(pointeur);
	free(cle);
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
