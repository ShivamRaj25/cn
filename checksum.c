#include <stdio.h>
#include <string.h>

int main() {
    char a[20], b[20];
    char sum[20], complement[20];
    int i, length;

    printf("Enter first binary string\n");
    scanf("%s", a);

    printf("Enter second binary string\n");
    scanf("%s", b);

    if (strlen(a) == strlen(b)) {
        length = strlen(a);
        char carry = '0';

        for (i = length - 1; i >= 0; i--) {
            // Binary addition with carry
            sum[i] = (a[i] ^ b[i] ^ carry);
            carry = (a[i] & b[i]) | ((a[i] ^ b[i]) & carry);
        }

        printf("\nSum=%s", sum);

        for (i = 0; i < length; i++) {
            // One's complement calculation
            complement[i] = (sum[i] == '0') ? '1' : '0';
        }

        // Invert the carry for checksum
        carry = (carry == '1') ? '0' : '1';

        printf("\nChecksum=%c%s\n", carry, complement);
    } else {
        printf("\nWrong input strings\n");
    }

    return 0;
}
