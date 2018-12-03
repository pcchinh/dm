#include "produce.h"

int Out = 0;
void Get()
{
  int item;

  sem_wait(&full_sem_mutex); 

  item = buffer[Out];
  Out = (Out + 1) % BUFF_SIZE;
  printf("...Consuming %c ...Out %d\n",item,Out);
  if(Out==EMPTY) 
    {
	
      sem_post(&empty_sem_mutex);
    }
  sleep(1);
  sem_post(&full_sem_mutex);
}

void * Consumer()
{
  int i;
  for(i = 0; i < 10; i++)
    {
      Get();
    }
}

