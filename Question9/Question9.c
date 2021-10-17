#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define fakeMin 300000 // larger than any number we expect to see

int arrayMin(const int arr[], int len){
    int temp, i, min =fakeMin;
    for (i = 0; i < len; ++i)
    {
        if(arr[i] < min){
            min = arr[i];
        }
    }
    return min;
}


int bankersAndClients(int c,int b,int** time){
    
    // Complete the bankersAndClients function .
    int nCombinations = 1<<b; //2^b
    int combinationsArray[nCombinations][b];
    int i,j, bitwisej, k, overalMin, tempDif;

    for (j = 0; j < nCombinations; ++j)
    {
        for (k = 0; k < b; ++k)
        {
            combinationsArray[j][k] = fakeMin;
        }
    }

    for (k = 0; k < b; ++k)
    {
        combinationsArray[1<<k][k]=time[k][0];
    }
    for (i = 1; i < c; ++i)
    {
        for (j = nCombinations-1; j >= 0; --j)
        {
            bitwisej=j;
            if(__builtin_popcount(j) <= i){
                overalMin = arrayMin(combinationsArray[j], b);
                for (k = 0; k < b; ++k, bitwisej = bitwisej >> 1)
                {
                    if ((bitwisej & 1) ==0)
                    {
                        tempDif = overalMin + time[k][i] - combinationsArray[j+(1<<k)][k];
                        if(tempDif < 0){
                            combinationsArray[j+(1<<k)][k] += tempDif; 
                        }
                    }
                    else if(combinationsArray[j][k] != fakeMin)
                    {
                        combinationsArray[j][k]+= time[k][i];
                    }
                }
            }
        }
    }

    overalMin = fakeMin;
    int  tempVal;
    for (j = 0; j < nCombinations; ++j)
    {
        tempVal = arrayMin(combinationsArray[j], b);
        if (tempVal < overalMin)
        {
            overalMin = tempVal;
        }
    }

    return overalMin;
}

int main(){
    int b,c;
    scanf("%d %d", &c, &b);
    int answer;
    int** time;
    time = malloc(b * sizeof *time);
    for (int i=0; i<b; i++)
    {
        time[i] = malloc(c * sizeof *time[i]);
    }

    for(int i = 0; i < b; i++){
        for(int j = 0;j < c;j++){
            scanf("%d",&time[i][j]);
        }
    }
    answer = bankersAndClients(c,b,time);
    // Do not remove below line
    printf("%d",answer);
    // Do not print anything after this line
    for (int i=0; i<b; i++)
    {
        free(time[i]);
    }
    free(time);

    return 0;
} 
