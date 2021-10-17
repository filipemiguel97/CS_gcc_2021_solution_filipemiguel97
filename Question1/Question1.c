#include<stdio.h>


int solution(int n)
{
    return 2*( n -1) / 3 + 1;
}

/* Do not edit below code */
int main(void) {
    int n; 
    scanf("%d",&n);
    int answer=solution(n);
    printf("%d",answer);
    return 0;
} 