#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[])
{
	int p[2];
	int pid;
	char content;
	pipe(p);
	if (argc > 1) {
		fprintf(2, "error");
		exit(1);
	}
	if (fork() == 0) {
		pid = getpid();
		close(p[0]);
		printf("%d: received ping", pid);
		write(p[1],"0",1);
		close(p[1]);
	} else {
		pid = getpid();
		close(p[1]);
		read(p[0],&content,1);
		printf("%d: received pong", pid);
		close(p[0]);
	}
	exit(0);
}
