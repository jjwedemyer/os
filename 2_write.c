#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
	if(argc != 4)
		exit(EXIT_FAILURE);
	pid_t read_pid = (pid_t) atoi(argv[1]);
	key_t seg_key = (key_t) atoi(argv[2]);
	FILE* fp = fopen(argv[3],"r");
	printf("opened\n");
	int mem = shmget(seg_key, 1024*sizeof(char), 0777);
	printf("mem: %d errno: %d",mem, errno);
	char* line = shmat(mem, NULL, 0);
	printf("line: %s\n",line);

	// read from file and write to shared mem
	while(1){
		if(fgets(line, 1024, (FILE *)fp) != NULL)
			printf("%s",line);
		if(feof(fp))
			break;
		kill(read_pid, SIGUSR1);
		sleep(1);
	}

	return 0;
}
