#include <stdio.h>
#include "affiche_tas.h"
#include <ctype.h>

void afficher_tas(){
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 16; j++) { 
	    printf("%4d", j + 16*i);
        }
        printf("\n");
        for (j = 0; j < 16; j++) { 
	    printf("%4d", tas[j + 16*i]);
        }
        printf("\n");
        for (j = 0; j < 16; j++) { 
	    if (isalnum(tas[j + 16*i])) {
	        printf("%4c", tas[j + 16*i]);
	    } else {
		printf("    ");
	    }
        }
        printf("\n\n");
    }
    printf("---------------------------------------------------------------\n\n");
}

void tas_init(){
  libre = 0;
  tas[0] = TAILTAS;
  tas[1] = -1;
}

int first_fit(int taille, int* prec){
  int p=libre;
  while ((tas[p+1]!=-1)&&(tas[p]<taille)){
    *prec=p;
    p=tas[p+1];
  }
  return p;
}

/*
int first_fit(int taille, int* prec){
  int actuel=libre;
  int precedent=-1;
  while (true){
    if(tas[actuel] >= taille){
      
      *prec=precedent;
      return actuel;
    } else {
      precedent=actuel;
      actuel=tas[actuel+1];
    }
  }
}
*/

char *tas_malloc(unsigned int taille){
  int p, prec;
  p = first_fit(taille, &prec);
  if (p==-1){
    return NULL;
  }
  if(p==libre){
    if (tas[p]==taille+1 || tas[p] == taille){
      libre = tas[p+1];
      return &tas[p+1];
    } else {
      libre=p+taille+1;
	  tas[p+taille+1]=tas[p]-(taille+1);
      tas[p]=taille;
      tas[p+taille+2]=tas[p+1];
      return &tas[p+1];
    }
  }else{
    if (tas[p]==taille+1 || tas[p] == taille){
		tas[prec+1] = tas[p+1];
    	return &tas[p+1];
    }else {
		tas[p+taille+1]=tas[p]-(taille+1);
    	tas[p]=taille;
    	tas[p+taille+2]=tas[p+1];
		tas[prec+1] = tas[p+taille+2];
    	return &tas[p+1];
    }
  }
}

int tas_free(char *ptr){
	int prec;
	int actuel=libre;
	int taille=tas[(*ptr)-1];
	if (libre>(*ptr)-1){
		if ((*ptr)+taille==libre){
			tas[(*ptr)-1]=taille+tas[libre];
		}
		tas[*ptr]=tas[libre+1];
		libre=(*ptr)-1;
		int i;
		for(i = 0; i < tas[*ptr-1]; i++){
			tas[*ptr + i] = 0;
		}
		return 0;
	}
	while (actuel < (*ptr)-1){
		prec=actuel;
		actuel=tas[actuel+1];
	}
	fusion_gauche(prec, *ptr -1);
	fusion_droite(*ptr-1, actuel);
	return 0;
}


int fusion_gauche(char *avant, char*actuel){
	if (*avant+tas[*avant]+1==*actuel){
		tas[*avant]+=tas[*actuel]+1;
		return 1;
	}
	return 0;
}

int fusion_droite(char *actuel, char* apres){
	if ( *actuel+tas[*actuel]+1==*apres ){	
		tas[*actuel]+=tas[*apres]+1;
		return 1;
	}
	return 0;
}

