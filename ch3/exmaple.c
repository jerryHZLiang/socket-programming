#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define STDIN 0  // file descriptor for standard input

int main(void) {
    fd_set rfds;
    struct timeval tv;
    int retval;
    char buf[255];
    int len;
    /* Watch stdin (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
//we must turn on the interested bits (by calling FD_SET) each time we call select.
    FD_SET(0, &rfds);

    /* Wait up to five seconds. */
    tv.tv_sec = 5;
    tv.tv_usec = 0;

while(1){
        retval = select(STDIN+1, &rfds, NULL, NULL, &tv);
    /* Don’t rely on the value of tv now! */

    if (retval == -1)
        perror("select()");
    else if (retval){
        fgets(buf, sizeof(buf), stdin);
        len = strlen(buf) - 1;
        if (buf[len] == '\n'){
            buf[len] = '\0';
        }
        if(strcmp(buf, "quit") == 0){
            printf("exit\n");
            exit(EXIT_FAILURE);
        }else{
            printf("'%s' was read from stdin.\n", buf);
        }
    }else{
        printf("No data within five seconds.\n");
        exit(EXIT_FAILURE);
    }     
}

    return 0;
}
