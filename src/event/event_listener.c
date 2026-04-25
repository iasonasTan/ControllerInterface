#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "event/event_listener.h"
#include "event/process_executor.h"
#include "config/config_loader.h"

// Implement handle method
void handle_event(int kc, EventArray events)
{
    printf("Handling %d\n", kc);
    for(size_t i = 0; i < events.size; i++) {
        if(events.data[i].keycode == kc) {
            printf("[{%s}]\n", events.data[i].command);
            execute_as_user(events.data[i].command);
        }
    }
}