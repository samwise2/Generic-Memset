#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void memsetHelper(void *src, void *dest)
{
    //char *d = (char*)dest;
    //printf("%c",*(char*)dest);
    //char *s = (char*)src;
    *(char*)src = *(char*)dest;
}

void intHelper(void *src, void*dest)
{
    *((int*)src) = *((int*)dest);
}

void map(void *src, size_t n, size_t srcb, void *dest, size_t destb,
         void (*f)(void*,void*)) {
    printf("%d\n",*((int*)dest));
    for (size_t i = 0; i < n; ++i) {
        f(src,dest);
        src += srcb;
        dest += destb;
    }
}


void reduce(void *src, size_t n, size_t srcb, void *dest, void (*f)(void*,void*)) {
    if (n == 1) {
        f(src,dest);
        return;
    }
    reduce(src+srcb, n-1, srcb, dest, f);
    f(src,dest);
}

// Same as reduce, but function application is done before the recursion
void reverseReduce(void *src, size_t n, size_t srcb, void *dest, void (*f)(void*,void*)) {
    f(src, dest);
    if (n == 1) return;
    reverseReduce(src+srcb, n-1, srcb, dest, f);
}

void iterativeMemSet(void *arr, size_t n, size_t size, char c)
{
    char *myArr = arr;
    for(int i=0; i<n;i++) {
        myArr[i] = c;
    }
    
}

void genericMemset(void *arr, size_t n, size_t size, void * fill)
{
    //void *a = malloc(n*size);
    map(arr, n, size, fill, 0, memsetHelper);
}


int dummy(void*x)
{
    int b = *((int*)x);
    return b;
}

int main () {
    /*int x=5;
    int *q = &x;
    int y = dummy(q);
    printf("y: %d", y);*/
    
    char c = 'c';
    char *d = &c;
    
    char *a = malloc(10*sizeof(char));
    iterativeMemSet(a, 10, sizeof(char), 97);
    for(int i=0;i<10;i++) printf("%c",a[i]);
    printf("\n");
    char *b = malloc(10*sizeof(char));
    //int d = 97;
    //char *c = 97;
    //printf("%c",c);
    genericMemset(b, 10, sizeof(char),d);
    for(int i=0;i<10;i++) printf("%c",b[i]);
    printf("\n");
    int *intTest = malloc(5*sizeof(int));
    int x=0;
    int *q = &x;
    genericMemset(intTest, 5, sizeof(int), q);
    /*memset(intTest, 0, 5*sizeof(int));
    //int x[5] = {1,2,3,4,5};
    //memset(x, 0, 5*sizeof(int));
    //genericMemset(intTest, 5, sizeof(int), 0);
    char stringEx[] = {'w', 'h', 'y',0};
    memset(stringEx,'$',3);*/
    for(int i=0;i<5;i++)printf("%d",intTest[i]);
    
}
