#include<stdio.h>
#define MAXFILS 2

int main (int argc, char *argv[]){
  int i = 0;
  while(i < argc - 2){
    if(i >= MAXFILS)
      wait();
    if(fork() == 0){
      execl("/bin/grep", "grep", argv[1], argv[i+2], NULL);
    }
    i++;
  }
  for(i = 0; i<MAXFILS;i++){
    wait();
  }
  return 0;
}


