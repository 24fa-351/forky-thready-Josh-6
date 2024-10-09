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

    if (dup2(fileno(fptr), fileno(stderr)) == -1)
    {
        perror("Failed to redirect stderr to results.txt");
        fclose(fptr);
        exit(1);
    }

    pid_t pid;
    for (int i = 1; i <= thing; i++)
    {
        pid = fork();
        int cpid = getpid();
        if (pid == 0) // equal to 0 means child
        {
            printf("Process %d (PID: %d) beginning!\n", i, cpid);//getpid());
            fprintf(stderr, "Process %d (PID: %d) beginning!\n", i, cpid);//getpid());
            random_sleep(i);
            printf("Process %d (PID: %d) exiting\n", i, cpid);//getpid());
            fprintf(stderr, "Process %d (PID: %d) exiting!\n", i, cpid);//getpid());
            exit(0);
        }
        else if (pid > 0) // greater than 0 means parent
        {
            // printf("look at me im th parent! (PID: %d)\n", getpid());
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

    dup2(fileno(ptr), fileno(stderr));

    pid_t pid;
    pid_t child_pid;
    for (int i = 1; i < thing; i++)
    {
        pid = fork();
        //int parent_pid = getpid();
        if (pid == 0)
        {
            fprintf(stderr, "Process %d (PID: %d) beginning\n", i,  getpid());
            printf("Process %d (PID: %d) beginning\n", i, getpid());

            random_sleep(i);

            child_pid = fork();
            if (child_pid == 0)
            {
                fprintf(stderr, "Process %d (PID: %d) started Process %d (PID: %d)\n", i, getppid(), i + 1, getpid());
                printf("Process %d (PID: %d) started Process %d (PID: %d)\n", i, getppid(), i + 1, getpid());
                continue;
            }
            else if (child_pid > 0)
            {
                wait(NULL);
                fprintf(stderr, "Process %d (PID: %d) exiting\n", i, getpid());
                printf("Process %d (PID: %d) exiting\n", i, getpid());
                exit(0); // Exit parent process after child finishes
            }
            else
            {
                exit(1);
            }
        }
        else if (pid > 0) // Parents actually can't be neglectful!
        {
            // printf("Look at me im th parent! (PID: %d)\n", getpid());
            wait(NULL);
            
            //fprintf(stderr, "Process %d (PID: %d) exiting\n", i, getpid());
            //printf("Process %d (PID: %d) exiting\n", i, getpid());
            exit(0); // Exit parent process after child finishes
        }
        else
        {
            exit(1);
        }
    }
    fclose(ptr);
}