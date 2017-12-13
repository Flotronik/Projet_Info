#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<SDL_phelma.h>

unsigned char** trace_chemin(unsigned char** im2, unsigned int* ch, int cl, int nl, int nc)  { int i;
  if (im2==NULL) im2=alloue_image_char(nl,nc);
  for(i=0; i<nl; i++) im2[i][ch[i]]=cl;
  return im2;
}
