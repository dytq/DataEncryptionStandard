#include "cle.h"

// partie gauche de la clé
int PC_1G [28] = {
	57,49,41,33,25,17,9 ,
	1 ,58,50,42,34,26,18,
	10,2 ,59,51,43,35,27,
	19,11,3 ,60,52,44,36
};

// partie droite de la clé
int PC_1D [28] = {
	63,55,47,39,31,23,15,
	7 ,62,54,46,38,30,22,
	14,6 ,61,53,45,37,29,
	21,13,5 ,28,20,12,4 
};

// Transposition avec oubli
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

bc_cle_s permutation_initial_cle(bc64 cle) {
	bc_cle_s B;
	B.gauche = 0;
	B.droite = 0;
	return B;
}

bc48 genere_cle_48_bits(bc_cle_s B) {
	
	return 0;
}
