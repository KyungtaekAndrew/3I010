#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define STR_SIZE 255

int main(){
  char str[STR_SIZE];
  char ajout[STR_SIZE];
  int taille;

  while(1){
    fgets(str,STR_SIZE,stdin);
    strcpy(ajout,"/bin/");
    if (strcmp(str,"quit\n")==0)
      break;
    taille=strlen(str);
    str[taille-1]='\0';
    if (str[taille-2]=='&'){
      str[taille-2]='\0';
      if (!fork()){
	strcat(ajout,str);
	execl(ajout,str,NULL);
      }
    }else{
      if(!fork()){
	strcat(ajout,str);
	execl(ajout,str,NULL);
      }else{
	wait(NULL);
      }
    }
  }
  return 0;
}
