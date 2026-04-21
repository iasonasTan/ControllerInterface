#pragma once

/**
 * @brief Returns input device ID.
 * @return int device ID as integer.
 */
int loadID();

/**
 * @brief Represents an event.
 * That contains a keycode that triggers the listener
 * and a command to execute then.
 */
typedef struct
{
    int keycode;
    char* command;
} Event;

/**
 * @brief Represents an event array.
 * That contains an event array and
 * the size of it.
 */
typedef struct
{
    Event* data;
    size_t size;
} EventArray;

/**
 * @brief Returns an EventArray with loaded events.
 * @return EventArray events to use.
 */
EventArray loadEvents();