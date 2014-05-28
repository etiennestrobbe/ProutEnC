#include "stdio.h"

int _filbuf(FILE *f){
	/*// controle 
	//- allouer eventuellement un buffer
	//- verifier que f est en lecture
	int n,c;
	n=read(f->_file,&c,1);
	f->_cnt=0; // pour garantir que le prochain getC qu'on va faire, on rapellera bien fillbuf
	return(n)?c:EOF;/*/
	int bufsize;
 
	bufsize = (f->_flag & _IONBF) ? 1 : BUFSIZ;
	if (f->_base == NULL)     // no buffer yet
	   if ((f->_base = (char *) malloc(bufsize)) == NULL)
		   return EOF;       // can't get buffer
	f->_ptr = f->_base;
 
	f->_cnt = read(f->_file, f->_ptr, bufsize);
	if (--f->_cnt < 0) {
	   if (f->_cnt == -1)
		   f->_flag |= _IOEOF;
	   else
		   f->_flag |= _IOERR;
	   f->_cnt = 0;
	   return EOF;
	}
	return (unsigned char) *f->_ptr++;
}

int _flsbuf(unsigned char c, FILE *f){
	return 0;
}
