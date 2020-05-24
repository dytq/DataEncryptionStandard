#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int * gauche; // taille 32
	int * droite; // taille 32
} bloc;

typedef struct {
	int * cle_56; // taille 56
	int * gauche; // taille 26
	int * droite; // taille 26
} sous_cle;

/* Les Différentes Matrice utilisé */

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

// Matrice de Developpement
int E[48] = {
	32,1 ,2 ,3 ,4 ,5 ,
	4 ,5 ,6 ,7 ,8 ,9 ,
	8 ,9 ,10,11,12,13,
	12,13,14,15,16,17,
	16,17,18,19,20,21,
	20,21,22,23,24,25,
	24,25,26,27,28,29,
	28,29,30,31,32,1 
};

int P[32] = {
	16,7 ,20,21,
	29,12,28,17,
	1 ,15,23,26,
	5 ,18,31,10,
	2 ,8 ,24,14,
	32,27,3 ,9 ,
	19,13,30,6 ,
	22,11,4 ,25 
};

int PC_2 [48] = {
	14,17,11,24,1 ,5 ,
	3 ,28,15,6 ,21,10,
	23,19,12,4 ,26,8 ,
	16,7 ,27,20,13,2 ,
	41,52,31,37,47,55,
	30,40,51,45,33,48,
	44,49,39,56,34,53,
	46,42,50,36,29,32
};

int PC_1G [28] = {
	57,49,41,33,25,17,9 ,
	1 ,58,50,42,34,26,18,
	10,2 ,59,51,43,35,27,
	19,11,3 ,60,52,44,36
};

int PC_1D [28] = {
	63,55,47,39,31,23,15,
	7 ,62,54,46,38,30,22,
	14,6 ,61,53,45,37,29,
	21,13,5 ,28,20,12,4 
};

int Boite_S [8][64] = {
	{
		14,4 ,13,1 ,2 ,15,11,8 ,3 ,10,6 ,12,5 ,9 ,0 ,7 ,
		0 ,15,7 ,4 ,14,2 ,13,1 ,10,6 ,12,11,9 ,5 ,3 ,8 ,
		4 ,1 ,14,8 ,13,6 ,2 ,11,15,12,9 ,7 ,3 ,10,5 ,0 ,
		15,12,8 ,2 ,4 ,9 ,1 ,7 ,5 ,11,3 ,14,10,0 ,6 ,13
	},

	{
		15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
		3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
		0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
		13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
	},

	{
		10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
		13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
		13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
		1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
	},

	{ 
		7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
		13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
		10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
		3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
	},

	{
		2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
		14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
		4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
		11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
	},

	{
		12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
		10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
		9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
		4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
	},

	{ 
		4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
		13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
		1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
		6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
	},

	{
		13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
		1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
		7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
		2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
	}
};
/* ------------------------------- */

/**
 * Permet d'initialisé un test
 * @param size: la taille du texte pour l'alloué
 * @return le texte init à 0
 * */
int * init_text(int size) {
	
	int * text = malloc(sizeof(int) * size);

	for(int i = 0; i < size; i++) {
		text[i] = 0;
	}
	
	return text;
}

/**
 * Permutation initial
 * @param text: pour la première permutation
 * @return res
 * */
int* permutation_initial(int * text) {
	int * tmp = init_text(64);
	for(int i = 0 ; i < 64 ; i++) {
		tmp[IP[i] - 1] = text[i];
	}
	for(int i = 0 ; i < 64 ; i++) {
		text[i] = tmp[i];
	}
	free(text);
	return tmp;
}

/**
 * Permutation final
 * @param text: pour la dernière permutation
 * @return res
 * */
int* permutation_final(int * text) {
	int * tmp = init_text(64);
	for(int i = 0 ; i < 64 ; i++) {
		tmp[i] = text[IP[i] - 1];
	}
	for(int i = 0 ; i < 64 ; i++) {
		text[i] = tmp[i];
	}
	free(text);
	return tmp;
}

/**
 * Initialise les blocs
 * @param text: texte de 64 bits
 * @return res
 * */
bloc init_bloc(int * text) {
	bloc B;
	B.gauche = init_text(32);
	B.droite = init_text(32);
	int k = 0;
	for(int i = 0; i < 32; i++) {
		B.gauche[i] = text[k];
		k++;
	}
	for(int i = 0; i < 32; i++) {
		B.droite[i] = text[k];
		k++;
	}
	return B;
}

/**
 * Fonction d'expansion
 * @param side: le coté pour appliqué l'expension
 * @return res
 * */
int * expansion(int * side) {
	int * tmp = init_text(48);
	
	for(int i = 0 ; i < 48 ; i++) {
		tmp[i] = side[E[i] - 1];
	}
	return tmp;
}

/**
 * Fonction de permutation
 * @param text_32: un texte de 32 bits
 * @return res
 * */
int * permutation(int * text_32) {
	int * tmp = init_text(32);
	
	for(int i = 0 ; i < 32 ; i ++) {
		tmp[i] = text_32[P[i] - 1];
	}
	free(text_32);
	return tmp;
}

/**
 * Permet d'afficher un texte
 * @param text
 * @param taille
 * */
void afficher_text(int * text, int size) {
	for(int i = 0; i < size ; i++) {
		printf("[%d]",text[i]);
	}
	printf("\n");
}

/**
 * Concatene les deux clé pour crée la clé de 56 bits
 * @param C: la structure bloc ou contient les inforamations
 * */
void cat_key(sous_cle * C) {
	int * res = init_text(56);
	int k = 0;
	
	for(int i = 0; i < 28; i++) {
		C->cle_56[k] = C->gauche[i];
		k++;
	}
	
	for(int i = 0; i < 28; i++) {
		C->cle_56[k] = C->droite[i];
		k++;
	}
}

/**
 * Permet de récuperer la clé de 56 bits dans la clé de 64 bits
 * @param cle_64: la clé de 64 bits
 * @return la clé de 56 bits
 * */
int * prendre_cle_56(int * cle_64) {	
	int * cle_56 = init_text(56);
	int parite[8] = {8,16,24,32,40,48,56,64};
	int k = 0;
	int j = 0;
	for(int i = 0; i < 64 ; i++) {
		if(i == parite[j] - 1) {
			j++;
		}
		else {
			cle_56[k] = cle_64[i];
			k++;
		}
	}
	return cle_56;
}

/**
 * Permet d'initialisé la sous-clé
 * @param cle_64: la clé de 64 bits
 * @return la structure de donnée
 * */
sous_cle init_sous_cle(int * cle_64) {
	sous_cle C; 
	C.gauche = init_text(28);
	C.droite = init_text(28);
	C.cle_56 = prendre_cle_56(cle_64);
	return C;
}

/**
 * Permet de crée la clé pour xor
 * @param C la structure de donné
 * @return la clé de 48 bits
 * */
int * creer_cle_48(sous_cle * C) {

	for(int i = 0 ; i < 28 ; i++) {
		C->gauche[i] = C->cle_56[PC_1G[i-1]];
	}
	for(int i = 0; i < 28 ; i++) {
		C->droite[i] = C->cle_56[PC_1D[i-1]];
	}
	cat_key(C);
	
	int * cle_48 = init_text(48);
	// transposition avec oubli
	for(int i = 0; i < 48; i++) {
		cle_48[i] = C->cle_56[PC_2[i]]; 
	}
	
	return cle_48;
}

/**
 * Xor pour deux tableaux
 * @param cle_48
 * @param side de 48 éléments
 * @return res du xor
 * */
int * Xor(int * cle_48, int * side) {
	int * res = init_text(48);
	for(int i = 0; i < 48 ; i++) {
		res[i] = cle_48[i] ^ side[i];
	}
	return res;
}

/**
 * Fonction de S boite
 * @param res_48: les 48 bits d'entrée
 * @return nombre de bits de 32 bits
 * */
int * S_boite_fonction(int * res_48) {
	
	return res_48;
}

/**
 * Permet d'assembler le message final
 * @param gauche: le cote gauche
 * @param droite: le cote droit
 * @return la concatenation des deux cotés
 * */
int * assemble_message(int * gauche, int * droite) {
	int * chiffre = init_text(64);
	int k = 0;
	for(int i = 0 ; i < 32; i++) {
		chiffre[k] = gauche[i];
		k++;
	}
	for(int i = 0 ; i < 32; i++) {
		chiffre[k] = droite[i];
		k++;
	}
	return chiffre;
}

/**
 * Fonction Ronde
 * @param B: structure de bloc
 * @param C: structure de sous cle
 * @return le resultat des 16 rondes
 * */
int * Ronde(bloc B, sous_cle C) {
	for(int i = 0 ; i < 16 ; i++) {
		
		int * bloc_48G = expansion(B.gauche);
		int * bloc_48D = expansion(B.droite);
		
		int * cle_48 = creer_cle_48(&C);
		
		S_boite_fonction(Xor(cle_48,B.gauche));
		S_boite_fonction(Xor(cle_48,B.droite));
		
		B.gauche = permutation(B.gauche);
		B.droite = permutation(B.droite);
		// il faut shift gauche les deux parties 
		free(cle_48);
		free(bloc_48G);
		free(bloc_48D);
	}
	return assemble_message(B.gauche,B.droite);
} 

/* DEBUG */
int main() {
	/* Init element */
	int * text = init_text(64);
	text[0] = 1;
	text[1] = 1;
	int * mdp = init_text(64);
	mdp[0] = 1;
	mdp[1] = 1;
	/* ------------ */ 
	printf("Message à chiffre:\n");
	afficher_text(text,64);
	printf("Clé:\n");
	afficher_text(mdp,64);
	
	/* PHASE 1 */
	// Première permutation
	text = permutation_initial(text);
	printf("Première permutation:\n");
	afficher_text(text,64);
	
	// init bloc
	bloc B = init_bloc(text);
	printf("Coté gauche:\n");
	afficher_text(B.gauche,32);
	printf("Coté droit:\n");
	afficher_text(B.droite,32);
	// Init la clé
	sous_cle C = init_sous_cle(mdp);
	printf("Initialisation des clés:\n");
	printf("clés gauche:\n");
	afficher_text(C.gauche,26);
	printf("clés droite:\n");
	afficher_text(C.droite,26);
	printf("clés:\n");
	afficher_text(C.cle_56,56);
	
	/* PHASE 2 */
	// Phase des 16 rondes
	int * chiffre = init_text(64);
	chiffre = Ronde(B,C);
	
	/* PHASE 3 */
	// Permutation inverse
	chiffre = permutation_final(chiffre);

	/* Free element */
	free(C.gauche);
	free(C.droite);
	free(C.cle_56);
	free(text);
	free(chiffre);
	free(mdp);
	/* ------------ */
	return 0;
} 
