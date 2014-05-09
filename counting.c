#include<stdio.h>
#define MAXVALUE 100000
#define MAXSIZE 100

void print(int ar[], int size){
 for(int i=0;i<size;i++){
  printf("%d ",ar[i]);
 }
 printf("\n");
}
void countSort(int ar[], int size){
 int countAr[MAXVALUE]={0};
 int sortedAr[size],k=0,i,j;
 for(int i=0;i<size;i++){
  countAr[ar[i]] += 1;
 }
 for(i=0;i<MAXVALUE;i++){
  for(j=0;j<countAr[i];j++){
   sortedAr[k++] = i;
  }
 }
 printf("sorted array:\n");
 print(sortedAr, size);
}

int main(){
 int ar[MAXSIZE],size,i=0;
 printf("Enter size of array: ");
 scanf("%d",&size);
 printf("Enter elements: ");
 while(i<size){
  scanf("%d",&ar[i++]);
 }
 countSort(ar,size);
 return 0;
}
