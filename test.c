#include "stdio.h"



int main(){
	int c;
	while((c=getchar()!=EOF)){
		write(1,(char *)c, 1);
	}
	return 0;
}
