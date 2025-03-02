#undef LIN
#ifdef LIN
#undef ON
#ifdef ON

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max #files open at once */

typedef struct _iobuf {
	int cnt; // characters left
	char *ptr; // next character position
	char *base; // location of buffer
	int flag; // mode of file access
	int fd; // file descriptor
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags {
	_READ = 01, /* file open for reading */
	_WRITE = 02, /* file open for writing */
	_UNBUF = 04, /* file is unbuffered */
	_EOF = 010, /* EOF has occurred on this file */
	_ERR = 020 /* error occurred on this file */
};

FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr */
								{ 0, (char *) 0, (char *) 0, _READ, 0 },
								{ 0, (char *) 0, (char *) 0, _WRITE, 1 },
								{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
							 };

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) ((p)->flag & _EOF) != 0)
#define ferror(p) ((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p))
#define getchar() getc(stdin)
#define putcher(x) putc((x), stdout)

#include <fcntl.h>
//ORIG #include "syscalls.h"
#define PERMS 0666 /* RW for owner, group, others */

FILE *fopen(char *name, char *mode) {
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break; /* found free slot */
	if (fp >= _iob + OPEN_MAX) /* no free slots */
		return NULL;

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);

	if (fd == -1) /* couldn't access name */
		return NULL;

	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;

	return fp;
}

//ORIG #include "syscalls.h"
int _fillbuf(FILE *fp) { // _fillbuf: allocate and fill input buffer
	int bufsize;

	if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) //ORIG: if ((fp->flag & (_READ | _EOF_ERR)) != _READ) // c - k&r fopen and fillbuf - Stack Overflow @ https://stackoverflow.com/questions/50598201/kr-fopen-and-fillbuf
		return EOF;

	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL) /* no buffer yet */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF; /* can't get buffer */

	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}

	return (unsigned char) *fp->ptr++;
}
#endif //ON

#define EX_8_03 // Solution by anonymous @ https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_8:Exercise_3#Solution_by_anonymous
#ifdef EX_8_03

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*
	 Exercise 8-3. Design and write _flushbuf, fflush, and fclose.
*/

#ifdef NULL
	 #undef NULL
#endif

typedef struct _iobuf
{
	 int cnt;    // characters left
	 char *ptr;  // next character position
	 char *base; // location of buffer
	 int flag;   // mode of file access
	 int fd;     // file descriptor
} FILE;

enum _flags {
	 _READ = 01,  // file open for reading
	 _WRITE = 02, // file open for writing
	 _UNBUF = 04, // file is unbuffered
	 _EOF = 010,  // EOF has occurred on this file
	 _ERR = 020   // error occurred on this file
};

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 // max #files open at once
#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

extern FILE _iob[OPEN_MAX];
int _fillbuf(FILE *fp);
int _flushbuf(int c, FILE *fp);
void error(char *msg);

#define feof(p) (((p)->flag & _EOF) == _EOF)
#define ferror(p) (((p)->flag & _ERR) == _ERR)
#define fileno(p) ((p)->fd)
#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)
#define PERMS 0666 // RW for owner, group, others
#define MAXERRORMSG 1000

FILE _iob[OPEN_MAX] = // stdin, stdout, stderr
{
	 { 0, (char *) 0, (char *) 0, _READ, 0 },
	 { 0, (char *) 0, (char *) 0, _WRITE, 1 },
	 { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};
FILE *fopen(char *name, char *mode);
int fflush(FILE *fp);
int fclose(FILE *fp);

int main(int argc, char *argv[]) {
	 printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	 int c;
	 char msg[MAXERRORMSG];
	 FILE *fpIn, *fpOut = stdout; // fpOut == stdout for usage 1 and 2
	 if (argc == 1) // read from stdin and write to stdout
		  fpIn = stdin;
	 else if (argc == 2) { // read from file and write to stdout
		  if ((fpIn = fopen(*++argv, "r")) == NULL)
				error(strcat(strcat(msg, "error: couldn't open file "), *argv)); // the double strcat adds "error..." to msg and then filename to msg after "error..." string
	 } else if (argc == 3) { // read from file1 and write to file2
		  if ((fpIn = fopen(*++argv, "r")) == NULL)
				error(strcat(strcat(msg, "error: couldn't open file "), *argv));
		  if ((fpOut = fopen(*++argv, "w")) == NULL)
				error(strcat(strcat(msg, "error: couldn't create/write to file "), *argv));
	 } else
		  error("usage 1: ./mystdio\nusage 2: ./mystdio input_file\nusage 3: ./mystdio intputfile outputfile");

	 while ((c = getc(fpIn)) != EOF) // read from fpIn and write to fpOut
		  putc(c, fpOut);
	 fclose(fpIn); // close the file since reached EOF. It is fine if it is stdin since exiting
	 fclose(fpOut); // close the file since reached EOF.  It is fine if it is stdout since exiting
	 exit(0);
}

FILE *fopen(char *name, char *mode) { // opens file. Returns NULL if could not open file/bad mode provided, otherwise returns file ptr
	 int fd;
	 FILE *fp;

	 if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		  return NULL;
	 for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		  if ((fp->flag & (_READ | _WRITE)) == 0) // if both _READ and _WRITE bits not set
				break;
	 if (fp >= _iob + OPEN_MAX) // no free slots
		  return NULL;

	 if (*mode == 'w')
		  fd = creat(name, PERMS);
	 else if (*mode == 'a') {
		  if ((fd = open(name, O_WRONLY, 0)) == -1)
				fd = creat(name, PERMS);
		  lseek(fd, 0L, 2);
	 } else
		  fd = open(name, O_RDONLY, 0);
	 if (fd == -1) // couldn't access name
		  return NULL;
	 fp->fd = fd;
	 fp->cnt = 0;
	 fp->base = NULL;
	 fp->flag = (*mode == 'r') ? _READ : _WRITE; // remove all flags and set only _READ or _WRITE
	 return fp;
}

int _fillbuf(FILE *fp) { // allocate and fill input buffer. If error or EOF, return EOF, otherwise return next char in buffer
	 if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) // if _READ is not set or _EOF or _ERR is set
		  return EOF; // only _READ should be set out of those three. Return EOF
	 int bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ; // get buffer size
	 if (fp->base == NULL) // no buffer yet
		  if ((fp->base = (char *) malloc(bufsize)) == NULL) // create buffer
				return EOF; // failed to create buffer, return EOF
	 fp->ptr = fp->base; // reset ptr to base since all chars in buffer have already been read
	 fp->cnt = read(fp->fd, fp->ptr, bufsize); // store number of chars read from fd in cnt. Overwrite buffer with up to bufsize number of chars in buffer pointed to by ptr
	 if (--fp->cnt < 0) { // if cnt - 1 is less than 0
		  if (fp->cnt == -1) // if == -1, reached EOF
				fp->flag |= _EOF; // turn on _EOF bit
		  else
				fp->flag |= _ERR; // if < -1, error occurred turn on _ERR bit
		  fp->cnt = 0; // reset number to indicate no chars left without having negative number
		  return EOF;
	 }
	 return (unsigned char) *fp->ptr++; // if read was successful, return char read from input
}

int _flushbuf(int c, FILE *fp) { // calls fflush to write unread buffered data to output. Stores char in new buffer. Returns EOF if error, otherwise 0
	 if (fp == NULL)
		  return EOF; // invalid pointer provided
	 else if (fflush(fp) == EOF)
		  return EOF; // an error occured in fflush
	 *fp->ptr++ = (char) c; // store provided char in buffer. Make sure to cast to the int to char since buffer is based on size of char
	 fp->cnt--; // update the counter for the number of chars that can fit in the buffer (just stored one)
	 return 0;
}

int fflush(FILE *fp) { // if fp is write FILE, writes unwritten buffer to output. if fp == NULL, flushes all write FILES. Returns EOF if error or read FILE provided, otherwise 0.
	 if (fp == NULL) { // if fp == NULL, then flush all buffers
		  int result = 0;
		  for (int i = 0; i < OPEN_MAX; i++) // go through all FILEs in _iob. Can't intelligently break from loop early since an older FILE can be closed before a newer one
				if (((&_iob[i])->flag & _WRITE) == _WRITE && fflush(&_iob[i]) == EOF) // if _WRITE flag set, flush it. Also, if fflush returns error, update result
					 result = EOF;
		  return result; // if any error occurred, return EOF, otherwise return 0
	 } else if (fp < _iob || fp >= _iob + OPEN_MAX)
		  return EOF; // invalid pointer provided
	 else if ((fp->flag & (_WRITE | _ERR | _READ)) != _WRITE) // if _WRITE is not set or _ERR or _READ is set.
		  return EOF; // only _WRITE should be set out of those three. Return EOF

	 int bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ; // get buffer size
	 if (fp->base == NULL) { // no buffer yet so nothing to flush. Create buffer to store provided char
		  if ((fp->base = (char *) malloc(bufsize)) == NULL) {
				fp->flag |= _ERR; // turn on _ERR bit
				return EOF; // malloc failed to allocate a buffer
		  }
	 } else { // buffer exists, so write contents to file
		  int n = fp->ptr - fp->base; // gets number of characters in buffer
		  if (write(fp->fd, fp->base, n) != n) {
				fp->flag |= _ERR; // turn on _ERR bit
				return EOF; // error writing buffer, return EOF
		  }
	 }
	 fp->ptr = fp->base; // reset ptr to base of buffer since data was already written or the buffer was just created
	 fp->cnt = bufsize; // update the counter for the number of chars that can fit in the buffer so putc will work correctly
	 return 0;
}

int fclose(FILE *fp) { // flushes any unwritten data for fp, discards any unread buffered input, frees any automatically allocated buffer, then closes the file. Returns EOF if error, otherwise 0
	 int result = 0;
	 if (fp == NULL || fp < _iob || fp >= _iob + OPEN_MAX)
		  return EOF; // invalid pointer provided
	 if ((fp->flag & _WRITE) == _WRITE) // if file is for writing
		  result = fflush(fp); // flush anything in buffer to output and store result
	 if (fp->base != NULL) // if there is a buffer that malloc allocated (applies to both read and write FILEs)
		  free(fp->base); // free it since we don't want a memory leak
	 if (close(fp->fd) != 0) // close file (note: it's legal to close stdin, stdout, and stderr. Just reopen them (e.g. freopen) or exit program afterwards to prevent issues)
		  result = EOF; // close returns 0 if no errors. So update result to error since it failed to close
	 fp->cnt = fp->flag = 0; // reset cnt and flag to 0
	 fp->fd = -1; // reset fd to -1 (which indicates error and should prevent improper usage of this FILE's fd)
	 fp->ptr = fp->base = NULL; // and reset the pointers to NULL. All of this resetting makes the FILE object avaliable for future fopen calls
	 return result; // defaults to 0 unless fflush or close returned an error
}

// print an error message and exit. Since normal printf messages aren't coded, use putc for stderr
void error(char *msg)
{
	 fflush(NULL); // flush all buffers before program exits and error is printed
	 while (*msg != '\0')
		  putc(*msg++, stderr); // write error chars to stderr
	 putc('\n', stderr); // finish it off with '\n', just in case
	 fflush(stderr); // make sure error message is printed
	 exit(1); // close program
}

#endif //EX_8_03
#endif //LIN
