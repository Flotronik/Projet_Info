#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL_phelma.h>

void seam_carving(unsigned char** im, int nbcol, int nl,int nc) 
{
	unsigned char**energie=NULL,**energ=NULL;
	unsigned int*coutfinal,* chemin; unsigned char**pere;
	int i;
	for(i=0;i<nbcol;i++){
		coutfinal=alloue_image_int (nl,1);
		chemin=alloue_image_int(nl,1);
		pere=alloue_image_char(nl,nc-i);
		energ=alloue_image_char(nl,nc-i);

		energie=gradienty(energ,im,nl,nc-i);
		calcul_cout(coutfinal,energie,pere,nl,nc-i);
		trouve_chemin(chemin,pere,coutfinal,nl,nc-i);
		supprime_colonne(im,chemin,nl,nc-i);

		libere_image(pere);
		libere_image(energ);
		free(coutfinal);
		free(chemin);
	}
}
