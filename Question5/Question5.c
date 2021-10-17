#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* solution(char* input)
{
    int len = strlen(input), n=0, max1=0, max2=0, was1=0;

    for (int i = 0; i < len; ++i)
    {
        if(input[i] - '1'==0){
            if(n>max1){
                max2=max1;
                max1=n;
            }
            else if(n>max2&&!was1){
                max2=n;
            }
            was1=1;
            n=0;
        }
        else{
            n++;
            was1=0;
        }
    } 
    if(!was1){
        if(n>max1){
            max2=max1;
            max1=n;
        }
        else if(n>max2){
            max2=n;
        }
    } 

    if(!(max1%2) || max2 >= ((max1+1)/2))
        return "B";
    else
        return "A";
}

int main(void) {

    int max = 100000;
    char *s=(char*)malloc(max*sizeof(char));
    scanf("%s",s);
    char *ans=solution(s);
      printf("%s",ans);
    return 0;
}
