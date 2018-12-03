
#include "produce.h"

int In = 0;

void Put(char item)
{

  sem_wait(&empty_sem_mutex); 

  buffer[In] = item;
  In = (In + 1) % BUFF_SIZE;
  printf("Producing %c ...In %d\n",item,In);
  if(In==FULL)
    {
      sem_post(&full_sem_mutex);

    }
	sleep(1);
  sem_post(&empty_sem_mutex);

}

void * Producer()
{
  int i;
  for(i = 0; i < 10; i++)
    {
      Put((char)('A'+ i % 26));
    }
}
