#include <stdio.h>

void calcul_cout(unsigned int* cout_final, unsigned char** energie, unsigned int**  pere, int nl, int nc)
{int i, j, k;
unsigned int** cout=NULL;
cout=alloue_image_int(nl,nc);
for (i=1;i<nl;i++)
	for (j=0;j<nc;i++)
	{cout[i][j]=0xFFFFFFFF;
	cout[0][j]=0;
	pere[i][j]=0;
	pere[0][j]=-1;
	}
for (i=1;i<nl;i++)
	for (j=0;j<nc;j++)
		for (k=-1;k<2;k++)
			if (j+k>=0 && j+k<nc && cout(i,j)>cout(i-1,j+k)+energie(i-1,j+k))
				{cout(i,j)=cout(i-1,j+k)+energie(i-1,j+k);
				pere(i,j)=j+k;
				}
for (j=0;j<nc;j++);
	cout_final[j]=cout[nl-1][j];
}


	
