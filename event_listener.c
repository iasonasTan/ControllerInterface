#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "event_listener.h"
#include "config_loader.h"

// Implement handle method
void handle_event(int kc, EventArray events)
{
    printf("Handling %d\n", kc);
    for(size_t i = 0; i < events.size; i++) {
        if(events.data[i].keycode == kc) {
            printf("[{%s}]\n", events.data[i].command);
            system(events.data[i].command);
        }
    }
}