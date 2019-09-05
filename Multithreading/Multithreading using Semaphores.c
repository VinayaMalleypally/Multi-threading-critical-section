#define _REENTRANT
/*header files*/
#include <pthread.h>
#include<semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>
struct rusage mytiming;
struct timeval mytimeval;
/*Tested on linux 1/23/11 */
/* compile with gcc -ofname thread-template.c -lpthread */

struct shared_dat
   {
   int value;     /* shared variable to store result*/
   };

sem_t lock;
struct shared_dat  *counter;
int temp;
/* initializing the mutex lock */
/****************************************************************
 * * This function increases the value of shared variable "counter"
 *   by one 2500000 times
 *   ****************************************************************/
void * thread1(void *arg)
{       int count100=0;
        int line = 0;
        while (line < 2500000)
           {
        /* inserting semaphore lock and entering the critical section*/

        sem_wait(&lock);
        if((counter->value%100 == 0)&&(line+100<2500000)){
                counter->value = counter->value+100;
                counter->value = counter->value*2;
                counter->value = counter->value/2;
        /*incrementing the counter100 which keeps track of increments of 100 */
                count100++;
                line=line+100;
        }
        else{
            counter->value++;
            counter->value = counter->value * 2;
            counter->value = counter->value / 2;
            line++;

         }
        sem_post(&lock);
        /*releasing semaphore lock*/
        }
        printf("number of 100 increments: %d\n",count100);
        printf(" from thread1 counter  =  %d\n", counter->value);
        return(NULL);
}
/****************************************************************
 * This function increases the value of shared variable "counter"
 * by one 2500000 times
 * ****************************************************************/
void * thread2(void *arg)
{
        int line = 0;

        while(line < 2500000)
        {
           /*inserting the semaphore lock */
           /* and entering the  Critical Section*/
            sem_wait(&lock);
            counter->value++;
            counter->value = counter->value * 2;
            counter->value = counter->value / 2;
            sem_post(&lock);
        /*releasing semaphore lock*/
            line++;
        }

        printf("from thread2 value of counter = %d\n", counter->value);
        return(NULL);
}

void * thread3(void *arg)
{
        int line = 0;

        while(line < 2500000)
        {
           /*inserting the semaphore wait*/
           /* and entering the  Critical Section*/
            sem_wait(&lock);
            counter->value++;
            counter->value = counter->value * 2;
            counter->value = counter->value / 2;
            sem_post(&lock);
           /*releasing semaphore lock*/
           line++;
        }

        printf("from thread3 value of counter = %d\n", counter->value);
        return(NULL);
}

/****************************************************************
 * *                  Main Body                                    *
 * ****************************************************************/
 main()
{
        int             r=0;
        int             i;
        int             shmid;       /* shared memory ID */
        pthread_t       tid1[1];     /* process id for thread 1 */
        pthread_t       tid2[1];     /* process id for thread 2 */
        pthread_t       tid3[1];
        sem_init(&lock,0,1);
        counter = (struct shared_dat *) malloc(sizeof(struct shared_dat));
        /* initialize shared memory to 0 */
        counter->value = 0 ;
        printf("1 - I am here %d in pid %d\n",r,getpid());
        fflush(stdout);
         /* Required to schedule thread independently.
        *  Otherwise use NULL in place of attr. */
        /* Create the threads using default attributes */
        pthread_create(&tid1[0], NULL, thread1, NULL);
        pthread_create(&tid2[0], NULL, thread2, NULL);
        pthread_create(&tid3[0], NULL, thread3, NULL);

        /* Wait for the threads to finish */
        pthread_join(tid1[0], NULL);
        pthread_join(tid2[0], NULL);
        pthread_join(tid3[0], NULL);
        printf("from parent value of counter  =  %d\n", counter->value);
        printf("---------------------------------------------------------------------------\n");
        printf("\t\t    End of simulation\n");
        printf("Time for execution: \n");
        getrusage(RUSAGE_SELF, &mytiming);
        printf("Time used is sec: %d, usec %d\n",mytiming.ru_utime.tv_sec,
        mytiming.ru_utime.tv_usec);
        printf("System Time used is sec: %d, usec %d\n",mytiming.ru_stime.tv_sec,mytiming.ru_stime.tv_usec);
        exit(0);

}

/*SEMAPHORES
TIME for execution:
RUNTIME used is sec:0, usec 66989
SYSTEM TIME is sec:0, usec 2999
MUTEX_LOCKS
TIME for execution:
RUNTIME used is sec:0, usec 62990
SYSTEM TIME is sec:0, usec 0

The Mutex_lock solution for Critical Section Problem differs from that of the semaphore solution to the Critical section problem.
This is because Mutex_lock provides exclusive access to a resource and
Semaphore helps to maintain the access by multiple processes to a common resource in a multiprogramming Operating System*/
