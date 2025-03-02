#undef LIN
#ifdef LIN
#include <stdio.h>
#include <stdlib.h>
#define NULL_ 0 
#define BUFSIZE 512 
#define PMODE 0644/*rw for owner,r for group,others*/ 

static int error(s1,s2) /*print error message and die*/ 
char* s1, s2; 
{ 
    printf(s1,s2); 
    printf("\n"); 
    exit(1); 
}

int main(argc,argv) /*cp: copy f1 to f2*/ 
int argc; 
char *argv[]; 
{ 
    printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

    int f1, f2, n; 
    char buf[BUFSIZE]; 

    if (argc != 3) 
        error("usage:cp from to", NULL_); 
    if ((f1=open(argv[1],0))== -1) 
        error("cp:can't open %s", argv[1]); 
    if ((f2=creat(argv[2],PMODE))== -1) 
        error("cp: can't create %s", argv[2]); 
    while ((n=read(f1,buf,BUFSIZE))>0) 
        if (write(f2,buf,n) !=n) 
            error("cp: write error", NULL_); 
    exit(0); 
} 
#endif

#undef UNLINK // unlink | Программирование на C и C++ @ http://www.c-cpp.ru/content/unlink
#ifdef UNLINK

#include <stdio.h>
//ORIG #include <dos.h>

#undef LIN // Linux
#define WIN // Windows
#ifdef LIN
#include <unistd.h> //MINE unlink(2) - Linux man page @ https://linux.die.net/man/2/unlink
#define ARGC 5
#elif defined WIN
#include <io.h> // _unlink, _wunlink | Microsoft Docs @ https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2010/1c3tczd6(v=vs.100)?redirectedfrom=MSDN
#define unlink _unlink // unlink is not unix-specific @ https://stackoverflow.com/questions/2192415/unlink-vs-remove-in-c
#define ARGC 4
#endif

int main(int argc, char* argv[]) { // Следующая программа удаляет файл, указанный в качестве первого аргумента командной строки:
    printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

    if (argc == ARGC) {
        if (unlink(argv[1]) == -1) // unistd.h // unlink(2) - Linux man page @ https://linux.die.net/man/2/unlink
            printf("Cannot remove file with unlink.\n");
#ifdef LIN
        if (rmdir(argv[2]) == -1) // unistd.h // rmdir(2): delete directory - Linux man page @ https://linux.die.net/man/2/rmdir
            printf("Cannot remove directory with rmdir.\n");
#endif
        if (remove(argv[3]) == -1) // stdio.h // It calls unlink(2) for files, and rmdir(2) for directories. // remove(3): remove file/directory - Linux man page @ https://linux.die.net/man/3/remove
            printf("Cannot remove file with remove.\n");
        if (remove(argv[4]) == -1)
            printf("Cannot remove directory with remove.\n");
    }
    else
        printf("Enter %d arguments.\n", ARGC - 1);

    (void)getchar();
    return 0;
}
#endif