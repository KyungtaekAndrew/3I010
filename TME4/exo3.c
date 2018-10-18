#include<stdio.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<sys/wait.h>
#include<sys/times.h>
#include<stdlib.h>
#include<unistd.h>

struct rusage usage;
struct timeval start, end;

int main (int argc, char *argv[]){
  int i = 0;
  pid_t *tab = (pid_t *)malloc((argc-2)*sizeof(pid_t));
  for(i = 2; i < argc; i++){
    if(fork() == 0){
      tab[i-2] = getpid();
      sleep(10);
      execl("/bin/grep", "grep", argv[1], argv[i], NULL);
      //execl("/bin/sleep     ","sleep(50)   ",NULL);
    }
  }
  for(i = 2; i < argc; i++){
    wait4(tab[i-2],NULL,0,&usage);
    printf("Ended at: %ld.%lds\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
  }
  return 0;
}
