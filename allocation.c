#include <stdio.h>

unsigned char ** alloue_image_char(int nl, int nc)
{unsigned char **p;
p=(unsigned char**)malloc(nl,sizeof(*p));
if (p==NULL)
	return NULL;
else 
	{*p=(unsigned char*)malloc(nl*nc,sizeof(**p));
	if (*p==NULL)
		{free(p);
		return NULL;
		}
	else
		for (i=1;i<nl;i++)
			p[i]=p[i-1]+nc;	
	}
return p;
}

unsigned int ** alloue_image_int(int nl, int nc)
{unsigned int **p;
p=(unsigned int**)malloc(nl,sizeof(*p));
if (p==NULL)
	return NULL;
else 
	{*p=(unsigned int*)malloc(nl*nc,sizeof(**p));
	if (*p==NULL)
		{free(p);
		return NULL;
		}
	else
		for (i=1;i<nl;i++)
			p[i]=p[i-1]+nc;	
	}
return p;
}

void libere_image(unsigned int** im)
{free(im);
}
	
