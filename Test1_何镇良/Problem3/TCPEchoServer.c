#include <arpa/inet.h> /* for sockaddr_in and inet_ntoa() */
#include <fcntl.h>
#include <stdio.h>  /* for printf() and fprintf() */
#include <stdlib.h> /* for atoi() and exit() */
#include <string.h> /* for memset() */
#include <sys/ioctl.h>
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h> /* for close() */

#define MAXPENDING 5 /* Maximum outstanding connection requests */

void DieWithError(char *errorMessage); /* Error handling function */
void HandleTCPClient(int clntSocket);  /* TCP client handling function */

void reverseStr(char *str)
{
	int length;			
	char *p1;
	char *p2;
 
	length = strlen(str);		//获取字符串长度
	p1	   = str;				//p1指向字符串首地址
	p2     = str + length - 1;	//p2指向字符串尾地址
	if (str == NULL)		
	{
		printf("空指针错误！");
		return ;
	}
	while (p1 < p2)				//当p1地址小于p2地址时执行循环
	{
		char c = *p1;			
		*p1	   = *p2;				//完成指针指向地址的值的交换
		*p2    = c;
		p1++;						//交换完毕后p1指针指向下一个字符地址
		p2--;						//交换完毕后p2指针指向上一个字符地址
	}
 
}

int main(int argc, char *argv[])
{

    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
    unsigned short echoServPort;     /* Server port */
    unsigned int clntLen;            /* Length of client address data structure */
    char *msg;
    int yes = 1;
    if (argc != 2) /* Test for correct number of arguments */
    {
        fprintf(stderr, "Usage:  %s <Server Port>\n", argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]); /* First arg:  local port */

    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");
    if (setsockopt(servSock, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(int)) == -1)
        DieWithError("setsockopt() failed");

    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(echoServPort);      /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) <
        0)
        DieWithError("bind() failed");

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");

    char buffer[128];
    fd_set rfds;
    int retval, nread;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    FD_SET(servSock, &rfds);

    printf("input 'quit' to quit the server.\n");
    for (;;) /* Run forever */
    {      /* Set the size of the in-out parameter */
        // clntLen = sizeof(echoClntAddr);
        // /* Wait for a client to connect */
        // if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
        //     DieWithError("accept() failed");
        // int sendnum=0;
        // //if(sendnum=!=strlen(msg))
        // recv(clntSock, msg, strlen(msg)-1, 0);
        // msg = reverseStr(msg);  
        // send(clntSock, msg, sizeof(msg)-1, 0);
        // HandleTCPClient(clntSock);
        // }
        FD_ZERO(&rfds);
        // select.
        FD_SET(0, &rfds);
        FD_SET(servSock, &rfds);
        retval = select(FD_SETSIZE, &rfds, (fd_set *)0, (fd_set *)0,
                        (struct timeval *)0); //&tv);

        if (retval == -1)
            DieWithError("select()");
        else if (retval)
        {
            if (FD_ISSET(0, &rfds))
            {
                ioctl(0, FIONREAD, &nread);
                if (nread == 0)
                {
                    printf("There is no input\n");
                    continue;
                }
                nread = read(0, buffer, nread);
                nread--;
                buffer[nread] = '\0';
                if (strcmp(buffer, "quit") == 0)
                {
                    printf("The server will be shut down in 1 second...\n");
                    sleep(1);
                    exit(1);
                }
                else if (strcmp(buffer, "RETURN") == 0)
                {   FD_CLR(0, &rfds);
                    printf("The information will be ended\n");
                    close(1);    
                }
                    printf("read %d letter from keyboard: %s\n", nread, buffer);
            }
            if (FD_ISSET(servSock, &rfds))
            {
                /* Set the size of the in-out parameter */
                clntLen = sizeof(echoClntAddr);

                /* Wait for a client to connect */
                if ((clntSock = accept(servSock, (struct sockaddr *)&echoClntAddr,
                                       &clntLen)) < 0)
                    DieWithError("accept() failed");
                printf("\nHandling client %s:%d\n", inet_ntoa(echoClntAddr.sin_addr),
                       ntohs(echoClntAddr.sin_port));
                   HandleTCPClient(clntSock);
            }
        }
        else
        {
            printf("Out of time\n");
            break;
        }
    }
}
