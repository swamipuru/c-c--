#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int totalInvestors=4;
int maximumTransaction = 1000;
int compareStrings(char *str1, char *str2){
  int i=0;
  int res=1;
  while(str1[i] && str2[i]){
    if(str1[i]!=str2[i]){
      res = 0;
      break;
    }
    i++;
  }
  return res;
}

int getStringIndex(char investores[][10],char *str){
  int i=0,index=-1;
  for(i=0;i<totalInvestors;i++){
    if(compareStrings(investores[i],str)==1){
       index = i;
       break;
    }
  }
   return index;
}

int main(){
  totalInvestors=10;
  char investors[totalInvestors][10];
  int initialAmount[totalInvestors][totalInvestors];
  int i=0,j=0,k=0,choice,transferAmount,rIndex, sIndex;
  char sender[10],receiver[10];
  static int totalTranscation=0;
  int transactionTable[maximumTransaction][3];
  int maximumInvestments[totalInvestors],max=0,index=-1;

  FILE *fp = fopen("input.txt","r");
  char c;
  c = fscanf(fp,"%d",&totalInvestors);
  printf("\nc: %c\n",c);
  for(i=0;i<totalInvestors;i++){
    c = fscanf(fp,"%s",investors[i]);
  }

  for(i=0;i<totalInvestors;i++){
    for(j=0;j<totalInvestors;j++){
      c = fscanf(fp,"%d",&initialAmount[i][j]);
    }
  }

  /*  printf("\n\n");
  for(i=0;i<totalInvestors;i++){
    for(j=0;j<totalInvestors;j++){
      printf("%d ",initialAmount[i][j]);
    }
    printf("\n");
    }*/
  fclose(fp);
  
  for(i=0;i<totalInvestors;i++){
    maximumInvestments[i]=0;
  }
  for(i=0;i<maximumTransaction;i++){
    for(j=0;j<3;j++)
      transactionTable[i][j]=-1;
  }

  printf("\nHere are your investors:\n");
  for(i=0;i<totalInvestors;i++){
    printf("%s\n",investors[i]);
  }

  while(1){
    printf("\nSelect one of the following:\n");
    printf("1. Invest money with someone.\n");
    printf("2. See transactions between investors.\n");
    printf("3.Quit\n");
    scanf("%d",&choice);
    switch(choice){
    case 1:
      printf("Who is sending money?\n");
      scanf("%s",sender);
      printf("Who is receiving the money?\n");
      scanf("%s",receiver);
      printf("Amount of money being transferred?\n");
      scanf("%d",&transferAmount);
      sIndex = getStringIndex(investors,sender);
      rIndex = getStringIndex(investors,receiver);
      //printf("sender: %d\n",sIndex);
      //printf("receiver: %d\n",rIndex);
      if(initialAmount[sIndex][sIndex] >= transferAmount && sIndex != -1 && rIndex != -1){
	initialAmount[sIndex][sIndex] -= transferAmount;
	initialAmount[rIndex][rIndex] += transferAmount;
	transactionTable[totalTranscation][0] = sIndex;
	transactionTable[totalTranscation][1] = rIndex;
	transactionTable[totalTranscation][2] = transferAmount;
	totalTranscation += 1;
	maximumInvestments[sIndex] += 1;
      }else if(sIndex == -1){
	printf("There is no investor %s listed.\n",sender);
      }else if(rIndex == -1){
	printf("There is no investor %s listed.\n", receiver);
      }else{
	printf("\nSorry this transaction cannot be performed. %s does not have enough money.",sender);
      }
      break;
    case 2:
     if(transactionTable[0][0]== -1){
	printf("\nThere have not been any transcation thus far.");
      }else{
	i=0;
	while(transactionTable[i][0] != -1){
	  printf("%s made a $%d investment with %s\n",investors[transactionTable[i][0]],transactionTable[i][2],investors[transactionTable[i][1]]);
	  i++;
	}
      }
      break;
    case 3:
      index = -1;
      max = 1;
      for(i=0;i<totalInvestors;i++){
	if(max <= maximumInvestments[i]){
	  max = maximumInvestments[i];
	  index = i;
	}
      }
      if(index != -1){
	printf("%s made the most investments!!!\n",investors[index]);
      }else
	printf("No investments have been made.\n");
      exit(0);
      break;
    default:
      printf("Sorry that was not a valid input.\n");
    }
  }
  return 0;
}
