#pragma once

/**
 * @file process_executor.h
 * @brief User-context command executor.
 *
 * Provides a wrapper around system() that runs shell commands as a
 * non-root user, even though the main program runs with root privileges.
 * The target username is read once from `username.conf` and cached.
 */

/**
 * @brief Executes a shell command as the configured non-root user.
 *
 * On the first call, reads the username from `username.conf` (relative
 * to the working directory) and caches it for subsequent calls.
 * The command is then run via:
 *
 *     runuser -u <username> -- <command>
 *
 * This is necessary because the program runs as root (required for
 * EVIOCGRAB), but GUI applications such as rofi or Telegram need to
 * run under the user's graphical session to access DISPLAY and D-Bus.
 *
 * @param command The shell command to execute. For background execution,
 *                append `&` to the command string in `events.conf`
 *                (e.g. `"Telegram&"`).
 *
 * @note Uses system(), which spawns a shell. The command string is not
 *       sanitised — only add trusted entries to `events.conf`.
 * @note The username buffer is a static global; this function is not
 *       thread-safe.
 */
void execute_as_user(const char* command);
