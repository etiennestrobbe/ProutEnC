#include "stdio.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int _filbuf(FILE *f){

	// Verifier f lecture
	if(!f->_flag & _IOREAD){
		return EOF;
	}
	else{
		
		// Mettre en place le buffer si bufferisation
		int size = (f->_flag & _IONBF) ? 1 : BUFSIZ;
		
		// Si le buffer n'est pas fait
		if (f->_base == NULL){
			f->_bufsiz = size;
		   // Si on ne peut plus allouer
		   if ((f->_base = (unsigned char *) malloc(size)) == NULL){
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

	// Le fichier est ouvert
	if(f->_file && (f->_flag & _IOLBF | _IOWRT |  _IOREAD | _IORW)){

		// Allocation
		if(f->_base == NULL){
			if ((f->_base = (unsigned char *) malloc(BUFSIZ)) == NULL){
				f->_flag = _IOERR;
				return EOF;
			}
			f->_bufsiz = BUFSIZ;
			f->_flag = _IOMYBUF;
			f->_ptr = f->_base;
			f->_cnt = 0;
		}
		// Dernier caractere : retour à la ligne
		if(c == '\n'){
			write(f->_file, (unsigned char *) f->_base, - f->_cnt);
			f->_ptr = f->_base;
			f->_cnt = 0;
		}
		else{
			*(f->_ptr) = c;
			(f->_ptr)++;
		 }
		return c;
	}
	else{
		return EOF;
	}
	
return c;
}


int fflush(FILE *stream){
	int rc = 0;
  int count;
  int written;

  if (!stream) stream = 1;
  if ((stream->_flag & (_IOREAD | _IOWRT)) == _IOWRT && 
      ((stream)->_flag & (_IONBF | _IOMYBUF)) && 
      (count = stream->_ptr - stream->_base) > 0) {
    
      written = write(fileno(stream), stream->_base, count);

    if (written == count)  {
      // If this is a read/write file, clear _IOWR so that next operation can be a read
      if (stream->_flag & _IORW) stream->_flag &= ~_IOWRT;
    } else {
      stream->_flag |= _IOERR;
      rc = EOF;
    }
  }

  stream->_ptr = stream->_base;
  stream->_cnt = 0;

  return rc;
}


int fclose(FILE *f){
	int rtn=EOF;

	if(f == NULL)return(rtn);

	// On est en ecriture
	if((f->_flag & (_IOWRT | _IORW)) == 0){
		_flsbuf(EOF, f);
	}

	free((char*)f->_base);
	f->_base = NULL;

	f->_flag = 0;
	f->_cnt = 0;
	f->_ptr = f->_base;
	f->_bufsiz = 0;
	free(f);
	return(rtn);
}
/**
 * Méthode _Lmodeparse de Intel (sans le O_BINARY)
 * Copyright (c) 1984,85,86,87 Computer Innovations Inc, ALL RIGHTS RESERVED.
 */
unsigned _Lmodeparse(const char *openmode)
{
    register unsigned mode = 0;
    register int state;

    switch (*openmode++) {
        case 'r': mode |= (unsigned)O_RDONLY;
                  break;
        case 'w': mode |= (unsigned)(O_WRONLY | O_CREAT | O_TRUNC);
                  state = 1;
                  break;
        case 'a': mode |= (unsigned)(O_APPEND | O_WRONLY | O_CREAT);
                  state = 1;
                  break;
        default:  return 0xFFFFu;
    }

    while (*openmode) {
        switch (*openmode++) {
            case 'r': if (!state) return 0xFFFFu;
                      mode &= (unsigned)(~O_WRONLY);
                      mode |= (unsigned)O_RDWR;
                      break;
            case 'w': if (state) return 0xFFFFu;
                      mode &= (unsigned)(~O_RDONLY);
                      mode |= (unsigned)O_RDWR;
                      break;
            case '+': mode &= (unsigned)(~(O_RDONLY | O_WRONLY));
                      mode |= (unsigned)O_RDWR;
                      break;
            default:  return 0xFFFFu;
        }
    }
    return mode;
}

FILE *fopen(const char *path, const char *mode){
	FILE *f = malloc(sizeof(FILE));
	int fd;
	int flag;	
	flag =  _Lmodeparse(mode);
	
	

	if ((fd = open(path, flag, 0640)) < 0) {
		f->_flag = 0;			/* release */
		return (NULL);
	}
	if ((f->_base = (unsigned char *) malloc(BUFSIZ)) == NULL){
			   return NULL;
	}
	f->_ptr = f->_base;
	
	f->_file = fd;
	f->_flag |= (strcmp(mode,"r")==0)? (_IOREAD|_IOMYBUF):(_IOWRT|_IOLBF|_IOMYBUF) ;
	f->_bufsiz = BUFSIZ;
	return f;
}

int setvbuf(FILE *stream, char *buf, int mode, int size){
	if(size<1){
		return EOF;
	}
	if(!(mode == _IONBF || mode == _IOLBF || mode == _IOFBF)){
		return EOF;
	}
	if(stream == NULL){
		return EOF;
	}
	if(buf == NULL){
		if((stream->_base= (unsigned char *) malloc(size)) == NULL){
			return EOF;
		}
	}
	else{
		stream->_base = buf;
	}
	stream->_ptr = stream->_base;
	stream->_flag |= mode;
	stream->_bufsiz = size;
	stream->_cnt = 0;
	return 0;
}

void setbuf(FILE *stream, char *buf){
	if(buf == NULL){
		setvbuf(stream,NULL,_IONBF,0);
	}
	else{
		setvbuf(stream,buf,_IOFBF,BUFSIZ);
	}
}

