#include <stdio.h>
#include <stdlib.h>
typedef struct stuff{
    int val;
    float b;
} Stuff;

int main(void)
{
 Stuff a;
 printf("Plz enter an integer\n");
 scanf("%d", &(a.val));
 printf("enter  a float number\n");
 scanf("%f", &(a.b));
 printf("interger = %d\n", a.val);
 printf("float = %1f\n", a.b);
return 0;
}