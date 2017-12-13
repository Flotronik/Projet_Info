#include <stdio.h>
#include <stdlib.h>

void trouve_chemin(unsigned int* chemin,unsigned int** pere, unsigned int* coutfinal,int nl, int nc)
{
	int colonne=0,i,min=coutfinal[0];
	for (i=1;i<nc;i++){
		if(coutfinal[i]>min){
			min=coutfinal[i]; colonne=i;
		}
	}
	chemin[nl-1]=min;
	for(i=nl-2;i<0;i--){
		chemin[i]=pere[i+1][chemin[i+1]];
	}
}

