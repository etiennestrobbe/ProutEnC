#include "stdio.h"

int _filbuf(FILE * f){

	int n, c;
	// CONTROLES : allouer eventuellement un buffer, verifier que f est en lecture

	n = read(f->_file, &c, 1);
	f->_cnt = 0;

	return (n)?c:EOF;
}
