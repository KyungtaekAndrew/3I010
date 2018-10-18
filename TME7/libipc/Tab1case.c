/* Diffusion tampon 1 case */

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <libipc.h>

/************************************************************/

/* definition des parametres */ 

#define NE          3     /*  Nombre d'emetteurs         */ 
#define NR          5     /*  Nombre de recepteurs       */

/************************************************************/

/* definition des semaphores */

#define EMET 0
#define MUTEX 1

int RECEP[NR]={2,3,4,5,6};

/************************************************************/

/* definition de la memoire partagee */

typedef struct _mem {
  int x;
  int nb_recep;
} mem;

mem* sp;

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
  det_shm((char *)sp); 
} 

/************************************************************/

/* fonction EMETTEUR */

void emetteur(int id){
  while(1){
    printf("Emetteur %d bloque\n",id);
    P(EMET);
    printf("Emetteur %d libere\n",id);
  }
}
	

/************************************************************/
  
/* fonction RECEPTEUR */ 

void recepteur(int id){
  int i;
  while(1){
    printf("Recepteur %d commence\n",id);
    P(MUTEX);
    sp->nb_recep++;
    if (sp->nb_recep==NR){
      for (i=0;i<NR;i++){
	V(RECEP[i]);
      }
      printf("Je libere tout le monde\n");
      sp->nb_recep=0;
    }
    V(MUTEX);
    P(RECEP[id]);
    printf("Recepteur %d fini\n",id);
    V(EMET);
  }
}


/************************************************************/

int main() { 
  struct sigaction action;
  /* autres variables (a completer) */
    
  setbuf(stdout, NULL);

  /* Creation du segment de memoire partagee */
  
  sp = (mem *)init_shm(sizeof(mem));
  sp->x=0;
  sp->nb_recep=0;
    
  /* creation des semaphores */ 

  creer_sem(2+NR);
    
  /* initialisation des semaphores */ 
    
  init_un_sem(EMET,1);
  init_un_sem(MUTEX,1);
  int i;
  for (i=0;i<NR;i++){
    init_un_sem(RECEP[i],0);
  }

    
  /* creation des processus emetteurs */

  int pid;
  for(i = 0; i < NE; i++){
    if((pid=fork())==0){
      emetteur(i);
    }else{
      emet_pid[i] = pid;
    }
  }
    
  /* creation des processus recepteurs */ 

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
    
  pause();                    /* attente du Ctrl-C  */
  return EXIT_SUCCESS;
} 
