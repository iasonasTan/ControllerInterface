#!/bin/bash
gcc \
    event_listener.c \
    controller.c \
    device_loader.c \
    -o ctrl
