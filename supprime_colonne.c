#include <stdio.h>

void supprime_colonne(unsigned char** im, unsigned int* chemin, int nl, int nc)
{int i,j;
for (i=0;i<nl;i++)
	{for (j=chemin(i);j<nc;j++)
		swap(im[i][j],im[i][j+1]);
	im[i][nc-1]=0;
	}
}

