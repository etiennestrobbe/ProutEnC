#include "stdio.h"
#include <unistd.h>
#include <stdlib.h>


int _filbuf(FILE *f){

	// Verifier f lecture
	if(!f->_flag & _IOREAD){
		puts("file not in read mode");
		return EOF;
	}
	else{
		
		// Mettre en place le buffer si bufferisation
		int size = (f->_flag & _IONBF) ? 1 : BUFSIZ;
		f->_bufsiz = size;
		// Si le buffer n'est pas fait
		if (f->_base == NULL){
		   // Si on ne peut plus allouer
		   if ((f->_base = (char *) malloc(size)) == NULL){
			   return EOF;
		   }
		   else{
			   // TODO mettre les bons drapeaux
			   f->_flag |= _IOMYBUF;
		   }
		}

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
}

int _flsbuf(unsigned char c, FILE *f){
	return 0;
}

/*
int fclose(FILE *iop){
	int rtn=EOF;

	/* si le FILE est null, il n'a jamais été ouvert *
	if(iop == NULL)return(rtn);
	
	if(iop->_flag & (_IOREAD | _IOWRT | _IORW)
	   && (iop->_flag & _IOSTRG) == 0) {
		rtn = (iop->_flag & _IONBF)? 0: fflush(iop);
		if(close(fileno(iop)) < 0)
			rtn = EOF;
	}
	if(iop->_flag & _IOMYBUF) {
		free((char*)iop->_base);
		iop->_base = NULL;
	}
	iop->_flag = 0;
	iop->_cnt = 0;
	iop->_ptr = iop->_base;
	iop->_bufsiz = 0;
	return(rtn);
}*/

