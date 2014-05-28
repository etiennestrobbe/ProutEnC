#include "stdio.h"
#include <unistd.h>
#include <stdlib.h>

extern unsigned char (*_smbuf)[_SBFSIZ];

void	_findbuf(FILE *);
void	_bufsync(FILE *);
int _filbuf(FILE *f){

	// Verifier f lecture

	// Mettre en place le buffer si bufferisation
	int size = (f->_flag & _IONBF) ? 1 : BUFSIZ;
	// Si le buffer n'est pas fait
	if (f->_base == NULL)
	   // Si on ne peut plus allouer
	   if ((f->_base = (char *) malloc(size)) == NULL)
		   return EOF;

	// On initialise ptr
	f->_ptr = f->_base;

	// On lit sur le fichier et on enregistre le nombre de caracteres
	f->_cnt = read(f->_file, f->_ptr, size);
	
	/* si le compteur vaut 0 alors on est en EOF */
	if ((f)->_cnt == 0) {
		f->_flag |= _IOEOF;
		return EOF;
	}
	else if((f)->_cnt == 0){
		f->_flag |= _IOERR;
		f->_cnt = 0;
		return EOF;
	}
	return (unsigned char) *f->_ptr++;
}

int _flsbuf(unsigned char c, FILE *f){

	int size = (f->_flag & _IONBF) ? 1 : BUFSIZ;

	// Si le buffer n'existe pas
	if(f->_bufsiz <=1){
		f->_base = malloc(size);
		f->_ptr = f->_base;
		f->_cnt = size;
	}

	// Si le buffer est plein
	if(f->_ptr == f->_base + size){
		puts("BUFFER PLEIN J'ECRIS DANS FICHIER");
		int r = write(f->_file, (char *) f->_base, size);
		if(r){
			puts("R !");
		}
		else
		{
			puts("PAS R !");
		}
		f->_ptr = f->_base;
		f->_cnt = size;
	}
	puts("J'ECRIS DANS BUFFER BITE");
	*(f->_ptr)++ = c;
	f->_cnt--;

	// D'autres cas ?

	return c;
}
