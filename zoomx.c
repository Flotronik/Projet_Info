#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL_phelma.h>


/* 
	Zoom horizontal de centre nl/2,jc. L'image reste de la meme taille
        nbcol sont supprimees donc le facteur de zoom est nc-nbcol/nc
*/
unsigned char ** zoomx_image(unsigned char **ims, unsigned char **im, int nbcol, int jc, int nl, int nc) { int i,j;
  double nj; 
  if (ims == NULL) ims = alloue_image_char(nl,nc);
  for (i=0; i<nl; i++)
    for (j=nbcol/2; j<nc-nbcol/2; j++) {
       nj=nc/2+(j-nc/2)*nc/(double)(nc-nbcol);
       ims[i][j]= (1-nj+(int)nj)*im[i][((int)nj+nc)%nc] + (nj-(int)nj) *im[i][((int)nj+1)%nc];
    }
  return ims;
}
