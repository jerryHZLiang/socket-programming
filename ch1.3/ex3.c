#include <netdb.h>
#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define Hostname "10.4.40.89"
int main(){
    struct hostent *he;
    struct in_addr **addr_list;
    he = gethostbyname(Hostname);
    printf("All addresses: ");
    addr_list = (struct in_addr **)he->h_addr_list;
    for(int i = 0; addr_list[i] != NULL; i++) {
        printf("%s \n", inet_ntoa(*addr_list[i]));
    }
    return 0;
}


