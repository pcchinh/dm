

#include "produce.h"


int main()
{
  pthread_t produce,consumer;
  //khoi tao semaphores

  sem_init(&empty_sem_mutex,0,1);
  sem_init(&full_sem_mutex,0,0);

  //int pthread_create(pthread_t * thread, pthread_attr_t * attr, void * (*start_routine)(void *), void * arg);
  //  pthread_attr_t dat la NULL neu giu thuoc tinh thread mac dinh 
  pthread_create(&produce, NULL,Producer, NULL); // tao thread cho produce
    
  pthread_create(&consumer, NULL,Consumer, NULL);// tao thread cho consumer
   
  pthread_join(produce, NULL); /*cho  producer ket thuc */
    
  pthread_join(consumer, NULL); /* cho consumer ket thuc */
  //huy semaphores
  sem_destroy(&empty_sem_mutex);
  sem_destroy(&full_sem_mutex);

  //thoat thread

  pthread_exit(NULL);
  return 0;
}
