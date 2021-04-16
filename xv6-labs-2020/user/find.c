#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char origin[512];

char* filename(char *path) {
	static char buf[DIRSIZ+1];
	char* p;
	for (p = path + strlen(path); p >= path && *p != '/'; p--) 
		;
	p++;
	memmove(buf, p, strlen(p));
	buf[strlen(p)] = '\0';
	return buf;
}


void find(char* path, char* file) {
	char buf[512], *p;
  	int fd;
 	struct dirent de;
 	struct stat st;
	int i = 0;
	int len = strlen(path);
 	if ((fd = open(path, 0)) < 0) {
 		fprintf(2, "find : cannot open %s\n", path);
 		return;
 	}
 	if (fstat(fd, &st) < 0) {
 		fprintf(2, "find : cannot stat %s\n", path);
 		close(fd);
 		return;
 	}
 	switch(st.type) {
 		case T_FILE:
 			if (strcmp(file, filename(path)) == 0) {
 				//printf("%s", filename(path));
 			}
 			break;
 		case T_DIR:
 			strcpy(buf, path);
 			p = buf + strlen(buf);
 			*p++ = '/';
 			while (read(fd, &de, sizeof(de)) == sizeof(de)) {
 				if (de.inum == 0) {
 					continue;
 				}
 				//printf("%s\n",de.name);
 				if (strcmp(de.name, ".") != 0 && strcmp(de.name, "..") != 0) {
 					//printf("%s\n",de.name);
 					i = 0;
 					p = buf + len;
 					*p++ = '/';
 					while (de.name[i] != '\0') {
 						*p++ = de.name[i++];
 					}
 					*p++ = '\0';
 					//printf("%s ,%s" ,buf , file);

 					//printf("%s\n",buf);
 					find(buf, file);
 				}
 				if (strcmp(file, de.name) == 0) {
 					//printf("%s\n", de.name);
 					printf(path);
 					printf("/");
 					printf(de.name);
 					printf("\n");
 				}
 			}
 			break;
 	}
 	close(fd);
}



int main(int argc, char *argv[])
{

	strcpy(origin, argv[1]);
	find(argv[1], argv[2]);
	exit(0);
}
