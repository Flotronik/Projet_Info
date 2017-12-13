#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned char**gradienty(unsigned char** energ, unsigned char** im, int nl, int nc)
{
	int i,j;
	if(energ==NULL){ 
		energ=alloue_image_char(nl,nc);
	}

	for(i=0;i<nl;i++){
		for(j=0;j<nc;j++){
			energ[i][j]=abs(im[i][(j-1+nc)%nc]-im[i][(j+1)%nc]);
		}
	}
	return energ; 
} 
