/* Diffusion tampon N case */

  #include <stdio.h> 
  #include <unistd.h> 
  #include <signal.h> 
  #include <libipc.h>

/************************************************************/

/* definition des parametres */ 

  #define NE          2     /*  Nombre d'emetteurs         */ 
  #define NR          5     /*  Nombre de recepteurs       */ 
  #define NMAX        3     /*  Taille du tampon           */ 

/************************************************************/

/* definition des semaphores */ 

#define EMET 0
#define MUTEX 1

int RECEP[NR]={2,3,4,5,6};
int TABEM[NMAX]={7,8,9};

/************************************************************/

/* definition de la memoire partagee */ 

typedef struct _mem {
  int x[NMAX];
  int nb_recep[NMAX];
int ir[NR];
int ie;
} mem;

mem* sp;

/************************************************************/

/* variables globales */ 
    int emet_pid[NE], recep_pid[NR]; 

/************************************************************/

/* traitement de Ctrl-C */ 

  void handle_sigint(int sig) 
  { int i;
  	for (i = 0; i < NE; i++) kill(emet_pid[i], SIGKILL); 
	for (i = 0; i < NR; i++) kill(recep_pid[i], SIGKILL); 
	det_sem(); 
	det_shm((char *)sp); 
 
  } 

/************************************************************/

/* fonction EMETTEUR */ 

	// A completer - contient les instructions executees
        // par un emetteur

void emetteur(int id){
  while(1){

	int i,I;
	P(MUTEX);
	I=sp->ie;
	sp->ie=(sp->ie+1)%NMAX;
	V(MUTEX);
	P(TABEM[I]);
	sp->nb_recep[I]=0;
	printf("emetteur %d a ecrit dans la case %d, nb recep est %d	\n",id,I,sp->nb_recep[I]);
	for (i=0;i<NR;i++){
		V(RECEP[i]);
	}
	//ecrire;


  }
}

/************************************************************/

/* fonction RECEPTEUR */ 

	// A completer - contient les instructions executees
        // par un recepteur

void recepteur(int id){
  while(1){

	P(RECEP[id]);
	int J;
	P(MUTEX);
	J=sp->ir[id];
	sp->ir[id]=(sp->ir[id]+1)%NMAX;
	sp->nb_recep[J]++;
	printf("recepteur %d a lu dans la case %d, nb_recep=%d\n",id,J,sp->nb_recep[J]);
	if(sp->nb_recep[J] == NR){
		printf(" tous les recepteur ont lu la case de %d\n",J);
		V(TABEM[J]);		
	}
	V(MUTEX);


  }
}

/************************************************************/

int main() { 
    struct sigaction action;
    /* autres variables (a completer) */
    
    setbuf(stdout, NULL);

/* Creation du segment de memoire partagee */

	// A completer
  sp = (mem *)init_shm(sizeof(mem));
int i;
for (i=0;i<NMAX;i++){
  sp->x[i]=0;
  sp->nb_recep[i]=0;
}
for (i=0;i<NR;i++){
  sp->ir[i]=0;
}
sp->ie=0;

/* creation des semaphores */ 

	// A completer
  creer_sem(2+NR+NMAX);

/* initialisation des semaphores */ 
    
	// A completer
    
  init_un_sem(EMET,1);
  init_un_sem(MUTEX,1);
  for (i=0;i<NR;i++){
    init_un_sem(RECEP[i],0);
  }
  for (i=0;i<NMAX;i++){
    init_un_sem(TABEM[i],1);
  }

    
/* creation des processus emetteurs */ 

	// A completer - les pid des processus crees doivent
        // etre stockes dans le tableau emet_pid

  int pid;
  for(i = 0; i < NE; i++){
    if((pid=fork())==0){
      emetteur(i);
    }else{
      emet_pid[i] = pid;
    }
  }

/* creation des processus recepteurs */ 

	// A completer - les pid des processus crees doivent
        // etre stockes dans le tableau recep_pid

  for(i = 0; i < NR; i++){
    if((pid=fork())==0){
      recepteur(i);
    }else{
      recep_pid[i]=pid;
    }
  }
    
/* redefinition du traitement de Ctrl-C pour arreter le programme */ 

    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = handle_sigint;
    sigaction(SIGINT, &action, 0); 

    pause();                     /* attente du Ctrl-C */
    return EXIT_SUCCESS;
} 
