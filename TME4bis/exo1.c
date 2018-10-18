#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
  if(argc != 2){
    return -1;
  }
  int L = atoi(argv[1]);
  int i = 0;
  int p;
  while(i < L){
    if(p=fork()){
      if(fork()){
	if (i==0)
	  printf("%d\n",p);
	i=L;
	sleep(30);
      }else{
	i++;
      }
    }else{
      i++;
    }
  }
  return 0;
}
