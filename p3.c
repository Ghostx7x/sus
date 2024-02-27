
#include<stdio.h>
#include<stdlib.h>

int mutex = 1, full = 0, empty = 3, x = 0;

int my_wait(int);
int my_signal(int);
void producer();
void consumer();

int main() {
    int n;
    printf("\n1.Producer\n2.Consumer\n3.Exit");
    while (1) {
        printf("\nEnter your choice:");
        scanf("%d", &n);
        switch (n) {
            case 1: 
                if ((mutex == 1) && (empty != 0))
                    producer();
                else 
                    printf("Buffer is full!!");
                break;
            case 2: 
                if ((mutex == 1) && (full != 0))
                    consumer();
                else 
                    printf("Buffer is empty!!");
                break;
            case 3: 
                exit(0);
                break;
        }
    }
    return 0;
}


int my_wait(int s) {
    return (--s);
}

int my_signal(int s) {
    return (++s);
}

void producer() {
    mutex = my_wait(mutex);
    full = my_signal(full);
    empty = my_wait(empty);
    x++;
    printf("\nProducer produces the item %d", x);
    mutex = my_signal(mutex);
}

void consumer() {
    mutex = my_wait(mutex);
    full = my_wait(full);
    empty = my_signal(empty);
    printf("\nConsumer consumes item %d", x);
    x--;
    mutex = my_signal(mutex);
}
