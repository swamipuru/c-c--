#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
/* Head ends here */
int lonelyinteger(int a_size, int* a) {
    int ar[101] = {0};
    int i,ans=0,temp;
    for(i=0; i<a_size; i++){
        //printf("ar[%d]: %d temp: %d\n ",a[i],ar[a[i]],a[i]);
	temp = a[i];
        if(ar[temp] == 0)
            ans = a[i];
        ar[temp] = ar[temp]+1;
 	printf("ar[%d]: %d temp: %d\n ",a[i],ar[a[i]],a[i]);
    }
    for(i=0;i<101;i++){
	if(ar[i] == 1)
	ans = i;
    }
return ans;
}
/* Tail starts here */
int main() {
    int res;
    int _a_size, _a_i;
    scanf("%d", &_a_size);
    int _a[_a_size];
    for(_a_i = 0; _a_i < _a_size; _a_i++) { 
        int _a_item;
        scanf("%d", &_a_item);
        
        _a[_a_i] = _a_item;
    }
    
    res = lonelyinteger(_a_size, _a);
    printf("%d", res);
    
    return 0;
}
