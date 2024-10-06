#include <stdio.h>
#include <stdlib.h>
#include "forky.h"

int main(int argc, char *argv[])
{
    int num_things = atoi(argv[1]);
    int pattern = atoi(argv[2]);

    if(pattern == 1)
    {
        pattern_one(num_things);
    }
    else if(pattern == 2)
    {
        pattern_two(num_things);
    }
    else
    {
        pintf("Pattern not allowed!\n");
    }
}