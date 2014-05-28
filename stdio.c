#include "stdio.h"

int _filbuf(FILE *f)
{
	// controle 
	//- allouer eventuellement un buffer
	//- verifier que f est en lecture
	int n;
	n=read(f->_file, &c, 1);
	f->_cnt=0; // pour garantir que le prochain getC qu'on va faire, X
	
	return(n)?c:EOF
}
