#include<stdio.h>

int main() {
    int w, i, f, frames[50];

    printf("Enter window size: ");
    scanf("%d", &w);

    printf("\nEnter number of frames to transmit: ");
    scanf("%d", &f);

    printf("\nEnter %d frames: ", f);

    for (i = 0; i < f; i++) // Fix: Start the loop from 0
        scanf("%d", &frames[i]);

    printf("\nWith sliding window protocol, the frames will be sent in the following manner (assuming no corruption of frames)\n\n");
    printf("After sending %d frames at each stage, sender waits for acknowledgment sent by the receiver\n\n", w);

    for (i = 0; i < f; i++) {
        if ((i + 1) % w == 0) { // Fix: Check if (i + 1) is a multiple of w
            printf("%d\n", frames[i]);
            printf("Acknowledgement of above frames sent is received by sender\n\n");
        } else {
            printf("%d ", frames[i]);
        }
    }

    if (f % w != 0)
        printf("\nAcknowledgement of above frames sent is received by sender\n");

    return 0;
}
