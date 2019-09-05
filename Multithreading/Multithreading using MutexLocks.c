#define _REENTRANT
 /*header files*/
#include <pthread.h>
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

pthread_mutex_t m;
struct shared_dat  *counter;
int temp;
/* initializing the mutext lock */
/****************************************************************
 * * This function increases the value of shared variable "counter"
 *   by one 2500000 times
 *   ****************************************************************/
void * thread1(void *arg)
{       int count100=0;
        int line = 0;
        while (line < 2500000)
           {
        /* inserting trylock and checking if it is already used */
        int check1=pthread_mutex_trylock(&m);
        if(check1==0){
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
        pthread_mutex_unlock(&m);
        }
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
           /*inserting the trylock and checking if its failure or success. */
           /* and entering the  Critical Section*/
        int check2 = pthread_mutex_trylock(&m);
if(check2==0){
            counter->value++;
            counter->value = counter->value * 2;
            counter->value = counter->value / 2;
            pthread_mutex_unlock(&m);
line++;
}
}

           printf("from thread2 value of counter = %d\n", counter->value);
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
        pthread_mutex_init(&m,NULL);
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

        /* Wait for the threads to finish */
    pthread_join(tid1[0], NULL);
    pthread_join(tid2[0], NULL);
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
