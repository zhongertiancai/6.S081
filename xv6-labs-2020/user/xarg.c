#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]){
	char buf[MAXARG];
	char* myargv[MAXARG];
	int i = 0;
	int n;
	int args_index = 0;
	if (argc < 2) {
		fprintf(2, "lack of parameter\n");
		exit(1);
	}
	if (argc + 1 > MAXARG) {
		fprintf(2, "args have been filled up\n");
		exit(1);
	}
	for (i = 1; i < argc; i++) {
		myargv[args_index++] = argv[i];//skip the xarg
	}
	while ((n = read(0, buf, 1024)) > 0) {
		if (fork() == 0) {
			char *arg = (char*) malloc(sizeof(buf));
			int index = 0;
			for (i = 0; i < n; i++) {
				if (buf[i] == ' ' || buf[i] == '\n') {
					arg[index] = 0;
					myargv[args_index++] = arg;
					index = 0;
					arg = (char*) malloc(sizeof(buf));
				}
				else {
					arg[index++] = buf[i];
				}
			}
			arg[index] = 0;
			myargv[args_index] = 0;
			exec(myargv[0], myargv);
		} else {
			wait(0);
		}
	}
	exit(0);
}