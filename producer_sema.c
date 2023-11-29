#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 8

sem_t semEmpty;
sem_t semFull;
sem_t mutexBuffer;

int buffer[10];
int count = 0;

void *producer(void *args)
{
    while (1)
    {
        // Produce
        int x = rand() % 100;
        sleep(1);

        // Add to the buffer
        sem_wait(&semEmpty);
        sem_wait(&mutexBuffer);

        // pthread_mutex_lock(&mutexBuffer);
        buffer[count] = x;
        count++;
        printf("Produced %d\n", x);

        // pthread_mutex_unlock(&mutexBuffer);
        sem_post(&mutexBuffer);

        sem_post(&semFull);
    }
}

void *consumer(void *args)
{
    while (1)
    {
        int y;

        // Remove from the buffer
        sem_wait(&semFull);
        sem_wait(&mutexBuffer);
        y = buffer[count - 1];
        count--;
        sem_post(&mutexBuffer);
        sem_post(&semEmpty);

        // Consume
        printf("Consumed %d\n", y);
        
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    sem_init(&mutexBuffer, 0, 1);
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);
    int i;
    for (i = 0; i < THREAD_NUM; i++)
    {
        if (i < 6)
        {
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0)
            {
                perror("Failed to create thread");
            }
        }
        else
        {
            if (pthread_create(&th[i], NULL, &consumer, NULL) != 0)
            {
                perror("Failed to create thread");
            }
        }
    }
    for (i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join thread");
        }
    }
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    sem_destroy(&mutexBuffer);
    return 0;
}