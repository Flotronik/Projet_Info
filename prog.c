#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<SDL_phelma.h>


main(int ac, char**av) { int nl, nc;
  unsigned char** im, ** im3;
  SDL_Surface* fenetre=NULL;
  
  if (ac!=4 || av[1]==NULL || 
      (im=lectureimage8(av[1],&nl,&nc))==NULL){
      printf("Usage : %s fichier_image_entree fichier_image_sortie nb_colonne_a_supprimer \n",av[0]); exit(1); 
  }
  int nbcol=atoi(av[3]);
  int mode=1;

  if (nbcol<=0 || nbcol>=nc) { printf("Pas assez ou trop de colonnes Ã  supprimer\n"); exit(-1); }

  if (mode) {fenetre=newfenetregraphique(nc,3*nl); 
    if (fenetre==NULL) exit(EXIT_FAILURE);
    Draw_FillRect(fenetre, 0, 0, nc, 3*nl, SDL_PH_NOIR);
    afficheim8SDL(fenetre, im,nl,nc,0,2*nl);
  }

  im3=zoomx_image(NULL,im,nbcol,nc/2,nl,nc);
  seam_carving(im,nbcol,nl,nc);

  if (mode) { 
    afficheim8SDL(fenetre, im,nl,nc,nbcol/2,nl); 
    afficheim8SDL(fenetre, im3,nl,nc,0,0); 
    puts("Taper CR pour terminer"); getchar();
  }
  ecritureimagepgm(av[2],im,nl,nc);

  libere_image_char((unsigned char**)im,nl); libere_image_char((unsigned char**)im3,nl);
  exit(EXIT_SUCCESS);
}
