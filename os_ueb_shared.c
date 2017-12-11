#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int* mem;
	// create shared mem seg
	int addy = shmget(IPC_PRIVATE, sizeof(int)*2, IPC_CREAT | 0777 | IPC_EXCL);
	// fork,
	mem = (int*)shmat(addy, NULL, 0);
	if(fork() != 0){
		while(1){
		if(mem[0] == 0){
			mem[1] = rand();
			mem[0] = 1;
		}
	}
	} else {
		while(1){
		if(mem[0] == 1){
			printf("%d",mem[1]);
			mem[0] = 0;
		}
		}
	}
	return 0;
}