#include <stdio.h>
#include <stdlib.h>
#include "allocation.h"


main()
{
	unsigned char ** imagechar=NULL; unsigned int ** imageint=NULL; int i,j;
	imagechar=alloue_image_char(10,10);
	imageint=alloue_image_int(10,10);
	for (i=0; i<10;i++)
		for (j=0; j<10;j++)
		printf("L'adresse de la case %d est : %p\n",i,&imageint[i][j]);
		//printf("L'adresse de la case %d est : %p\n",i,&imagechar[i][j]);
}


