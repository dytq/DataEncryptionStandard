#include "cle.h"

bc64 reverse_64_bits(bc64 v) {
	unsigned long int r = v;
	int s = sizeof(v) * 8 - 1;

	for (v >>= 1; v; v >>= 1)
	{   
		r <<= 1;
		r |= v & 1;
		s--;
	}
	r <<= s; 
	return r;
} 

bc56 reverse_56_bits(bc64 v) {
	unsigned long int r = v; 
	int s = sizeof(v) * 8 - 1; 

	for (v >>= 1; v; v >>= 1)
	{   
		r <<= 1;
		r |= v & 1;
		s--;
	}
	r <<= s;  
	return r >> 8;
} 

void init_cles(char * mot_de_passe, bc_cle_s * B, int ** pointeur) {
	bc64 * blocs;
	int taille_cle = strlen(mot_de_passe);
	blocs = convertir_message_64_bits(mot_de_passe,taille_cle,1);
	blocs[0] = reverse_64_bits(0x133457799BBCDFF1); // reverse
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
	cle = cle << 28;
	cle = cle | C->droite;
	cle = reverse_56_bits(cle);
	return swap_bloc_56_to_48(cle,pointeur);
}