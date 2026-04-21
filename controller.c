#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/ioctl.h>

#include "event_listener.h"
#include "device_loader.h"

int main()
{
    int dev_id = loadID();
    char dev[256];
    snprintf(dev, sizeof(dev), "/dev/input/event%d", dev_id);

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

    printf("Listening...\n");
    while(1)
    {
        ssize_t n = read(fd, &ev, sizeof(ev));
        if(n < (ssize_t)sizeof(ev)) break;

        if(ev.type == EV_KEY && ev.value == 1)
        {
            printf("Pressed %d\n", ev.code);
            handle_event(ev.code); // Implemented in event_listener.c
        }

    }
    
    ioctl(fd, EVIOCGRAB, 0);
    close(fd);
    return 0;

}
