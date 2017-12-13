#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned char ** alloue_image_char(int nl, int nc) 
{
	unsigned char **p; int i;
	p=(unsigned char**)calloc(nl,sizeof(*p));
	if (p==NULL) {
		return NULL;
	} else {
		*p=(unsigned char*)calloc(nl*nc,sizeof(**p));
		if (*p==NULL) {
			free(p);
			return NULL;
		} else { 
			for (i=1;i<nl;i++) {
				p[i]=p[i-1]+nc;	
			}
		}
	}
	return p;
}

unsigned int ** alloue_image_int(int nl, int nc)
{
	unsigned int **p; int i;
	p=(unsigned int**)calloc(nl,sizeof(*p));
	if (p==NULL) {
		return NULL;
	} else { 
		*p=(unsigned int*)calloc(nl*nc,sizeof(**p));
		if (*p==NULL) {
			free(p);
			return NULL;
		} else {
			for (i=1;i<nl;i++) {
				p[i]=p[i-1]+nc;	
			}
		}
	}
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



void calcul_cout(unsigned int* cout_final, unsigned char** energie, unsigned int**  pere, int nl, int nc)
{   


    int i, j, k;
    unsigned int** cout=NULL;
    cout=alloue_image_int(nl,nc);
    for (i=1;i<nl;i++) {
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
		chemin[i]=pere[i+1][chemin[i+1]];
	}
}



main(){
int i,a,j,nbcol=2;
unsigned char**im=alloue_image_char(6,7);
unsigned char**energie=alloue_image_char(6,7);
unsigned int*cout_final=calloc(7,sizeof(*cout_final));
unsigned int*chemin=calloc(6,sizeof(*chemin));
unsigned int**pere=alloue_image_int(6,7);
im[0][0]=195;
im[0][1]=196;
im[0][2]=196;
im[0][3]=197;
im[0][4]=197;
im[0][5]=197;
im[0][6]=197;
im[1][0]=184;
im[1][1]=187;
im[1][2]=189;
im[1][3]=191;
im[1][4]=192;
im[1][5]=193;
im[1][6]=194;
im[2][0]=183;
im[2][1]=184;
im[2][2]=185;
im[2][3]=86;
im[2][4]=187;
im[2][5]=187;
im[2][6]=188;
im[3][0]=173;
im[3][1]=174;
im[3][2]=62;
im[3][3]=143;
im[3][4]=174;
im[3][5]=176;
im[3][6]=178;
im[4][0]=172;
im[4][1]=169;
im[4][2]=137;
im[4][3]=99;
im[4][4]=157;
im[4][5]=174;
im[4][6]=176;
im[5][0]=178;
im[5][1]=188;
im[5][2]=173;
im[5][3]=193;
im[5][4]=176;
im[5][5]=180;
im[5][6]=180;

if ((7-a)==0) {printf("Trop de colonnes à supprimer"); exit(-1);}

for(a=0;a<nbcol;a++){

printf("%d itération\n",a+1);
printf("\n");
printf("\n");
printf("\n");
printf("image avant travail\n");
for(i=0;i<6;i++){
for(j=0;j<(7-a);j++){
printf("%hhu\t",im[i][j]);}
printf("\n");}
printf("\n");
printf("\n");
printf("\n");

energie=gradienty(energie,im,6,7-a);

printf("energie\n");
for(i=0;i<6;i++){
for(j=0;j<(7-a);j++){
printf("%hhu\t",energie[i][j]);}
printf("\n");}
printf("\n");
printf("\n");
printf("\n");

calcul_cout(cout_final, energie,pere,6,7-a);
printf("pere\n");
for(i=0;i<6;i++){
for(j=0;j<(7-a);j++){
printf("%d\t",pere[i][j]);}
printf("\n");}
printf("\n");
printf("\n");
printf("\n");

printf("cout final\n");
for(i=0;i<(7-a);i++){
printf("%d\t",cout_final[i]);}
printf("\n");
printf("\n");
printf("\n");
printf("\n");


trouve_chemin(chemin,pere,cout_final,6,7-a);
printf("chemin\n");
for(i=0;i<6;i++){
printf("%d\t",chemin[i]);}
printf("\n");
printf("\n");
printf("\n");
printf("\n");

supprime_colonne(im, chemin, 6,7-a);

printf("image\n");
for(i=0;i<6;i++){
for(j=0;j<(7-a);j++){
printf("%hhu\t",im[i][j]);}
printf("\n");}
printf("\n");
printf("\n");
printf("\n");
}
}



