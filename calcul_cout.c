#include <stdio.h>

void calcul_cout(unsigned int* cout_final, unsigned char** energie, unsigned int**  pere, int nl, int nc)
{   
	/*unsigned char** energie=NULL;
	energie=alloue_image_char(nl,nc);
	energie[0][0]=1;    
	energie[0][1]=1;  
	energie[0][2]=1;  
	energie[1][0]=7;  
	energie[1][1]=5;  
	energie[1][2]=4;  
	energie[2][0]=4;  
        energie[2][1]=2;  
        energie[2][2]=98; */ 

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
	    //printf("i=%d\n",i);
	    for (j=0;j<nc;j++) {
	    	    //printf("j=%d\n",j);
		    for (k=-1;k<2;k++) {
			    //printf("k=%d\n",k);
			    //printf("coutk=%d\n",cout[i-1][j+k]);
			    //printf("energiek=%d\n",energie[i-1][j+k]);
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


	
