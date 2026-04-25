#pragma once

/**
 * @file config_loader.h
 * @brief Parsing utilities for device and event configuration files.
 *
 * Provides the core data types used throughout the program and the
 * functions that load configuration from disk at startup.
 */

/**
 * @brief Represents a single key-to-command mapping.
 *
 * An Event binds a Linux input keycode to a shell command string.
 * When that key is pressed, the associated command is executed.
 *
 * @note `command` is heap-allocated via strdup() inside loadEvents().
 *       It is never freed during normal program execution.
 */
typedef struct
{
    int keycode;    /**< Linux input keycode (e.g. KEY_ENTER = 28). */
    char* command;  /**< Shell command to execute when the key is pressed. */
} Event;

/**
 * @brief A dynamic array of Event mappings.
 *
 * Returned by loadEvents() and passed around by value.
 * The `data` pointer is heap-allocated and owned by the caller.
 */
typedef struct
{
    Event* data;  /**< Pointer to the array of events. */
    size_t size;  /**< Number of events in the array. */
} EventArray;

/**
 * @brief Loads the input device path from `device.conf` into a buffer.
 *
 * Reads the first line of `device.conf` (relative to the working directory)
 * and writes it into `dest`. The path should point to a stable device node
 * such as `/dev/input/by-id/...` to survive reboots.
 *
 * @param dest      Buffer to write the device path into.
 * @param buff_size Size of `dest` in bytes. Typically sizeof(dest)
 *                  at the call site where dest is a fixed-size array.
 * @return 0 on success, 1 if the file could not be opened.
 */
int loadDev(char* dest, size_t buff_size);

/**
 * @brief Loads key-to-command mappings from `events.conf` into an EventArray.
 *
 * Parses `events.conf` (relative to the working directory), which must
 * contain one mapping per line in the format:
 *
 *     keycode=command
 *
 * Example:
 *
 *     96=rofi -show drun
 *     74=Telegram&
 *
 * The file must end with a newline. `arr->data` is heap-allocated with
 * calloc(); the caller is responsible for freeing it if needed.
 *
 * @param arr Pointer to an uninitialized EventArray. Must not be NULL.
 *            On success, arr->data and arr->size are populated.
 * @return 0 on success, 1 if the file could not be opened.
 */
int loadEvents(EventArray* arr);
