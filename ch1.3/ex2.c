#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <stdlib.h>    
#include <string.h>     
#include <unistd.h>     

int main(int argc, char *argv[])
{
    int sock;                        
    struct sockaddr_in echoServAddr,peerAddr;
    unsigned short echoServPort;
    char *servIP; 
    if ((argc < 2) || (argc > 3))   
    {
       fprintf(stderr, "Usage: %s <Server IP> [<Echo Port>]\n",
               argv[0]);
       exit(1);
    }
    servIP = argv[1];              

    if (argc == 3)
        echoServPort = atoi(argv[2]);
    else
        echoServPort = 7;
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    memset(&echoServAddr, 0, sizeof(echoServAddr));   
    echoServAddr.sin_family      = AF_INET;             
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);   
    echoServAddr.sin_port        = htons(echoServPort); 

    if (bind(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    int echoServLen = sizeof(echoServAddr);
    int peerLen = sizeof(peerAddr);
    getsockname(sock, (struct sockaddr *)&echoServAddr, (socklen_t *)&echoServLen);
    getpeername(sock, (struct sockaddr *)&peerAddr, (socklen_t *)&peerLen);
    printf("connected server address = %s:%d\n", inet_ntoa(echoServAddr.sin_addr),
           ntohs(echoServAddr.sin_port));
    printf("connected peer address = %s:%d\n",
           inet_ntoa(peerAddr.sin_addr),
           ntohs(peerAddr.sin_port));
    printf("\n");    /* Print a final linefeed */

    close(sock);
    exit(0);
}
