#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  int *upstream,*downstream;
  char* res;
  
  pipe(upstream); pipe(downstream);
  
  if(fork() != 0){ //parent
    close(upstream[1]); close(downstream[0]);
    write(downstream,argv[1],1024);
    close(downstream[1]);
    int byread = read(upstream[0],res,1024);
    printf("Das Ergebnis ist: %s",res);
    close(upstream[0]);
    exit(0);
    
  } else { // child
    close(upstream[0]); close(downstream[1]);
    close(STDIN_FILENO); close(STDOUT_FILENO);
    dup2(downstream[0],STDIN_FILENO); dup2(upstream[1],STDOUT_FILENO);
    
    execl("/usr/bin/bc","/usr/bin/bc");
  }
}
