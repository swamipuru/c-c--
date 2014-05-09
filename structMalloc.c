#include<stdio.h>
#include<stdlib.h>

typedef struct node{
  int data;
  int value;
  int value1;
  int value2;
  int value3;
  int value4;
  int value5;
  int value6;
  int value7;
  int value8;
  int value9;
  int value10;
  int value11;
  int value12;
  int value13;
  int value14;
  int value15;
  struct node *next;
}node;

node* print(node *ptr){
  node *temp;
  while(ptr != NULL){
    printf("%p %d\n",(void*)ptr, ptr->data);
    temp = ptr;
    ptr = ptr->next;
  }
  return temp;
}

void* getPreviousNode(node *ptr){
  return (void*)(ptr - 1);//size of node
}

int main(int argc, char *argv[]){
  node *head;
  node *ptr,*temp;
  head = (node*)malloc(sizeof(node));
  head->data = 0;
  head->next = NULL;
  ptr = head;
  long unsigned i=0;
  while(i<atoi(argv[1])){
    temp = (node*)malloc(sizeof(node));
    temp->data = i++;
    temp->next = NULL;
    ptr->next = temp;
    ptr = ptr->next;
  }
  printf("size of node %lu\n",sizeof(node));
  printf("List is: ");
  ptr = NULL;
  ptr = head;
  temp = print(head);
  printf("last node is %p\n",(void*)temp);

  ptr =(node*) getPreviousNode(temp);
  printf("previous node is %p\n",(void*)ptr);
  ptr->next = NULL;
  ptr = head;

  printf("after removing last node: \nList is :");
  temp = print(head);
  printf("Last node is : %p",(void*)temp);

  return 0;
}

