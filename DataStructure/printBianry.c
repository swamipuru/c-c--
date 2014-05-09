#include<stdio.h>

void getBinary(int x, int d){
  printf("x:%d d: %d\n",x,d);
  char buf[33];
  int i=0;
  while(d){
    if(x&1)
      buf[i++]='1';
    else
      buf[i++]='0';
    x = x >> 1;
    d--;
  }
  buf[i] = '\0';
  while(i)
    printf("%c",buf[--i]);
}

int main(int argc,char **argv){
  getBinary(atoi(argv[1]),atoi(argv[2]));
  printf("\n");
  return 0;
}
