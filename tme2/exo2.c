#include "exo2.h"

void lance_commande(char* commande)
{
	int i=system(commande);
  	if(i==-1){
	    printf("error\n");
	}
}
