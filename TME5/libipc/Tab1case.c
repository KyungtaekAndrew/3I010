/* Diffusion tampon 1 case */

  #include <stdio.h> 
  #include <unistd.h> 
  #include <stdlib.h> 
  #include <signal.h> 
  #include <libipc.h>

/************************************************************/

/* definition des parametres */ 

#define NE          2     /*  Nombre d'emetteurs         */ 
#define NR          5     /*  Nombre de recepteurs       */

/************************************************************/

/* definition des semaphores */

#define EMET 0
#define MUTEX 1

/************************************************************/

/* definition de la memoire partagee */

struct mem_{
  int x;
  int nblec;
} mem;

/************************************************************/

/* variables globales */ 
    int emet_pid[NE], recep_pid[NR]; 

/************************************************************/

/* traitement de Ctrl-C */ 

  void handle_sigint(int sig) { 
      int i;
      for (i = 0; i < NE; i++) kill(emet_pid[i], SIGKILL); 
      for (i = 0; i < NR; i++) kill(recep_pid[i], SIGKILL); 
      det_sem(); 
      det_shm((char *)p); 
  } 

/************************************************************/

/* fonction EMETTEUR */
void emetteur(int id, mem* p){
  while(1){
    int i=0;

    
    p->x--;
    if (p->x<=0){
      
  
    int i;
    for(i=0;i<NR;i++){
      V(recep_pid[i]);
    }
  }
  
}
	// A completer - contient les instructions executees
        // par un emetteur

/************************************************************/

/* fonction RECEPTEUR */ 
void recepteur(int id, mem * p){
  while(1){
    
    P(id);
    
    
  }
}
	// A completer - contient les instructions executees
        // par un recepteur

/************************************************************/

int main() { 
    struct sigaction action;
    /* autres variables (a completer) */
    
    setbuf(stdout, NULL);

/* Creation du segment de memoire partagee */
    
    mem* p = (mem*)init_shm(sizeof(mem));
    
/* creation des semaphores */ 

    creer_sem(NE);
    creer_sem(NR);
    
/* initialisation des semaphores */ 
    
    int i;
    int emet_pid
    for (i=0;i<NE;i++){
      emet_pid[i]=i;
    }
    for (i=0;i<NR;i++){
      recep_pid[i]=NE+i;
    }
    for(i = 0; i < NE; i++){
      int pid;
      if((pid=fork())==0){
	emetteur(i);
      }else{
	emet_pid = pid;
      }
    }
    for(i = 0; i < NR; i++){
      int pid;
      if((pid=fork())==0){
	recepteur(i);
      }else{
	recep_pid[i]=pid;
      }
    }
    
/* creation des processus emetteurs */
    
	// A completer - les pid des processus crees doivent
        // etre stockes dans le tableau emet_pid

/* creation des processus recepteurs */ 

	// A completer - les pid des processus crees doivent
        // etre stockes dans le tableau recep_pid

/* redefinition du traitement de Ctrl-C pour arreter le programme */ 

    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = handle_sigint;
    sigaction(SIGINT, &action, 0); 
    
    pause();                    /* attente du Ctrl-C  */
    return EXIT_SUCCESS;
} 
