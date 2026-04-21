#include <stdio.h>
#include <stdlib.h>

#include "device_loader.h"

int loadID() {
    FILE* file = fopen("device.conf", "r");
    if(file == NULL) {
        perror("Error loading configuration file...");
        return 1;
    }

    char line[4];

    fgets(line, sizeof(line), file);

    fclose(file);

    return atoi(line);
}