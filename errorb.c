#include <stdio.h>
int main() { 
int data[7];
 int encodedData[11], receivedData[11], c1, c2, c3, c, i;
  printf("Enter 7 bits of data one by one\n"); 
  for (i = 0; i < 7; i++) 
  scanf("%d", &data[i]); 
 encodedData[2] = data[0]; encodedData[4] = data[1]; 
 encodedData[5] = data[2]; encodedData[6] = data[3]; 
 encodedData[8] = data[4]; encodedData[9] = data[5]; 
 encodedData[10] = data[6]; 
 encodedData[0] = encodedData[2] ^ encodedData[4] ^ encodedData[6] ^ encodedData[8] ^ encodedData[10]; encodedData[1] = encodedData[2] ^ encodedData[5] ^ encodedData[6] ^ encodedData[9] ^ encodedData[10]; encodedData[3] = encodedData[4] ^ encodedData[5] ^ encodedData[6]; encodedData[7] = encodedData[8] ^ encodedData[9] ^ encodedData[10]; printf("\nEncoded data is\n"); 
 for (i = 0; i < 11; i++) 
 printf("%d", encodedData[i]); 
 printf("\n\nEnter received data bits one by one\n"); 
 for (i = 0; i < 11; i++) 
 scanf("%d", &receivedData[i]);
  c1 = receivedData[0] ^ receivedData[2] ^ receivedData[4] ^ receivedData[6] ^ receivedData[8] ^ receivedData[10]; c2 = receivedData[1] ^ receivedData[2] ^ receivedData[5] ^ receivedData[6] ^ receivedData[9] ^ receivedData[10]; c3 = receivedData[3] ^ receivedData[4] ^ receivedData[5] ^ receivedData[6]; 
  c = c3 * 4 + c2 * 2 + c1; 
  if (c == 0) { printf("\nNo error while transmission of data\n"); } 
  else { printf("\nError on position %d", c); 
  printf("\nData sent : ");
   for (i = 0; i < 11; i++)
    printf("%d", encodedData[i]);
     printf("\nData received : "); 
     for (i = 0; i < 11; i++) printf("%d", receivedData[i]); printf("\nCorrect message is\n");
     if (receivedData[c - 1] == 0) 
     receivedData[c - 1] = 1; 
     else receivedData[c - 1] = 0; 
     for (i = 0; i < 11; i++) {
      printf("%d", receivedData[i]); 
      } } return 0; 
      }