#include "interface.h"

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

void chiffrement(char * message, char * mot_depasse) {	
	int * (*pointeur) = malloc(sizeof(int *) * NBR_TABLEAUX); // liste de pointeurs pour choisir quel tableau on utilise
	init_pointeur(pointeur);
	unsigned long int taille_message = strlen(message);
	int nbr_bloc = ((taille_message - 1) / 8) + 1;

	bc64 * blocs = convertir_message_64_bits(message, taille_message, nbr_bloc);
	//blocs[0] = 0x123456789ABCDEF;
	/*blocs[0] = 0x0123456789abcdef;
	printf("hexa:");
	for(int i = 0 ; i < nbr_bloc ; i++) {
		printf("[%lX]\n",blocs[i]); 
	}
	printf("bin:");
	bc64 copie = ~blocs[0];
	for (int i = 0; i < 64; i++)
	{
		printf("%lX",copie & 1);
		copie = copie >> 1;
	}
	printf("\n");
	*/
	/* Generation de cles */
	bc48 * sous_cle = malloc(sizeof(bc48) * 16);
	bc_cle_s * cle = malloc(sizeof(bc_cle_s));
	init_cles("testtest", cle,  pointeur);
	for(int i = 0 ; i < 16 ; i++) {
		cle->gauche = double_shift_bc28(cle->gauche, (*(pointeur[14] + i)));
		cle->droite = double_shift_bc28(cle->droite, (*(pointeur[14] + i)));	
		printf("cle gauche [%X] : cle droite : [%X] \n",cle->gauche,cle->droite);
		sous_cle[i] = genere_cle_48_bits(cle, pointeur[12]);
		printf("sous - cle: %lX\n",sous_cle[i]);
	} 
	blocs[0] = 0x123456abcd132536;
	printf("init text:%lX\n",blocs[0]);
	blocs[0] = reverse_64_bits(blocs[0]);
	blocs[0] = swap_bloc_64(blocs[0],pointeur[0]);
	bc_text_s B = init_bc_text(blocs[0]);
	printf("Split:\n");
	printf("L[0]=%X\n",B.gauche);
	printf("R[0]=%X\n",B.droite);
	/*
	for(int i = 0 ; i < nbr_bloc ; i++) {
		blocs[i] = swap_bloc_64(blocs[i], pointeur[0]);
		printf("IP:%lX\n",blocs[i]);
		bc_text_s B = init_bc_text(blocs[i]);
		printf("L[0]=%X\n",B.gauche);
		printf("R[0]=%X\n",B.droite);
		bc32 tmp = 0;
		for(int j = 0 ; j < 16 ; j++) {
			B.gauche = B.gauche ^ feistel(B.droite,sous_cle[j],pointeur);
			B.droite = B.droite ^ feistel(B.gauche,sous_cle[j],pointeur);
			printf("L[%d]=%X, R[%d] %X et cle:%lX\n",j+1,B.gauche,j+1,B.droite,sous_cle[j]);
		}
	
		blocs[i] = 0;
		blocs[i] = B.gauche;
		blocs[i] = blocs[i] << 32;
		blocs[i] = blocs[i] | B.droite;
	
		blocs[i] = swap_bloc_64(blocs[i], pointeur[1]);
	}
	
	for(int i = 0 ; i < nbr_bloc ; i++) {
		printf("[%lX]\n",blocs[i]); 
	}
	*/
	free(blocs);
	free(pointeur);
	free(cle);
}

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
