#include "feistel.h"


bc32 feistel(bc32 moitie_bloc, bc48 sous_cle, int ** pointeur) {
	moitie_bloc = reverse_32_bits(moitie_bloc);
	bc48 expansion = swap_bloc_32_to_48(moitie_bloc, pointeur[13]);
	bc48 S = expansion ^ sous_cle;
	bc32 res =  fonctionS(S,pointeur);
	res = reverse_32_bits(res);
	res = swap_bloc_32(res, pointeur[10]);
	return res;
}

// a paralliser
bc4 thread_fonction_s(bc6 s,int * pointeur) {
	int ligne = ((s>>5) << 1) | (s&1);
	int colonne = (s & 0x1F) >> 1;
	return *(pointeur + (colonne + (16*ligne)));
}

bc32 fonctionS(bc48 text, int ** pointeur) {
	bc32 res = 0;
	bc48 masque = 0x0000003F; // masque initial
	int k = 9; // tableaux S entre 9 - 2
	bc32 tmp = 0;
	for(int i = 0 ; i < 8 ; i++) {
		masque = masque << 6*!(!i); // on déplace de 6 à gauche et on recupere la valeur
		tmp = thread_fonction_s((masque & text) >> 6*i,pointeur[k]); 
		tmp = tmp << (4*i);
		res = res | tmp;
		tmp = 0;
		k--;
	}
	return res;
}