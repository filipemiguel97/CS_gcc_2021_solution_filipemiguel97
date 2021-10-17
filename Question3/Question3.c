#include <stdio.h>

int profit_maxi(int maxSum, int* a, int* b, int n, int m) {
    int inda=0, indb=0, mova=0, movb=0, profit_max=0, rollingmax=0;
    for (inda = 0; inda < n; inda++)
    {
        mova+=a[inda];
        if(mova > maxSum){
            mova-=a[inda];
            inda--;

            if(mova < 0){
                mova=0;
            }
            break;
        }
    }
    if(inda > n-1){
        inda = n-1;
    }

    profit_max = inda+1;

    for(indb=0; indb < m; indb++)
    {
        movb += b[indb];
        while((0<=inda) && ((mova + movb) > maxSum)){
            mova-=a[inda];
            inda--;

            if(mova < 0){
                mova=0;
            }
        }
        if((mova + movb) > maxSum)
            break;

        rollingmax = inda + indb + 2;
        if(rollingmax > profit_max){
            profit_max = rollingmax;
        }
    }
    return profit_max;

}

int main()
{ 
    int n, m, x, i, result;
    scanf("%d %d %d", &n, &m, &x);

    int a[n], b[m];
    for (i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    for (i = 0; i < m; ++i) {
        scanf("%d", &b[i]);
    }

    result = profit_maxi(x, a, b, n, m);

    printf("%d", result);
    return 0;
}