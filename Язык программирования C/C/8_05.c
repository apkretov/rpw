//#define _bufsize 512
//#define _nfile 20 /*files that can be handled*/
//typedef struct _iobuf { // � ����������� ���������� ����� ����������� ����������� ���������� ������, � �� ������������. ��������� ����� �������� ���������� �� ���������, ������� �������� ��������� ��������� ���������� � �����: ��������� ������, ����� ���� ��� �������� �������� ��������; ������� ����� ��������, ���������� � ������; ��������� ��������� ������� ������� � ������; ��������� ��������, ����������� ����� ������ ��� ������ � �.�.; ���������� �����.
//	 char *_ptr; /*next character position*/ // � ���������� ���� �������� �� ����� stdio.h �����, ��������������� ������ ��� ������������� ��������� ����������, ���������� � �������������, � ��� ����� ��������� ����������� ���������� � ������� � ��������� ������������.
//	 int _cnt; /*number of characters left*/
//	 char *_base; /*location of buffer*/
//	 int _flag; /*mode of file access*/
//	 int _fd; /*file descriptor*/
//} file;
//extern file _iob[_nfile];
//
//#define stdin (&_iob[0])
//#define stdout (&_iob[1])
//#define stderr (&_iob[2])
///*MINE
//#define _stdin (&_iob[0])
//#define _stdout (&_iob[1])
//#define _stderr (&_iob[2])
//*/
//
//#define _READ 01 /* file open for reading */
//#define _WRITE 02 /* file open for writing */
//#define _UNBUF 04 /* file is unbuffered */
//#define _BIGBUF 010 /* big buffer allocated */
//#define _EOF 020 /* EOF has occurred on this file */
//#define _ERR 040 /* error has occurred on this file */
//#define NULL 0
//#define EOF (-1)
//
//#define getc(p) (--(p)->_cnt >= 0 ? *(p)->_ptr++ & 0377 : _filebuf(p)) // � ���������� ��������� ������ getc ������ ��������� �������, ����������� ��������� � ���������� ������. (���� ����������� #define ������� �������, �� ��� ������������ � ������� �������� ����� �����). ���� ������ ������� ���������� �������������, �� getc �������� ������� _filebuf, ������� ����� ��������� �����, ���������������� ���������� ��������� � ���������� ������.
//#define getchar() getc(_stdin)
//
//#define putc(x, p) (--(p)->_cnt >= 0 ? *(p)->_ptr++ = (x) : _flushbuf((x), p)) // �������� � �������� ����� �����, ��� � getc, ��������� ��� ���������� ������ � ������� _flushbuf.
//#define putchar(x) putc(x, _stdout)
//
//#include <stdio.h> // ������� ����� ��������� ������� fopen ������� � ����������� ����� � ������������� ��� � ������ �����, � ����� � ������������� ����� ��������� ����� �������, ����� ��� ��������� ������ ���������. ������� fopen �� �������� �����-���� �������� ������; ��� �������� �������� _filebuf ��� ������ ������ �� �����.
//#define PMODE 0644 /*r/w for owner;r for others*/
//file* fopen(name, mode) /*open file,return file ptr*/
//register char* name, * mode;
//{
////MINE file* fopen(char* name, * mode) { /*open file,return file ptr*/
//	register int fd;
//	register file* fp;
//	if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
//		fprintf(_stderr, "illegal mode %s opening %s\n",
//			mode, name);
//		exit(1);
//	}
//	for (fp = _iob; fp < _iob + _nfile; fp++)
//		if ((fp->_flag & (_READ | _WRITE)) == 0)
//			break; /*found free slot*/
//	if (fp >= _iob + _nfile) /*no free slots*/
//		return(NULL);
//	if (*mode == 'w') /*access file*/
//		fd = creat(name, PMODE);
//	else if (*mode == 'a') {
//		if ((fd = open(name, 1)) == -1)
//			fd = creat(name, PMODE);
//		lseek(fd, ol, 2);
//	}
//	else
//		fd = open(name, 0);
//	if (fd == -1) /*couldn't access name*/
//		return(NULL);
//	fp->_fd = fd;
//	fp->_cnt = 0;
//	fp->_base = NULL;
//	fp->_flag &= (_READ | _WRITE);
//	fp->_flag |= (*mode == 'r') ? _READ : _WRITE;
//	return(fp);
//}

#undef MINE // Ref. --(p)->_cnt
#ifdef MINE

#include <stdio.h>

static struct s_t {
	int i;
	int* pi;
};
typedef struct s_t s;
s a[3], *pa = a;

static f1() {
	printf("%d\n", ++pa->i); // The three are equivalent: incremting i.
	printf("%d\n", ++(pa)->i);
	printf("%d\n", ++(pa->i));

	printf("%d\n", (++pa)->i); // Different: incrementing pa.
}

static f2() {
	for (s *pa = a; pa < a + sizeof(a) / sizeof(*a); ++pa) {
		pa->pi = &pa->i;
		printf("%d\t%d\t%d\t%d\t%d\n", *pa->pi, *(pa)->pi, *(pa->pi), (*pa).i, *(*pa).pi);
	}
}

#undef ON
#ifdef ON
int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	a[0].i = 100;
	a[1].i = 10;
	a[2].i = 20;

	//f1();
	f2();

	(void)getchar();
	return 0;
}
#endif

#endif //MINE
