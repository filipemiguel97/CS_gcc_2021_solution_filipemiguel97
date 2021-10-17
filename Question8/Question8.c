#include <stdio.h>

long long int calculateMaximizedReturns(int, int, int, int, int[]);

int main()
{
    int n, k, d, m;
    int returns[5000]; 
    // sum=0;
    scanf("%d %d %d %d", &n, &k, &d, &m);
    for(int i=0; i<n; i++)
        scanf("%d", &returns[i]);
    long long int maximizedReturns = calculateMaximizedReturns(n, k, d, m, returns);
    //do not remove the following line
    printf("%lld", maximizedReturns);
    return 0;
}

long long int  calculateMaximizedReturns(int n, int k, int d, int m, int returns[])
{
    int i;

    //create a cum sum, with extra d elements at the end;
    int lenCumRet = n+ d ;
    int cumulativeReturns[lenCumRet];
    int cumSum=0;
    for (i = 0; i <= n; ++i)
    {
        cumSum+=returns[i];
        cumulativeReturns[i]=cumSum;
    }

    for(i = n;i < lenCumRet; ++i){
        cumulativeReturns[i]=cumSum;
    }
    // get maximum return;
    
    //initialize maxProfits at first investment;
    long long int maxProfits[n];
    long long int maxd, multipliedRets, currmax;
    int id, investment, j;
    for (i = 0; i < n; ++i)
    {
        multipliedRets= (m - 1) * (cumulativeReturns[i + d] - cumulativeReturns[i]);
        maxd = multipliedRets  - returns[i];
        maxProfits[i] = maxd + cumulativeReturns[n];
    }
    n--;

    //getting the rest of the investments; 
    for (investment = 1; investment < k; ++investment)
    {
        for (i = 0; i < n; ++i)
        {
            maxd=0;
            for (id = i; (id <= i+d) && (id<n); ++id)
            {
                multipliedRets= (m - 1) * (cumulativeReturns[id] - cumulativeReturns[i]);
                currmax = multipliedRets + maxProfits[id+1] - returns[i];
                if(currmax > maxd){
                    maxd = currmax;
                }
            }
            maxProfits[i] = maxd;
        }
        n--;
    }

    maxd=0;
    for (int l = 0; l < n; ++l)
    {
        currmax = maxProfits[l];
        if(currmax > maxd){
            maxd = currmax;
        }
    }
    return maxd;
}