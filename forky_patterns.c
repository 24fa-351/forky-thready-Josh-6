#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include "forky.h"

void random_sleep(int n)
{
    srand(time(NULL) ^ (getpid() << 16));
    int sleep_time = (rand() % 8) + 1;
    //printf("%d is sleeping for %d seconds!\n", n, sleep_time);
    sleep(sleep_time);
}

void pattern_one(int thing)
{
    for(int i = 1; i <= thing; i++)
    {
        pid_t pid = fork();
        
        if(pid == 0) // equal to 0 means child
        {
            printf("Process %d (PID: %d) beginning\n", i, getpid());
            random_sleep(i);
            printf("Process %d (PID: %d) exiting\n", i, getpid());
            exit(0); 
        }
        else if(pid > 0) // greater than 0 means parent
        {
            // only have one parent and dont need to do anything to it
        }
        else
        {
            exit(1); // less than 0 means something went really wrong when creating fork
        }
    }

    for (int i = 1; i <= thing; i++) 
    {
        wait(NULL);
    }
}

void pattern_two(int thing)
{

}