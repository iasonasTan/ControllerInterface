#!/bin/bash
gcc \
    event_listener.c \
    controller.c \
    config_loader.c \
    -o ctrl
