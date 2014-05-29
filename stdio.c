#include "stdio.h"
#include <unistd.h>
#include <stdlib.h>


int _filbuf(FILE *f){

	// Verifier f lecture
	if(!f->_flag & _IOREAD){
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

	// on recupere la taille du buffer
	int size = (f->_flag & _IONBF) ? 1 : BUFSIZ;
	
	// si le buffer est en mode NBF alors on ecrit direct sur le fichier (pas de bufferisation)
	if(size==1){
		write(f->_file,&c,1);
	}
	

	// Si le buffer n'existe pas, on le creer (allocation)
	if(f->_base == NULL){
		if ((f->_base = (char *) malloc(size)) == NULL){
			f->_flag |= _IOERR;
			return EOF;
		}
		// init des attribut du FILE
		f->_bufsiz = size;
		f->_ptr = f->_base;
		f->_flag |= _IOMYBUF;
	}
	

	// Si le buffer est plein
	if(f->_ptr == f->_base + size){
		// si l'ecriture du buffer dans le fichier f marche pas
		if(!write(f->_file, (char *) f->_base, size)){
			f->_flag |= _IOERR;
			return EOF;
		}
		f->_ptr = f->_base;
		*(f->_ptr)++ = c;
		f->_cnt = 0;
	}
	else if(f->_flag & _IOLBF && c == '\n'){
		if(!write(f->_file, (char *) f->_base, -f->_cnt)){
			f->_flag |= _IOERR;
			return EOF;
		}
		f->_ptr = f->_base;
		f->_cnt = 0;
	}
	else{
		*(f->_ptr)++ = c;
	}


	return c;
}


int fclose(FILE *f){
	int rtn=EOF;

	if(f == NULL)return(rtn);

	// On est en ecriture
	if(f->_flag & (_IOWRT | _IORW) == 0){
		_flsbuf(EOF, f);
	}

	free((char*)f->_base);
	f->_base = NULL;

	f->_flag = 0;
	f->_cnt = 0;
	f->_ptr = f->_base;
	f->_bufsiz = 0;
	return(rtn);
}

