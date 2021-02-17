/*
*Frank Gatto
*CIS3207 Assignment 1 Part B
*A discrete event simulation that models a simplified machine
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Event
{
    char type[100];
    int time;
};


int readFromConfig();
void handleEvent();
struct Event createJob();

int main()
{
    FILE *infile = fopen("config.txt", "r");
    if(infile == NULL)
    {
        printf("Could not load the config file.");
        exit(1);
    }
    int seed = readFromConfig(infile);
    int INIT_TIME = readFromConfig(infile);
    int FIN_TIME = readFromConfig(infile);
    int ARRIVE_MIN = readFromConfig(infile);
    int ARRIVE_MAX = readFromConfig(infile);
    int QUIT_PROB = readFromConfig(infile);
    int NETWORK_PROB = readFromConfig(infile);
    int CPU_MIN = readFromConfig(infile);
    int CPU_MAX = readFromConfig(infile);
    int DISK1_MIN = readFromConfig(infile);
    int DISK1_MAX = readFromConfig(infile);
    int DISK2_MIN = readFromConfig(infile);
    int DISK2_MAX = readFromConfig(infile);
    int NETWORK_MIN = readFromConfig(infile);
    int NETWORK_MAX = readFromConfig(infile);
    int currentTime = INIT_TIME;
    srand(seed);
    
    struct Event cpu[1000];
    struct Event disk1[1000];
    struct Event disk2[1000];
    struct Event network[1000];
    struct Event priorityQueue[1000];

    for(int i = 0; i < 1000; i++)
    {
        priorityQueue[i] = createJob(ARRIVE_MIN,ARRIVE_MAX);
    }

    while(currentTime < FIN_TIME)
    {
        int position = 0;
        for(int i = 0; i < 1000; i++)
        {
            if(priorityQueue[i].time <= position)
            {
                position = 1;
            }
        }
        currentTime += priorityQueue[position].time;
        if(strcmp(priorityQueue[position].type, "CPU_ARRIVAL") == 0)
        {
            int cpuPosition = 0;
            while(cpu[cpuPosition].type != NULL)
            {
                cpuPosition++;
            }
            cpu[cpuPosition] = priorityQueue[position];
        }
        else if(strcmp(priorityQueue[position].type, "DISK1_ARRIVAL") == 0)
        {
            int disk1Position = 0;
            while(disk1[disk1Position].type != NULL)
            {
                disk1Position++;
            }
            disk1[disk1Position] = priorityQueue[position];
        }
        else if(strcmp(priorityQueue[position].type, "DISK2_ARRIVAL") == 0)
        {
            int disk2Position = 0;
            while(disk2[disk2Position].type != NULL)
            {
                disk2Position++;
            }
            disk2[disk2Position] = priorityQueue[position];
        }
        else if(strcmp(priorityQueue[position].type, "NETWORK_ARRIVAL") == 0)
        {
            int networkPosition = 0;
            while(network[networkPosition].type != NULL)
            {
                networkPosition++;
            }
            network[networkPosition] = priorityQueue[position];
        }
        priorityQueue[position] = createJob(ARRIVE_MIN,ARRIVE_MAX);

    }


    return 0;
}

int readFromConfig(FILE *infile)
{
    fscanf(infile, "%s");
    return fscanf(infile, "%d");
}

struct Event createJob(min, max)
{
    int number = rand() % (5-0+1) + 5;
    struct Event event;
    if(number == 1)
    {
        struct Event event = {"DISK1_ARRIVAL", (rand() % (max - min + 1)) + max};
    }
    else if(number == 2)
    {
        struct Event event = {"DISK2_ARRIVAL", (rand() % (max - min + 1)) + max};
    }
    else if(number == 3)
    {
        struct Event event = {"NETWORK_ARRIVAL", (rand() % (max - min + 1)) + max};
    }
    else if(number == 4)
    {
        struct Event event = {"CPU_ARRIVAL", (rand() % (max - min + 1)) + max};
    }
    else 
    {
        struct Event event = {"CPU_ARRIVAL", (rand() % (max - min + 1)) + max};
    }
    return event;
}