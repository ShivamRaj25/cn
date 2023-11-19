
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

int x = 0;

void capture() {
    exit(0);
}

int get() {
    return x;
}

void put() {
    x++;
}

void* node(void* p) {
    int name;
    int seq1, seq2, i = 0;
    
    name = atoi((char*)p);

    while (1) {
        seq1 = get();
        seq2 = get();

        if (seq1 == seq2) {
            put();
            seq1 = get();
            printf("station %d transmitting frame %d\n", name, ++i);
            sleep(3);
            seq2 = get();

            if (seq1 != seq2) {
                printf("station %d collision occurred %d\n", name, i--);
            }
        }

        sleep(3);
    }

    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, node, "1");
    pthread_create(&t2, NULL, node, "2");
    pthread_create(&t3, NULL, node, "3");

    while (1);

    return 0;
}
