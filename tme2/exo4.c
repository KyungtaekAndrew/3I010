#include "exo2.h"

#define TICK ((double)sysconf(_SC_CLK_TCK))

struct tms tdef, tdeb;
clock_t t1,t2;

void lance_commande(char* commande)
{
	t1=times(&tdeb);
	int i=system(commande);
  	if(i==-1){
	    printf("error\n");
	}
	t2=times(&tdef);
	
	printf("Statistiques de \"%s\"\n",commande);
	printf("Temps total : %f\n",(double)((t2-t1)/TICK));
	printf("Temps utilisateur : %f\n",(double)(tdef.tms_utime-tdeb.tms_utime));
	printf("Temps systeme : %f\n",(double)(tdef.tms_stime-tdeb.tms_stime));
	printf("Temps util. fils : %f\n",(double)(tdef.tms_cutime-tdeb.tms_cutime));
	printf("Temps sys.fils : %f\n",(double)(tdef.tms_cstime-tdeb.tms_cstime));

}
