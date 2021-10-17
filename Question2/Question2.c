#include <stdio.h>
#include <stdlib.h>


int compare (const void * a, const void * b)
{
    return ( (*(int**)a)[1] - (*(int**)b)[1]);
}

int securitiesBuying(int z,int security_value[], int N)
{
    int no_of_stocks=0;
   // participants code here

    int* sec[N];
    int secStore[N][2];
    int n;
    for(n=0;n<N; n++) {
        secStore[n][0] = n + 1;
        secStore[n][1] = security_value[n];
        sec[n] = secStore[n];
    }

    qsort(sec, N, sizeof(int*), compare);

    for(n=0; n < N; n++){
        int prod = sec[n][0] * sec[n][1];
        if(prod > z){
            no_of_stocks += z / sec[n][1];
            break;
        }
        else{
            no_of_stocks += sec[n][0];
            z-= prod; 
        }
    }

    return no_of_stocks;
}

int main(void) {
    int z;
    scanf("%d",&z);
    int input,security_value[50],size=0;
    while(scanf("%d",&input)==1)
    {
        security_value[size++]=input;
    }
    
    int no_of_stocks_purchased = securitiesBuying(z,security_value, size);
    printf("%d",no_of_stocks_purchased);
    return 0;
}

