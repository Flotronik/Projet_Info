#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<SDL_phelma.h>


unsigned char ** alloue_image_char(int nl, int nc) 
{
	unsigned char **p; int i;
	p=(unsigned char**)calloc(nl,sizeof(*p));
	if (p==NULL) {
		return NULL;
	} else {
for(i=0;i<nl;i++){
p[i]=(unsigned char*)calloc(nc,sizeof(**p));
		if (p[i]==NULL) {
			return NULL;
		}}}
	return p;
}

unsigned int ** alloue_image_int(int nl, int nc)
{
	unsigned int **p; int i;
	p=(unsigned int**)calloc(nl,sizeof(*p));
	if (p==NULL) {
		return NULL;
	} else { 
for(i=0;i<nl;i++){
		p[i]=(unsigned int*)calloc(nc,sizeof(**p));
		if (*p==NULL) {
			return NULL;
		} }}
	return p;
}

void libere_image_char(unsigned char** im, int nl)
{
	int i;
	for (i=0;i<nl;i++) {
		free(im[i]);
	}
	free(im);
}

void libere_image_int(unsigned int** im, int nl)
{
	int i;
	for (i=0;i<nl;i++) {
		free(im[i]);
	}
	free(im);
}
	

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



void calcul_cout(unsigned int* cout_final, unsigned char**energie,unsigned int**pere,int nl, int nc)
{   

    int i, j, k;
    unsigned int** cout=NULL;
    cout=alloue_image_int(nl,nc);
    for (i=0;i<nl;i++) {
	    for (j=0;j<nc;j++) {
	    cout[i][j]=0xFFFFFFFF;
	    pere[i][j]=0;
	    }
    }

    for (j=0;j<nc;j++) {
	    cout[0][j]=0;
	    pere[0][j]=-1;
    }

    for (i=1;i<nl;i++) {
	    for (j=0;j<nc;j++) {
		    for (k=-1;k<2;k++) {
			    if (j+k>=0 && j+k<nc && cout[i][j]>cout[i-1][j+k]+energie[i-1][j+k]) {
                    		cout[i][j]=cout[i-1][j+k]+energie[i-1][j+k];
				pere[i][j]=j+k;
			    }
	            }
	    }
    }		


    for (j=0;j<nc;j++) {
	    cout_final[j]=cout[nl-1][j];
    }
}



void swap (unsigned char**im,int nl,int nc, int i,int j)
{
	unsigned char tmp;
	tmp = im[i][j];
	im[i][j] = im[i][j+1];
	im[i][j+1] = tmp;
}

void supprime_colonne(unsigned char** im, unsigned int* chemin, int nl, int nc)
{
	int i,j;
	for (i=0;i<nl;i++) {
		for (j=chemin[i];j<(nc-1);j++) {
			swap(im,nl,nc,i,j);
			}
		im[i][nc-1]=0;
	}
}

void trouve_chemin(unsigned int* chemin,unsigned int** pere, unsigned int* coutfinal,int nl, int nc)
{ int j;
	int colonne=0,i,min=coutfinal[0];

	for (i=1;i<nc;i++){
		if(coutfinal[i]<min){
			min=coutfinal[i]; colonne=i;
		}
	}

	chemin[nl-1]=colonne;
	for(i=nl-2;i>=0;--i){
printf("%d\n",i);
printf("%d\n",pere[i+1][0]);
printf("%d\n",chemin[i+1]);
		chemin[i]=pere[i+1][chemin[i+1]];
printf("a\n");
	}

}


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




void seam_carving(unsigned char** im, int nbcol, int nl,int nc) 
{
	unsigned char**energie=NULL,**energ=NULL;
	unsigned int*coutfinal,* chemin; unsigned int**pere;unsigned int**cop;
	int i,j;
	for(i=0;i<nbcol;i++){
		coutfinal=calloc(nl,sizeof(*coutfinal));
		cop=alloue_image_int(nl,nc-i);
		chemin=calloc(nl,sizeof(*chemin));
		pere=alloue_image_int(nl,nc-i);
		energ=alloue_image_char(nl,nc-i);

		energie=gradienty(energ,im,nl,nc-i);	
//fonctionne jusqu'ici
		calcul_cout(coutfinal,energie,pere,cop,nl,nc-i);
//calcule bien coutfinal avec energie et pere mais pere se volatilise ??? (plus aucune trace du tableau pere...)
printf("energie\n");
printf("%d\t",energie[0][0]);
	for(i=0;i<nl;i++){
		for(j=0;j<nc;j++){
			printf("%d\t",energie[i][j]);}
		printf("\n");}
	printf("\n");
	printf("\n");
	printf("\n");

		trouve_chemin(chemin,pere,coutfinal,nl,nc-i);

		supprime_colonne(im,chemin,nl,nc-i);

		libere_image_int(pere,nl);
printf("a\n");
		libere_image_char(energ,nl);
printf("b\n");
		free(coutfinal);
printf("c\n");
		free(chemin);
	}
}



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
printf("d\n");

  if (mode) { 
    afficheim8SDL(fenetre, im,nl,nc,nbcol/2,nl); 
    afficheim8SDL(fenetre, im3,nl,nc,0,0); 
    puts("Taper CR pour terminer"); getchar();
  }


  ecritureimagepgm(av[2],im,nl,nc);

  libere_image_char((unsigned char**)im,nl); libere_image_char((unsigned char**)im3,nl);
  exit(EXIT_SUCCESS);
}


