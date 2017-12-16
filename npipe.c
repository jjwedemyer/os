#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	if(argc != 2)
		return 1;
	char* pipe = argv[1];
	char c;
	int fd = open(pipe,0666);
	while(1){
		read(fd, c, sizeof(char));
		printf("%c",c);
	}

	return 0;
}