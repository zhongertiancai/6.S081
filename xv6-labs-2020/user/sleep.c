#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
//argc number , argv content
int main(int argc, char *argv[]){
	if (argc <= 1) {
		fprintf(2,"require a number");
		exit(1);
	}
	int time;
	time = atoi(argv[1]);
	sleep(time);
	exit(0);
	return 0;
}
