#pragma once

/**
 * @file event_listener.h
 * @brief Key event dispatcher.
 *
 * Provides the function that matches an incoming keycode against
 * the loaded event table and triggers the corresponding command.
 */

#include "../config/config_loader.h"

/**
 * @brief Dispatches a keycode to its associated command.
 *
 * Searches `events` linearly for an entry whose keycode matches `kc`.
 * If a match is found, the associated command is executed via
 * execute_as_user(). If no match is found, the call is a no-op.
 *
 * Called from the main event loop for every EV_KEY press event
 * (ev.value == 1).
 *
 * @param kc     The Linux input keycode of the pressed key.
 * @param events The loaded event table produced by loadEvents().
 */
void handle_event(int kc, EventArray events);
