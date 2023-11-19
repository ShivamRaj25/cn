#include<stdio.h>

char data[20], div[20], temp[4], total[100];
int i, j, datalen, divlen, len, flag = 1;

void check();

int main() {
    printf("Enter the total bit of data: ");
    scanf("%d", &datalen);
    printf("\nEnter the total bit of divisor: ");
    scanf("%d", &divlen);
    len = datalen + divlen - 1;

    printf("\nEnter the data: ");
    for (i = 0; i < datalen; i++) {
        scanf(" %c", &data[i]);
        total[i] = data[i];
        temp[i] = data[i];
    }

    printf("\nEnter the divisor: ");
    scanf("%s", div);

    for (i = datalen; i < len; i++)
        total[i] = '0';

    check();  // Check for CRC

    for (i = 0; i < divlen; i++)
        temp[i + datalen] = data[i];

    printf("\nTransmitted Code Word: %s", temp);

    printf("\n\nEnter the received code word: ");
    scanf("%s", total);

    check();  // Check for CRC

    for (i = 0; i < divlen - 1; i++)
        if (data[i] == '1') {
            flag = 0;
            break;
        }

    if (flag == 1)
        printf("\nSuccessful!!");
    else
        printf("\nReceived code word contains errors...\n");

    return 0;
}

void check() {
    for (j = 0; j < divlen; j++)
        data[j] = total[j];

    while (j <= len) {
        if (data[0] == '1') {
            // XOR operation
            for (i = 1; i < divlen; i++)
                data[i] = ((data[i] == div[i]) ? '0' : '1');
        }

        // Left shift data word by 1 after div
        for (i = 0; i < divlen - 1; i++)
            data[i] = data[i + 1];

        // Replace empty right by total
        data[i] = total[j++];
    }
}
