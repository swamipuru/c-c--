#include<stdio.h>
#include<stdlib.h>
typedef struct emp{
  char name[20];
  int id;
}emp;

int main(){
  char ch = 'y';
  FILE *pk = fopen("keviv.txt","aw+");
  emp e;
  emp e2;
  if(pk == NULL){
    printf("File open error!!!!\n");
    exit(0);
  }
  while(ch == 'y'){
    printf("\n\nEnter recordes of employee:\n");
    printf("\nName: ");
    scanf("%s",e.name);
    printf("Id: ");
    scanf("%d",&e.id);
    fprintf(pk,"%s %d\n",e.name,e.id);
    printf("\nContinus(Y/N): ");
    fflush(stdin);
    getchar();
    scanf("%c",&ch);
  }
  fclose(pk);
  printf("File content:\n\n");
  pk = fopen("keviv.txt","ar+");
  e.name[0] = 'C';
  e.name[1] = 'h';//andra";
  e.id = 987;
  while(fread(&e2,sizeof(e2),1,pk)!= EOF){
    printf("%s %d\n",e2.name,e2.id);
    getchar();
  }
  fclose(pk);
  return 0;
}
