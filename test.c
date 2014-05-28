#include "stdio.h"


void tracer(FILE *f)
{
char buffer[500];
snprintf(buffer, 500, "Trace FILE %p\n", f);
write(2, buffer, strlen(buffer));
snprintf(buffer, 500,
"\tcnt: %d, ptr: %p, base: %p, bufsiz: %d, flag:%x, file:%d\n\n",
f->_cnt, f->_ptr, f->_base, f->_bufsiz, f->_flag, f->_file);
write(2, buffer, strlen(buffer));
}

int main(){
   tracer(stdin);
  return 0;
}
		
		
		
			
			
	
