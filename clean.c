#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>

int main(){
  int rc;
  printf("Testing 124...\n");
  rc = syscall(SYS_clear,"/usr/bin/clear",0444);
  if(rc == -1)
    fprintf(stderr, "clear failed, errno = %d\n",errno);
  return 0;
}
