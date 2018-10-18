#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<sys/wait.h>
#include<sys/times.h>
#include<sys/time.h>

#define STR_SIZE 255

int main(){
  char str[STR_SIZE];
  char ajout[STR_SIZE];
  char* arg[10];
  int taille;
  const char s[2] = " ";
  char *token;
  pid_t *tab = (pid_t *)malloc((argc-2)*sizeof(pid_t));
  while(1){
    int i = 0;
    fgets(str,STR_SIZE,stdin);
    strcpy(ajout,"/bin/");
    if (strcmp(str,"quit\n")==0)
      break;
    taille=strlen(str);
    str[taille-1]='\0';
    if (str[taille-2]=='&'){
      str[taille-2]='\0';
      if (!fork()){
	token = strtok(str,s);
	while(token != NULL){
	  arg[i] = (char*)malloc(sizeof(char)*strlen(token));
	  strcpy(arg[i],token);
	  token = strtok(NULL, s);
	  i++;
	}
	arg[i] = NULL;
	strcat(ajout,arg[0]);
	 execv(ajout,arg);

      }
    }else{
      if(!fork()){
	token = strtok(str,s);
	while(token != NULL){
	  arg[i] = (char*)malloc(sizeof(char)*strlen(token));
	  strcpy(arg[i],token);
	  token = strtok(NULL, s);
	  i++;
	};
	  arg[i] = NULL;
	  strcat(ajout,arg[0]);
	  execv(ajout,arg);
      }else{
	wait(NULL);
      }
    }
  }
  return 0;
}
