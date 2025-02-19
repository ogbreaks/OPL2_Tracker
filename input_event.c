#include "input_event.h"
#include <stdio.h>

void handle_event(InputEvent event) {
    switch (event.type) {
        case EVENT_KEY_PRESS:
            printf("Key pressed: %d\n", event.key);
            break;
        case EVENT_MOUSE_CLICK:
            printf("Mouse clicked at (%d, %d)\n", event.x, event.y);
            break;
        default:
            printf("Unknown event type.\n");
            break;
    }
}
