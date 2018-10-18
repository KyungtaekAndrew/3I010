#include "exo2.h"

int main(int argc, char** argv){
	int i; 
	for(i=1; i<argc;i++){
		lance_commande(argv[i]);
	}
	return 1;
}
