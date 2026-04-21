#include <stdio.h>
#include <stdlib.h>

#include "event_listener.h"

// Implement handle method
void handle_event(int kc)
{
    int KC_ENTER = 96;
    int KC_PLUS  = 78;
    int KC_MINUS = 74;
    int KC_MULTI = 55;
    int KC_NINE  = 73;
    int KC_SIX   = 77;
    int KC_THREE = 81;
    int KC_DOT   = 83;

    printf("Handling %d\n", kc);
    if(kc == KC_ENTER) {
        system("runuser -u iasonas -- xfce4-terminal &");
    }
    if(kc == KC_MINUS) {
        system("runuser -u iasonas -- brave &");
    }
    if(kc == KC_PLUS) {
        system("runuser -u iasonas -- mousepad &");
    }
}
