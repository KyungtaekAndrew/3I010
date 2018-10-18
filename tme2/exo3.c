#include "exo2.h"

struct timeval tdeb, tdef;

void lance_commande(char* commande)
{
	gettimeofday(&tdeb,NULL);
	int i=system(commande);
  	if(i==-1){
	    printf("error\n");
	}
	gettimeofday(&tdef,NULL);
	printf("commande %s %lf\n",commande,(tdef.tv_sec-tdeb.tv_sec)+1e-6*(tdef.tv_usec-tdeb.tv_usec));
}
