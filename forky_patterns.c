#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include "forky.h"

void random_sleep(int n)
{
    srand((time(NULL)) ^ (getpid() << 16));
    int sleep_time = (rand() % 8) + 1;
    //printf("%d is sleeping for %d seconds!\n", n, sleep_time);
    sleep(sleep_time);
}

void pattern_one(int thing)
{
    FILE *fptr;
    fptr = fopen("results.txt", "w");

    pid_t pid;
    for (int i = 1; i <= thing; i++)
    {
        pid = fork();

        if (pid == 0) // equal to 0 means child
        {
            fprintf(fptr,"Process %d (PID: %d) beginning\n", i, getpid());
            random_sleep(i);
            fprintf(fptr,"Process %d (PID: %d) exiting\n", i, getpid());
            exit(0);
        }
        else if (pid > 0) // greater than 0 means parent
        {
            //printf("look at me im th parent! (PID: %d)\n", getpid());
        }
        else
        {
            exit(1); // less than 0 means something went wrong when creating fork
        }
    }

    for (int i = 1; i <= thing; i++)
    {
        wait(NULL);
    }
    fclose(fptr);
}

void pattern_two(int thing)
{
    FILE *ptr;
    ptr = fopen("results.txt", "w");

    pid_t pid;
    for (int i = 1; i <= thing; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            //fprintf(ptr,"Process %d (PID: %d) beginning\n", i, getpid());
            printf("Process %d (PID: %d) beginning\n", i, getpid());
            random_sleep(i);
            if (i < thing)
            {
                //fprintf(ptr,"Process %d (PID: %d) started Process %d (PID: %d)\n", i, getpid(), i + 1, getpid());
                printf("Process %d (PID: %d) started Process %d (PID: %d)\n", i, getpid(), i + 1, getpid());
            }
        }
        else if (pid > 0) // Parents actually can't be neglectful! 
        {
            //printf("Look at me im th parent! (PID: %d)\n", getpid());
            wait(NULL);
            //fprintf(ptr,"Process %d (PID: %d) exiting\n", i, getpid());
            printf("Process %d (PID: %d) exiting\n", i, getpid());
            exit(0); // Exit parent process after child finishes
        }
        else
        {
            exit(1);
        }
    }
    fclose(ptr);
}