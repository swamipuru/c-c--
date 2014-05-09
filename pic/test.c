#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int displace = 30;

void sleep(time_t delay){
  time_t start,end;
  time(&start);
  do{
    time(&end);
  }while((end-start)<delay);
}

int main(int argv, char **argc){
  int i=0,j=0,k=0,p=0;
  float l = 1.0;
  do{
 //   j = system("clear");
    printf("\n");
    printf("____/ \\_____\n");
    printf("Designed By: Puru");
    i = (i+1)%2;
    /* k++;
    if(((k++)a%10) > 5)
      l = 0.9;
    else
      l = 1;
    */
    printf("\n k is initially %d ",k);
    if(k > 5)
      {
      l = 0.9;
      }
    else
      {
      l = 1.0;
      }

      if(k == 15){
      printf("\n k is now %d\n",k);
      k = 0;
      }
    printf("\nk = %d l = %f  \n",k,l);
    sleep(l);
    k++;
  }while(1); 
  //9916411611-Yashwant 9:00 am Novotol
  getchar();
  return 0;
}

