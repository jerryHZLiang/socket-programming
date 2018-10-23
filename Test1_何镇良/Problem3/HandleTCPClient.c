#include <stdio.h> /* for printf() and fprintf() */
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#define RCVBUFSIZE 32   /* Size of receive buffer */

void DieWithError(char *errorMessage); /* Error handling function */
void reverseString(char *s);

void HandleTCPClient(int clntSocket)
{
    char *echoBuffer; /* Buffer for echo string */
    int recvMsgSize;  /* Size of received message */
    echoBuffer = malloc(32 * sizeof(char));
    printf("Saying hello to the client...\n");
    sleep(1);

    if (send(clntSocket, "Hello client", 12, 0) != 12)
        DieWithError("send() failed");

    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");

    echoBuffer[recvMsgSize] = '\0';
    printf("Recieve %s from client...\nSending back...\n", echoBuffer);
    reverseString(echoBuffer);
    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0) /* zero indicates end of transmission */
    {
        /* Echo message back to client */
        sleep(1);
        if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
            DieWithError("send() failed");

        /* See if there is more data to receive */
        if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv() failed");
    }
    printf("Finish and close the client socket...\n");
    close(clntSocket); /* Close client socket */
}

void reverseString(char *s)
{
    int left = 0, right = strlen(s) - 1;
    while (left < right)
    {
        char t = s[left];
        s[left++] = s[right];
        s[right--] = t;
    }
}