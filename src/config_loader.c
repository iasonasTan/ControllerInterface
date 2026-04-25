#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config_loader.h"

int loadDev(char* dest, size_t buff_size)
{
    FILE* file = fopen("device.conf", "r");
    if(file == NULL)
    {
        perror("Error loading device config file...");
        return 1;
    }

    fgets(dest, buff_size, file);

    fclose(file);

    return 0;
}

void processLine(EventArray* arr, char* id, char* command,
    int* id_idx, int* command_idx, char* line, int char_idx) {

    int eqFound = 0;
    for(int i = 0; i < char_idx; i++)
    {
        if(line[i] == '=') {
            eqFound = 1;
            continue;
        }
        
        if(line[i] != '\n')
        {
            if(eqFound) {
                if(*command_idx < 999) command[(*command_idx)++] = line[i];
            } else {
                if(*id_idx < 9) id[(*id_idx)++] = line[i];
            }
        }
    }
}

int loadEvents(EventArray* arr)
{
    FILE* file = fopen("events.conf", "r");
    if(file == NULL)
    {
        perror("Error loading events config file...");
        return 1;
    }

    arr->size = 0;
    char ch;
    while((ch = fgetc(file)) != EOF)
    {
        if(ch == '\n')arr->size++;
    }
    
    rewind(file);

    arr->data = (Event*)calloc(arr->size, sizeof(Event));
    int events_idx = 0;

    char line[1000];
    int char_idx = 0;
    while((ch = fgetc(file)) != EOF)
    {
        line[char_idx] = ch;
        char_idx++;
        if(ch == '\n')
        {
            char id[10] = {0};
            char command[1000] = {0}; 
            int id_idx = 0, command_idx = 0;

            processLine(arr, id, command, &id_idx, &command_idx, line, char_idx);
            
            id[id_idx] = '\0';
            command[command_idx] = '\0';

            Event event;
            event.keycode = atoi(id);
            event.command = strdup(command); 
            
            arr->data[events_idx++] = event;
            char_idx = 0;
        }
    }
    
    fclose(file);

    return 0;
}