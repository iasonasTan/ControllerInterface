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
        return -1;
    }

    fgets(dest, buff_size, file);

    fclose(file);

    return 0;
}

EventArray loadEvents()
{
    FILE* file = fopen("events.conf", "r");
    if(file == NULL)
    {
        perror("Error loading events config file...");
        // TODO stop app
    }

    size_t events_len = 0;
    char ch;
    while((ch = fgetc(file)) != EOF)
    {
        if(ch == '\n')events_len++;
    }
    
    rewind(file);

    Event* events = (Event*)calloc(events_len, sizeof(Event));
    int events_idx = 0;

    char line[1000];
    int char_idx = 0;
    while((ch = fgetc(file)) != EOF)
    {
        line[char_idx] = ch;
        char_idx++;
        if(ch == '\n')
        {
            int eqFound = 0;
            char id[10] = {0};
            char command[1000] = {0}; 
            int id_idx = 0, command_idx = 0;

            for(int i = 0; i < char_idx; i++)
            {
                if(line[i] == '=') {
                    eqFound = 1;
                    continue;
                }
                
                if(line[i] != '\n')
                {
                    if(eqFound) {
                        if(command_idx < 999)
                            command[command_idx++] = line[i];
                    } else {
                        if(id_idx < 9)
                            id[id_idx++] = line[i];
                    }
                }
            }
            
            id[id_idx] = '\0';
            command[command_idx] = '\0';

            Event event;
            event.keycode = atoi(id);
            event.command = strdup(command); 
            
            events[events_idx++] = event;
            char_idx = 0;
        }
    }
    
    fclose(file);

    return (EventArray){ .data = events, .size = events_len };
}