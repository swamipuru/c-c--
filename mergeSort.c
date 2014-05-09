#include<stdio.h>
#define infinite 999999999

void print(int ar[],int l, int size){
  for(int i=l; i<=size; i++)
    printf("%d ",ar[i]);
  printf("\n");
}

void merge(int arr[], int p, int q, int r){
  int i,j,k;
  int n1 = q - p+1;
  int n2 = r-q;
  int L[n1], R[n2];
  //copy
  for(i=0;i<n1;i++)
    L[i] = arr[p+i];
  for(j=0;  j<n2; j++)
    R[j] = arr[q+1+j];
  //merge
 L[n1] = infinite;
 R[n2] = infinite; 
  for(i=0,j=0,k=p;k<=r;k++){
    if(L[i] <= R[j]){
      arr[k] = L[i];
      i++;
    }else{
      arr[k] = R[j];
      j++;
    }
  }
}

void mergeSort(int arr[], int p, int r){
  if(p < r){
    int q = (p +r)/2;
    mergeSort(arr, p,q);
    mergeSort(arr, q+1, r);
    merge(arr, p,q,r);
  }
}


int main(){
  int size = 7;
  int ar[] = {5,8,1,3,7,9,2};
  print(ar,0,size-1);
  mergeSort(ar,0,size-1);
  print(ar,0,size-1);
  return 0;
}
