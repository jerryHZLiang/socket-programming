#include <stdio.h>
#include <stdlib.h>
#include "ex4.h"

int main(){
    MSG *mp, m = {4, 1, 0};  //a =4 s= 4 -> fp
    char *fp, *tp;// fp指向m中的s[0], tp指向mp中的s[0]
    mp = (MSG *)malloc(sizeof(MSG));         // tp在mp s[0]-s[1]
    for (fp = (char *)m.s, tp = (char *)mp->s; tp < (char *)(mp+1);)
           *tp++ = *fp++;//*(tp++) = *(fp++);   //fp=1 -> tp
printf("\nprint results:\n");
printf("\nm={%d, %d, %d}\n", m.a, m.s[0], m.s[1]);
printf("\nmp={%d, %d, %d}\n", mp->a, mp->s[0], mp->s[1]);

    return 0;
}
