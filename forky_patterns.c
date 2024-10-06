#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include "forky.h"

void random_sleep()
{
    srand(time(NULL) ^ (getpid() << 16));
    int sleep_time = (rand() % 8) + 1;
    sleep(sleep_time);
}

void pattern_one(int thing)
{

}

void pattern_two(int thing)
{

}