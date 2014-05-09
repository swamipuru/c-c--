#include<stdio.h>
#include<stdlib.h>
#define MAX 10

typedef struct{
  int top;
  int contents[MAX];
}stack;

void push(stack *s, int data){
  if(s->top == MAX){
    printf("Stack Overflow....\n");
  }else{
    s->contents[++(s->top)] = data;
  }
}

int pop(stack *s){
  if(s->top == -1){
    printf("Stack Underflow....\n");
    return 0;
  }else{
    return s->contents[(s->top)--];
  }
}

int main(){
  stack s;
  int i=0;
  s.top = -1;
  push(&s,10);
  push(&s,20);
  push(&s,30);
  for(i=0;i<5;i++){
    printf("%d ",pop(&s));
  }
  printf("\n");
  return 0;
}
