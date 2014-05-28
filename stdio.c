#include "stdio.h"

int _filbuf(FILE *f){

	// Verifier f lecture

	// Mettre en place le buffer si bufferisation
	int size = (f->_flag & _IONBF) ? 1 : BUFSIZ;
	// Si le buffer n'est pas fait
	if (f->_base == NULL)
	   // Si on ne peut plus allouer
	   if ((f->_base = (char *) malloc(bufsize)) == NULL)
		   return EOF;

	// On initialise ptr
	f->_ptr = f->_base;

	// On lit sur le fichier et on enregistre le nombre de caracteres
	f->_cnt = read(f->_file, f->_ptr, size);
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

	f->_ptr = f->_base;
	free(f->base);
	f->_cnt = 0;
	return 0;
}
