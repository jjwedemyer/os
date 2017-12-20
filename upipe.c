#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* The index of the "read" end of the pipe */
#define READ 0

/* The index of the "write" end of the pipe */
#define WRITE 1
#define MAX_LENGTH 80

int main(int argc, char const *argv[])
{
	if(argc < 2)
		return EXIT_FAILURE;
	int fd[2], bytesRead;
	char* string, *readfrom;

	pipe(fd);

	if(fork() != 0){
		string = strndup(argv[1], MAX_LENGTH*sizeof(char));
		close(fd[READ]);
		write(fd[WRITE], string, MAX_LENGTH);
		close(fd[WRITE]);
	} else {
		close(fd[WRITE]);
		bytesRead = read(fd[READ],readfrom,MAX_LENGTH);
		printf("READ %d Bytes: %s\n",bytesRead,readfrom);
		close(fd[READ]);
	}
	return 0;
}