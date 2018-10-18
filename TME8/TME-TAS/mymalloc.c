#include <stdio.h>
#include "affiche_tas.h"
#include <ctype.h>
#include <string.h>

int main(){
	tas_init();
	char *p1, *p2, *p3, *p4;
	p1 = (char *) tas_malloc(10);
	printf("%d\n",libre);
	p2 = (char *) tas_malloc(9);
	p3 = (char *) tas_malloc(5);
	p4 = (char *) tas_malloc(7);
	strcpy( p1, "tp 1" );
	strcpy( p2, "tp 2" );
	strcpy( p3, "tp 3" );
	strcpy( p4, "tp 4" );
	afficher_tas();
	return 0;
}
