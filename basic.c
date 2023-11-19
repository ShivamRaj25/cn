CLIENT
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
int main()
{
int CreateSocket = 0,n = 0;
char dataReceived[1024];
struct sockaddr_in ipOfServer;
memset(dataReceived, '0' ,sizeof(dataReceived));
if((CreateSocket = socket(AF_INET, SOCK_STREAM, 0))< 0)
{
printf("Socket not created \n");
return 1;
}
ipOfServer.sin_family = AF_INET;
ipOfServer.sin_port = htons(2017);
ipOfServer.sin_addr.s_addr = inet_addr("127.0.0.1");
if(connect(CreateSocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer))<0)
{
printf("Connection failed due to port and ip problems\n");
return 1;
}
while((n = read(CreateSocket, dataReceived, sizeof(dataReceived)-1)) > 0)
{
dataReceived[n] = 0;
if(fputs(dataReceived, stdout) == EOF)
{
printf("\nStandard output error");
}
printf("\n");
}
if( n< 0)
{
printf("Standard input error \n");
}
return 0;
}
SERVER

#include <stdio.h> // standard input and output library
#include <stdlib.h> // this includes functions regarding memory allocation
#include <string.h> // contains string functions
#include <errno.h> //It defines macros for reporting and retrieving error conditions through
#include <time.h> //contains various functions for manipulating date and time
#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain
int main()
{
time_t clock;
char dataSending[1025]; 
int clintListn = 0, clintConnt = 0;
struct sockaddr_in ipOfServer;
clintListn = socket(AF_INET, SOCK_STREAM, 0); // creating socket
memset(&ipOfServer, '0', sizeof(ipOfServer));
memset(dataSending, '0', sizeof(dataSending));
ipOfServer.sin_family = AF_INET;
ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
ipOfServer.sin_port = htons(2017); // this is the port number of running server
bind(clintListn, (struct sockaddr*)&ipOfServer , sizeof(ipOfServer));
listen(clintListn , 20);
while(1)
{
printf("\n\nHi,Iam running server.Some Client hit me\n"); // whenever a request from client
clintConnt = accept(clintListn, (struct sockaddr*)NULL, NULL);
clock = time(NULL);
snprintf(dataSending, sizeof(dataSending), "%.24s\r\n", ctime(&clock)); // Printing
write(clintConnt, dataSending, strlen(dataSending));
close(clintConnt);
sleep(1);
}
return 0;
}

