#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void operate(int p[2]) {
	//the first
	int pp[2];
	pipe(pp);
	int first;
	int after;
	int status;
	int flag = 0;
	int next = 2;
	int count = 0;
	int terminal = 0;
	next = read(p[0], &first, sizeof(int));
	if (next <= 0) {
		exit(0);
	}

	//printf("child exist\n");
	if (fork() != 0) {
		while (1) {
			count=count+1;
			//printf("has read%d\n",count);
			if (flag == 0) {
				terminal = next;
				if (terminal <= 0) {
					break;
				}
				printf("prime %d\n", first);
				flag = 1;
			}
			terminal = read(p[0], &after, sizeof(int));
			if (terminal <= 0) {
					break;
			}
			if (after % first != 0) {
				write(pp[1], &after, sizeof(int));
			}
		}
		close(p[0]);
		close(pp[1]);
		wait(&status);
		exit(0);
	} else{
		close(pp[1]);
		operate(pp);
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	int status;
	if (argc > 1) {
		exit(1);
		fprintf(2, "Parameter error!");
	}
	int p[2];
	pipe(p);
	int i;

	if (fork() == 0) {
		close(p[1]);
		operate(p);
	} 
	else {
		close(p[0]);
		for (i = 2; i <= 35; i++) {
			write(p[1],&i,sizeof(int));
		}
		//printf("parent write done\n");
		close(p[1]);
		wait(&status);
		exit(0);
	}
	exit(0);
}
