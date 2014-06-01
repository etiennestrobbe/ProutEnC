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

int main(int argc,char **argv){
	struct _iobuf _IOB[MAX] = {
		{0, NULL, NULL, 0,_IOREAD, 0 },
		{0, NULL, NULL, 0,_IOWRT|_IOLBF, 1 },
		{0, NULL, NULL, 0,_IOWRT | _IONBF, 2 } 
	};	
	/*
	FILE *p = fopen("foo","r");
	tracer(p);
	fclose(p);
	tracer(p);
	return 0;
	if(argc <= 2) {
		return 0;
	}

	FILE *lecture = fopen(argv[1],"r");
	FILE *ecriture = fopen(argv[2],"w");

	if(lecture == NULL) {
		return -1;
	}

	char c;
	while((c = getc(lecture)) != EOF) {
		putc(c,ecriture);
	}

	fflush(ecriture);


	fclose(lecture);
	fclose(ecriture);
	*/

	int c;
	puts ("Enter text. Include a dot ('.') in a sentence to exit:");
	do {
		c=getchar();
		putchar (c);
	} while (c != '.');
	return 0;
}
