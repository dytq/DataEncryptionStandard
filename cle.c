#include "cle.h"

void init_cles(char * mot_de_passe, bc_cle_s * B, int ** pointeur) {
	bc64 * blocs;
	int taille_cle = strlen(mot_de_passe);
	if(taille_cle > 64) {
		fprintf(stderr,"Mot de passe entrée trop grande\n");
		exit(EXIT_FAILURE);
	}
	blocs = convertir_message_64_bits(mot_de_passe,taille_cle,1);
	*blocs = reverse_64_bits(*blocs);
	*B = permutation_initial_cle(*(blocs), pointeur);
	free(blocs);
}

bc_cle_s permutation_initial_cle(bc64 cle, int ** pointeur) {
	bc_cle_s B;
	bc56 bloc_56 = swap_bloc_64_to_56(cle, pointeur[11]);
	B.gauche = bloc_56 >> 28;
	/* en réalité un bc56 est un binaire de 64 bits */
	B.droite = bloc_56 << 4;
	B.droite = B.droite >> 4;
	return B;
}

bc48 genere_cle_48_bits(bc_cle_s * C, int * pointeur) {
	bc56 cle = C->gauche;
	cle = (cle << 28) | C->droite;
	cle = reverse_56_bits(cle);
	return swap_bloc_56_to_48(cle,pointeur);
}
