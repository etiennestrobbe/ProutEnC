#include "stdio.h"

int _filbuf(FILE *f)
{
	// controle 
	//- allouer eventuellement un buffer
	//- verifier que f est en lecture
	int n,c;
	n=read(f->_file, &c, 1);
	f->_cnt=0; // pour garantir que le prochain getC qu'on va faire, X
	
	return(n)?c:EOF;
}

int _flsbuf(unsigned char c, FILE *f){
	return 0;
}
