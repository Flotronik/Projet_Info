#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL_phelma.h>
#include "projet.h"


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
	
	
