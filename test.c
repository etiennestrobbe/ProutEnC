#include "stdio.h"
#include <string.h>
#define MAX 50



int main(int argc,char **argv){
	struct _iobuf _IOB[MAX] = {
		{0, NULL, NULL, 0,_IOREAD, 0 },
		{0, NULL, NULL, 0,_IOWRT|_IOLBF, 1 },
		{0, NULL, NULL, 0,_IOWRT | _IONBF, 2 } 
	};
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

	fclose(lecture);
	fclose(ecriture);
}
