#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/ioctl.h>

#include "event_listener.h"
#include "config_loader.h"

int main()
{
    // That stores the path.
    // Path's length must be less than than this array's length.
    char dev[1000];
    int loaded = loadDev(dev, sizeof(dev));
    if(loaded != 0) {
        return 1;
    }

    int fd;
    struct input_event ev;

    fd = open(dev, O_RDONLY);
    if(fd == -1)
    {
        perror("Error reading event file");
	    return 1;
    }

    if(ioctl(fd, EVIOCGRAB, 1) == -1)
    {
        perror("EVIOCGRAB error");
	    return 1;
    }

    EventArray events;
    int loadRet = loadEvents(&events);

    printf("Listening...\n");
    while(1)
    {
        ssize_t n = read(fd, &ev, sizeof(ev));
        if(n < (ssize_t)sizeof(ev)) break;

        if(ev.type == EV_KEY && ev.value == 1)
        {
            printf("Pressed %d\n", ev.code);
            handle_event(ev.code, events); // Implemented in event_listener.c
        }

    }
    
    ioctl(fd, EVIOCGRAB, 0);
    close(fd);
    return 0;

}
