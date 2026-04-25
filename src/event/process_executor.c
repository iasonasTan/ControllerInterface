#include <stdio.h>
#include <stdlib.h>

int loaded = 0;
char username[100];

void execute_as_user(const char* rootCommand)
{
    if(!loaded) 
    {
        loaded = 1;
        FILE* file = fopen("username.conf", "r");

        int idx;
        char ch;
        while((ch = fgetc(file)) != EOF)
        {
            username[idx] = ch;
            idx++;
        }
        username[idx] = '\0';
    }

    char command[256];
    snprintf(command, sizeof(command), "runuser -u %s -- %s", username, rootCommand);
    system(command);
}