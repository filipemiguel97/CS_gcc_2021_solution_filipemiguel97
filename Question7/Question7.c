#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


#define BMAX 1000000
#define LSizeMAX 40000 //if n has 2 and all primes up to BMAX divided by 2;
#define NMAX 100000

struct variableList
{
   int*list; 
   int size;
   bool merge;
};
typedef struct variableList variableList;

void killVariableList(variableList** list){
    if(*list){
        free((*list)->list);
    }
    free(*list);
}

void initializeVariableList(variableList** list){
    //killVariableList(list);
    (*list) = calloc(1, sizeof(variableList));
    (*list)->size = 0;
    (*list)->list = calloc(40000, sizeof(int));
}

void SieveOfEratosthenes(int n, bool sieve[])
{
    for(int i=0; i<= n; i++)
        sieve[i] = true;

 
    for (int p = 2; p * p < n; p++)
    {
        if (sieve[p] == true)
        {
            for (int i = p * p; i < n; i += p)
                sieve[i] = false;
        }
    }
 
}

//returns gridsize
int generatePrimeGrid(int n, bool sieve[], int grid[]){
    int np=0;
    for (int p = 2; p < n; p++){
        if (sieve[p]){
            grid[np++] = p;
        }
    }

    return np;
}

void fillInputVec(int n, int input[]){
    for (int i = 0; i < n; ++i)
    {
        input[i]=(int)(((double)rand() / (double)RAND_MAX) * BMAX);
    }
}


int compare (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

//check this
int unique (int n, const char **a) {
   int dst = 0, i;
   for (i = 1; i < n; ++i) {
       if (compare(a[dst], a[i]) != 0)
           a[++dst] = a[i];
   }

   return dst + 1;
} 

int compareListSize (const void * a, const void * b)
{
    return((*(variableList*)b).size - (*(variableList*)a).size);
}

//Does not work with factors of 1. Just remove all ones and set them as their own list.
int colapseBpList(int B, const int* pList, int pListLen){
    if(B==1){
        return B;
    }
    while(B  % pList[0]){
        pList++;
        pListLen--;
        if(pListLen < 1)
            break;
    }

    if(pListLen > 0){
        return colapseBpList(B / pList[0], pList, pListLen);
    }

    return B;
}

// make sure the lists are large enough before merging
int _importToL1(variableList* l1, variableList* l2){
    for (int i = l1->size, k=0; i < l1->size + l2->size; ++i, ++k)
    {
        l1->list[i] = l2->list[k];
    }
    l1->size+=l2->size;
    l2->size=0;
    l2->merge=false;
    qsort(l1->list, l1->size, sizeof(int), compare);
}

/*void mergeLists(variableList** listStack, int i1, int i2, int* nLists, bool delete){
    if(i1==i2)
        return;

    _importToL1(listStack[i1], listStack[i2]);
    
    if(delete){
        killVariableList(&(listStack[i2]));
        if(i2 > 0){
            for (int i = i2; i < (--(*nLists)); ++i)
            {
                listStack[i] = listStack[i+1];
            }
        }
    }
    else{
        listStack[i2]->size=0;
    }
}*/

void mergeAllLists(variableList** listStack, int* nLists, int lastList, bool delete){
    int i =0, i0=0, k=0, j=0;
    while(!(listStack[i]->merge)&&(i<lastList))
        i++;
    i0=i;
    listStack[i]->merge = false;
    while(i < lastList){
        if(listStack[i]->merge){
            _importToL1(listStack[i0], listStack[i]);
            if(delete){
                killVariableList(&(listStack[i]));
                //could be faster
                for (j = i; j < (--(*nLists)); ++j)
                {
                    listStack[j] = listStack[j+1];
                }
                lastList --;
                i--;
            }
        }
        // listStack[i]->merge = false;
        i++;
    }
    //sort by list size (largest to smallest)
    // qsort(listStack,*nLists,sizeof(variableList*),compareListSize);
}
 
void factorize(int num, variableList *list, const bool primeSieve[], int nPrimes , const int primes[]){
    //isPrime?
    if(primeSieve[num]){
        if(list->size > 0){
            if(list->list[list->size-1]!=num){
                list->list[list->size++]=num;
            }
        }
        else{
            list->list[list->size++]=num;
        }
        return;
    }
    else{
        while((num  % primes[0]) && (nPrimes > 0)){
            primes++;
            nPrimes--; 
        }
        if(nPrimes > 0){
            if(list->size > 0){
                if(list->list[list->size-1]!=primes[0]){
                    list->list[list->size++]=primes[0];
                }
            }
            else{
                list->list[list->size++]=primes[0];
            }

            factorize(num / primes[0], list, primeSieve, nPrimes ,primes);
        }
        else{
            list->list[list->size++]=num;
            return;
        }
    }
}

long mod2nN(int n, int N){
    if(n == 0) 
        return 1;
    long acc=1;
    while(acc < N && n > 0){
        acc*=2;
        n--;
    }
    return (mod2nN(n, N) * (acc%N))%N;
}

void countStablePartitions(int n, int values[]){
    qsort (values, n, sizeof(int), compare);
    

    //primes
    int N = 1000000;
    if(N < 2)
        N=2;

    int allPrimes[(int)(2 * N/log(N))];
    bool sieve[N];

    SieveOfEratosthenes(N, sieve);
    int nPrimes = generatePrimeGrid(N, sieve, allPrimes);


    //more memory efficient would be to store all prime factors in a single list, and store another list of numbers saying where each prime list starts, although would be more cumbersome.

    //list algorithm
    variableList** listStack = calloc(nPrimes, sizeof(variableList*));

    int nones=0;
    //getting rid of initial 1's;
    while(values[0]==1){
        values++;
        n--;
        nones++;
    }
    // printf("%d\n", n);

    int nLists =0;
    if(n > 0){
        initializeVariableList(&(listStack[0]));
        factorize(values[0], listStack[0], sieve, nPrimes, allPrimes);
        nLists++;
    }

    int i,j,remainder, vali;
    for (i = 1; i < n; ++i)
    {
        
        vali= values[i];
        for (j = 0; j < nLists; ++j)
        {
            if(vali==1)
                break;
            if(sieve[vali]&&(j==0)){
                j=nLists;
                break;
            }
            remainder = colapseBpList(vali, listStack[j]-> list, listStack[j]-> size);
            if(remainder < vali){
                listStack[j]-> merge=true;
                vali= remainder;
            }
        }
        if(vali > 1){
            initializeVariableList(&(listStack[nLists]));
            listStack[nLists]-> merge = true;
            factorize(vali, listStack[nLists++], sieve, nPrimes, allPrimes);
            j=nLists;

        }
        mergeAllLists(listStack, &nLists, j, true);
    }

/*    for(int i= 0; i < nLists; i++){
        printf("\n\n\n\nsize(%d): %d\n\n", i, listStack[i]->size);
        for (int k = 0; k < listStack[i]->size; ++k)
        {
            printf("list(%d): %d\n",k,(listStack[i]->list)[k] );
        }
    }
*/
    for(int i= 0; i < nLists; i++){
        killVariableList(&(listStack[i]));
    }
/*    printf("\n\n\n");
    printf("Final k: %d\n", klists);*/
    long int modBase = 1000000007;
    long int res;

    res= (((nones+1)*mod2nN(nLists, modBase))%modBase+(modBase-2))%modBase;

    if(res>0){
        printf("YES\n");
        printf("%ld", res);
    } 
    else{
        printf("NO\n");
        printf("%ld", res);
    }
    return;
    free(listStack);
}

int main()
{
    //input
    int n, i;
    scanf("%d", &n);
    int answer;
    int values[n];
    for (i = 0; i < n; ++i) {
        scanf("%d", &values[i]);
    }

/*    int n = NMAX;
    int values[n];

    fillInputVec(n, values);*/
    countStablePartitions(n, values);
    return 0;
}
