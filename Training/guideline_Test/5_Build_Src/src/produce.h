#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

#define BUFF_SIZE 4
#define FULL 0
#define EMPTY 0
char buffer[BUFF_SIZE];

extern int Out;
sem_t empty_sem_mutex; //producer semaphore
sem_t full_sem_mutex; //consumer semaphore
void * Producer();
void Put(char item);
void Get();
void * Consumer();
