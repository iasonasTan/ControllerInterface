#pragma once

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
 * @brief Loads events into the provided buffer.
 * Takes an empty EventArray*.
 * arr should NOT be null.
 * @return 0 on success, 1 on error.
 */
int loadEvents(EventArray* arr);

/**
 * @brief Loads the device path into the provided buffer.
 * @param buf Buffer to write the path into.
 * @return 0 on success, 1 on error.
 */
int loadDev(char* dest, size_t buff_size);