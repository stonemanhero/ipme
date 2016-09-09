#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define IP "163.172.54.116"
#define BUFFER_REQUEST 100
#define BUFFER_RESPONSE 1000

void print_ip(char *response);

int main()
{
	int socket_desc;
    struct sockaddr_in server;
    char request[BUFFER_REQUEST];
    char response[BUFFER_RESPONSE];

    bzero(request, BUFFER_REQUEST);
    bzero(response, BUFFER_RESPONSE);
       
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("/nError: can\'t create socket.\n\n");
        exit(-1);
    }
       
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    //make request string
    strcat(request, "GET /ipme/ipme.php");
	strcat(request, " HTTP/1.1\r\n");
	strcat(request, "Host: ");
	strcat(request, "www.pirotski.com");
	strcat(request, "\r\nConnection: close");
	strcat(request, "\r\n\r\n");
     
    if(connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
    	printf("\nError: Can\'t connect to server!\n\n");
        exit(-1);
    }
       
    if(send(socket_desc, request, strlen(request), 0) < 0)
    {
        printf("\nError: Can\'t send request!\n");
        exit(-1);
    }

    recv(socket_desc, response, BUFFER_RESPONSE, 0);

    print_ip(response);

    close(socket_desc);
}


void print_ip(char *response)
{
	char *p1 = strstr(response, "[ip]")+4;

    int i=-1;
    while(p1[++i] != '[')
    	printf("%c", p1[i]);

    printf("\n");
}
