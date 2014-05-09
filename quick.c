#include<stdio.h>

void print(int ar[], int l, int r){
  int i;
  for(i=l; i<= r; i++){
    printf("%d ",ar[i]);
  }
  printf("\n");
}
int partition(int ar[], int l, int r){
  int pivot = ar[l];
  int i=l, j= r;
  while(i < j){
    while(ar[i] <= pivot) i++;
    while(ar[j] > pivot) j--;
    if(i < j){
      int temp = ar[i];
      ar[i] = ar[j];
      ar[j] = temp;
     // print(ar, l, r);
    }
  }
  ar[l] = ar[j];
  ar[j] = pivot;
  return j;
}

void quick(int ar[], int l, int r){
  if(l < r){
    int pos = partition(ar, l, r);
    quick(ar, l, pos-1);
    print(ar, l, pos);
    quick(ar, pos+1, r);
  }
}

int main(){
  int ar[7] = {5,8,1,3,7,9,2};
  printf("\nInitial array is: ");
  print(ar, 0,6);
  quick(ar, 0,6);
  printf("after sorting\n");
  print(ar,0,6);
 return 0;
}
