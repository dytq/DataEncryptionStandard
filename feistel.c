#include "feistel.h"

bc32 feistel(bc32 moitie_bloc, bc48 sous_cle, int ** pointeur) {
	bc48 expansion = swap_bloc_32(moitie_bloc, pointeur[13]);
	bc48 S = expansion ^ sous_cle;
	bc32 res =  fonctionS(S);
	res = swap_bloc_32(res, pointeur[9]);
	return 0;
}

bc32 fonctionS(bc48 text) {
	return 0;
} 
