#include <stdio.h>
#include <stdlib.h>
 
int compare (const void * a, const void * b)
{
    return ( (*(int**)a)[1] - (*(int**)b)[1]);
}


int totalPairs(int n, int values[]){
    // Complete the total Pairs function
    int i,j,npairs=0, max, val;
    
    max=values[0];
    for(j=1;j<n; j++) {
        val = values[j];
        if(val < max)
            npairs++;
        else
            max = val;
    }
    max=values[n-1];
    for(j=n-2;j>=0; j--) {
        val = values[j];
        if(val < max)
            npairs++;
        else
            max = val;
    } 

    return npairs;
}
int main(){
    int n, i;
    scanf("%d", &n);
    int answer;
    int values[n];
    for (i = 0; i < n; ++i) {
        scanf("%d", &values[i]);
    }
    answer = totalPairs(n, values);
    // Do not remove below line
    printf("%d",answer);
    // Do not print anything after this line
    return 0;
}