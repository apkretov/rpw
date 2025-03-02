#undef LIN
#ifdef LIN

#define NAME_MAX 14 /* longest filename component; */ /* dsystem-dependent */
typedef struct { /* portable directory entry */
	long ino; /* inode number */
	char name[NAME_MAX+1]; /* name + '\0' terminator */
} Dirent;

typedef struct { /* minimal DIR: no buffering, etc. */
	int fd; /* file descriptor for the directory */
	Dirent d; /* the directory entry */
} DIR;

#include <stdio.h>
#include <string.h>
//ORIG #include "syscalls.h"
#include <fcntl.h> /* flags for read and write */
#include <sys/types.h> /* typedefs */
#include <sys/stat.h> /* structure returned by stat */
//ORIG #include "dirent.h"
void fsize(char *);

main(int argc, char **argv) { /* print file name */
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	if (argc == 1) /* default: current directory */
		 fsize(".");
	 else
		 while (--argc > 0)
			 fsize(*++argv);
	 return 0;
}

//ORIG int stat(char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));

void fsize(char *name) { /* fsize: print the name of file "name" */
	struct stat stbuf;
	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	printf("%8ld %s\n", stbuf.st_size, name);
}

int fstat(int fd, struct stat *);
DIR *opendir(char *dirname) { /* opendir: open a directory for readdir calls */
	int fd;
	struct stat stbuf;
	DIR *dp;
	if ((fd = open(dirname, O_RDONLY, 0)) == -1
		 || fstat(fd, &stbuf) == -1
		 || (stbuf.st_mode & S_IFMT) != S_IFDIR
		 || (dp = (DIR *) malloc(sizeof(DIR))) == NULL)
		return NULL;
	dp->fd = fd;
	return dp;
}

/*ORIG
#include <sys/dir.h> // local directory structure
Dirent *readdir(DIR *dp) { // readdir: read directory entries in sequence
	struct direct dirbuf; // local directory structure
	static Dirent d; // return: portable structure
	while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
		if (dirbuf.d_ino == 0) // slot not in use
			continue;
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZ);
		d.name[DIRSIZ] = '\0'; // ensure termination
		return &d;
	}
	return NULL;
}
*/

void closedir(DIR *dp) { /* closedir: close directory opened by opendir */
	if (dp) {
		close(dp->fd);
		free(dp);
	}
}

#define MAX_PATH 1024
void dirwalk(char *dir, void (*fcn)(char *)) { /* dirwalk: apply fcn to all files in dir */
	char name[MAX_PATH];
	Dirent *dp;
	DIR *dfd;
	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->name, ".") == 0
			 || strcmp(dp->name, ".."))
			continue; /* skip self and parent */
		if (strlen(dir)+strlen(dp->name)+2 > sizeof(name))
			fprintf(stderr, "dirwalk: name %s %s too long\n",
					  dir, dp->name);
		else {
			sprintf(name, "%s/%s", dir, dp->name);
			(*fcn)(name);
		}
	}
	closedir(dfd);
}
#endif
