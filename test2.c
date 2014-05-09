#include<stdio.h>
void fun2();
void fun1(){
  printf("fun1\n");
  fun2();
}

void fun2(){
  printf("fun2\n");
  fun1();
}

int main(){
  printf("main\n");
  fun1();
  return 0;
}
