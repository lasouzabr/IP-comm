/*
 * udpsend.c
 *
 *  Created on: Sep 21, 2015
 *      Author: leonardo
 */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFSIZE 255
 void ERRO(char *mess) { perror(mess); exit(1); }

 int main(int argc, char *argv[]) {
     int sock;
     struct sockaddr_in echoserver;
     struct sockaddr_in echoclient;
     char buffer[BUFFSIZE];
     unsigned int echolen, clientlen;
     int received = 0;
     char LAPTOP[]="192.168.1.212";

     	 	 	 /* Create the UDP socket */
                if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
                  ERRO("Failed to create socket");
                }
                /* Construct the server sockaddr_in structure */
                memset(&echoserver, 0, sizeof(echoserver));       /* Clear struct */
                echoserver.sin_family = AF_INET;                  /* Internet/IP */
                echoserver.sin_addr.s_addr = inet_addr(LAPTOP);  /* IP address */
                echoserver.sin_port = htons(atoi("1977"));       /* server port */


                /* Send the word to the server */
                echolen = strlen("KEY1_VALUE=0");
                if (sendto(sock,"KEY1_VALUE=0", echolen, 0,
                           (struct sockaddr *) &echoserver,
                           sizeof(echoserver)) != echolen) {
                 ERRO("Mismatch in number of sent bytes");
                }


                /* Receive the word back from the server */
                fprintf(stdout, "Received: ");
                clientlen = sizeof(echoclient);
                if ((received = recvfrom(sock, buffer, BUFFSIZE, 0,
                                         (struct sockaddr *) &echoclient,
                                         &clientlen)) != echolen) {
                  ERRO("Mismatch in number of received bytes");
                }
                /* Check that client and server are using same socket */
                if (echoserver.sin_addr.s_addr != echoclient.sin_addr.s_addr) {
                  ERRO("Received a packet from an unexpected server");
                }
                buffer[received] = '\0';        /* Assure null terminated string */
                fprintf(stdout, buffer);
                fprintf(stdout, "\n");
                close(sock);
                exit(0);
              }

