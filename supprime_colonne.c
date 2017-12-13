#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL_phelma.h>

void swap (unsigned char a, unsigned char b)
{
	unsigned char  tmp;
	tmp = a;
	a = b;
	b = tmp;
}

void supprime_colonne(unsigned char** im, unsigned int* chemin, int nl, int nc)
{
	int i,j;
	for (i=0;i<nl;i++) {
		for (j=chemin[i];j<nc-1;j++) {
			swap(im[i][j],im[i][j+1]);
			}
		im[i][nc-1]=0;
	}
}

