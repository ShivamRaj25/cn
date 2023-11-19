SERVER 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <time.h> 
#include <math.h> 
#define PORT 8080 
#define MIN_LIMIT 1 
#define MAX_LIMIT 100 
char *itoa(int num, char *buffer, int base) { 
int current = 0; 
if (num == 0) 
{ 
buffer[current++] = '0'; buffer[current] = '\0'; 
return buffer; 
} 
int num_digits = 0; 
if (num< 0) 
{ 
if (base == 10) 
{ num_digits++; 
buffer[current] = '-'; 
current++; num *= -1; 
} else 
return NULL; } 
num_digits += (int)floor(log(num) / log(base)) + 1; 
while (current <num_digits) 
{ 
int base_val = (int)pow(base, num_digits - 1 - current); int num_val = num / base_val; char value = num_val + '0'; 
buffer[current] = value; 
current++; 
num -= base_val * num_val; 
} 
buffer[current] = '\0'; 
return buffer; 
} 
int main() { 
int server_fd, new_socket, valread; struct sockaddr_in address; 
int opt = 1; 
int addrlen = sizeof(address); 
char buffer[1024] = {0}; 
char *hello = malloc(sizeof(char) * 200); 
// Creating socket file descriptor 
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
perror("socket failed"); exit(EXIT_FAILURE); 
} 
// Forcefully attaching socket to the port 8080 
if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt))) { perror("setsockopt"); 
exit(EXIT_FAILURE); 
} 
address.sin_family = AF_INET; address.sin_addr.s_addr = INADDR_ANY; address.sin_port = htons(PORT); 
// Forcefully attaching socket to the port 8080 
if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
{ 
perror("bind failed"); 
exit(EXIT_FAILURE); 
} 
if (listen(server_fd, 3) < 0) { 
perror("listen"); 
exit(EXIT_FAILURE); 
} 
if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
(socklen_t*)&addrlen)) < 0) 
{ 
perror("accept"); 
exit(EXIT_FAILURE); 
} 
printf("Connection Establishment with client was Successful!\n"); srand(time(0)); int num1 = (rand() % (MAX_LIMIT - MIN_LIMIT + 1)) + MIN_LIMIT; int num2 = (rand() % (MAX_LIMIT - MIN_LIMIT + 1)) + MIN_LIMIT; 
itoa(num1, hello, 10); 
send(new_socket, hello, strlen(hello), 0); 
sleep(5); 
itoa(num2, hello, 10); 
send(new_socket, hello, strlen(hello), 0); 
// int sum_n1_n2 = num1 + num2; 
printf("%d - number 1 \n%d - number 2\n", num1, num2); 
// snprintf(hello, 200, "\nThe sum of random numbers is: %d", sum_n1_n2); send(new_socket, hello, strlen(hello), 0); 
printf("Connection closed!\n"); 
// closing the connected socket close(new_socket); 
// closing the listening socket 
shutdown(server_fd, SHUT_RDWR); 
return 0; 
} 
CLIENT 
#include <arpa/inet.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#define PORT 8080 
int main() { 
int sock = 0, valread, client_fd; 
struct sockaddr_in serv_addr; 
char* hello = malloc(sizeof(char) * 200); char buffer[1024] = { 0 }; 
if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { printf("\n Socket creation error \n"); return -1; } 
serv_addr.sin_family = AF_INET; serv_addr.sin_port = htons(PORT); 
if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<= 0) { printf("\nInvalid address/ Address not supported \n"); 
return -1; } 
if ((client_fd 
= connect(sock, (struct sockaddr*)&serv_addr,sizeof(serv_addr)))< 0) { 
printf("\nConnection Failed \n"); return -1; 
} 
printf("Connection Establishment with server was Successful!\n"); 
valread = read(sock, buffer, 1024); int n1 = atoi(buffer); 
printf("Server: %d\n", n1); sleep(5); 
valread = read(sock, buffer, 1024); int n2 = atoi(buffer); 
printf("Server: %d\n", n2); 
int sum = n1+n2; printf("Sum = %d\n", sum); 
printf("Connection closed!\n"); 
close(client_fd); return 0; 
} 
