#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


void sighandler(int sig){
	if(sig == SIGUSR1){
		return;
	} else exit(EXIT_FAILURE);
}
int main(int argc, char const *argv[])
{
	//find key;
	key_t test = 10;
	int addy = -1;
	printf("oi\n");
	do{
		printf("oii %d\n",test);
		test++;
		addy = shmget(test, 1024*sizeof(char), IPC_CREAT | 0777);
	} while(addy == -1);
	printf("KEY: %d\n",test);
	// get mem;
	char *line = shmat(addy, NULL, 0);
	signal(SIGUSR1,sighandler);
	while(1){
		printf("%s",line);
		pause();
		
	}
	return 0;
}