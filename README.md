# JeController
 
A lightweight Linux daemon written in C that turns any input device into a programmable macro controller. It exclusively grabs the device from the OS and executes shell commands in response to key events.
 
## How it works
 
1. Reads the target input device path from `device.conf`
2. Opens and exclusively grabs it via `EVIOCGRAB` — the device's events are hidden from the rest of the OS
3. Listens for key press events and matches them against the mappings in `events.conf`
4. Executes the matching command as a regular user (not root) via `runuser`

## Project structure
 
```
.
├── src/
│   ├── main.c                    # Entry point: device grab & event loop
│   ├── config/
│   │   └── config_loader.c       # Loads configuration from files
│   └── event/
│       ├── event_listener.c      # Matches keycodes to events
│       └── process_executor.c    # Runs commands as the configured user
└── build.sh                      # Build script
```
 
## Building
 
```bash
./build.sh
```
 
This compiles all `.c` files under `src/` and outputs the binary to `bin/ctrl`.
 
Requires GCC and standard Linux headers (`linux/input.h`).
 
## Configuration
 
### `device.conf`
 
The full path to the input device. Use a stable path from `/dev/input/by-id/` or `/dev/input/by-path/` to avoid the event number changing between reboots.
 
```
/dev/input/by-id/usb-SONiX_USB_DEVICE-event-kbd
```
 
To find the right path:
```bash
ls /dev/input/by-id/
```
 
### `events.conf`
 
One mapping per line in the format `keycode=command`. The file must end with a newline.

 Example:
```
96=rofi -show drun
78=rofi -show run
74=Telegram&
77=playerctl next&
```
 
For background commands, append `&`.
 
To find the keycode of a key:
```bash
evtest /dev/input/by-id/your-device
```
 
### `username.conf`
 
The username that commands will be executed as. Since the program runs as root, this prevents GUI applications from failing due to missing `DISPLAY`/`DBUS` session.

 Example:
```
iasonas
```
 
## Running
 
The program must run as root in order to grab the device:
 
```bash
sudo ./bin/ctrl
```
 
To run it automatically on boot, use a systemd service or add it to `/etc/rc.local`.
 
## Notes
 
- While the device is grabbed, its events are invisible to the rest of the system. To release it, stop the program.
- Commands are executed with `system()` via `runuser`, so they inherit the shell environment of the specified user.
- If a command needs a graphical session (e.g. `rofi`, `Telegram`), make sure `DISPLAY` and `DBUS_SESSION_BUS_ADDRESS` are available to that user at the time of execution.
