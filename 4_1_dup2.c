#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
  if(argc != 2)
    return EXIT_FAILURE;
  int fd;
  fd = open(argv[1], O_WRONLY | O_CREAT, S_IRWXU);
  close(fd);
  dup2(fd,STDOUT_FILENO);
  printf("lolxd\n");
  return 0;
}