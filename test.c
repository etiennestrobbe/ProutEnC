#include "stdio.h"
#include <string.h>
#define MAX 50




void tracer(FILE *f){
	char buffer[500];
	snprintf(buffer, 500, "Trace FILE %p\n", f);
	write(2, buffer, strlen(buffer));
	snprintf(buffer, 500,"\tcnt: %d, ptr: %p, base: %p, bufsiz: %d, flag:%x, file:%d\n\n",f->_cnt, f->_ptr, f->_base, f->_bufsiz, f->_flag, f->_file);
	write(2, buffer, strlen(buffer));
}

int main(){
	struct _iobuf _IOB[MAX] = {
		{0, NULL, NULL, 0,_IOREAD, 0 },
		{0, NULL, NULL, 0,_IOWRT|_IOLBF, 1 },
		{0, NULL, NULL, 0,_IOWRT | _IONBF, 2 } 
	};	
	/**/
	tracer(stdout);
	putc('X', stdout);
	tracer(stdout);
	putc('Y', stdout);
	tracer(stdout);
	putc('\n', stdout);
	tracer(stdout);/**/
	int c;
	puts ("Enter text. Include a dot ('.') in a sentence to exit:");
	do {
		c=getchar();
		putchar (c);
	} while (c != '.');/**/
	return 0;
}


int poutc(int x, FILE *p){
	/* si le compteur est positif (il reste des caractères dans le buffer)*/
	if(--(p)->_cnt >= 0){
		/* la prochaine valeur de ptr vaut x (on met x dans le buffer) */
		(int)(*(p)->_ptr++ = (unsigned char)(x));
	}
	/* sinon (il ne reste plus de place dans le buffer, le buffer est plein)*/
	else{
		/* si le buffer est en mode bufferisation par ligne*/
		if(((p)->_flag & _IOLBF) && -(p)->_cnt < (p)->_bufsiz){
			/* et si x est difference du caractère "fin de ligne" */
			if((*(p)->_ptr = (unsigned char)(x)) != '\n' ){
				/* le pointeur ptr du buffer est incrementé */
				(int)(*(p)->_ptr++);
			}
			/* dans ce cas x vaut caractère de fin de ligne */
			else{
				/* on fais un flsbuf avec le caractere \n */
				_flsbuf(*(unsigned char *)(p)->_ptr, p);
			}
		 }
		 /* le buffer est en mode buffering total */
		 else{
			 /* on fait un flsbuf avec le caractère x qqconque*/
			 _flsbuf((unsigned char)(x), p);
		 }
	}
}
