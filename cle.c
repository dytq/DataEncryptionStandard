#include "cle.h"
/*
void affiche_bin(bc64 text, int taille) {
	for(int i = 0; i < taille; i++) {
		printf("%ld",text & 1);
		text = text >> 1;
	}
	printf("\n");
}*/

void init_cles(char * mot_de_passe, bc_cle_s * B, int ** pointeur) {
	bc64 * blocs;
	int taille_cle = strlen(mot_de_passe);
	blocs = convertir_message_64_bits(mot_de_passe,taille_cle,1);
	*B = permutation_initial_cle(blocs[0], pointeur);
	free(blocs);
}

bc_cle_s permutation_initial_cle(bc64 cle, int ** pointeur) {
	bc56 bloc_56 = swap_bloc_64_to_56(cle,pointeur[15]);
	bc_cle_s B;
	B.gauche = bloc_56 >> 28;
	B.droite = bloc_56;
	// Permutation PC1
	B.droite = swap_bloc_28(B.droite,pointeur[10]);
	B.gauche = swap_bloc_28(B.gauche,pointeur[11]); 
	return B;
}

bc48 genere_cle_48_bits(bc_cle_s * B,int * pointeur) {
	bc56 cle = B->gauche;
	cle = cle << 28;
	cle = cle | B->droite;
	return swap_bloc_56_to_48(cle,pointeur);
}
