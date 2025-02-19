#include "action_reaction.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 256

static KeyAction key_actions[MAX_KEYS];

void register_key_action(int key, Action action) {
    if (key >= 0 && key < MAX_KEYS) {
        key_actions[key].key = key;
        key_actions[key].action = action;
    }
}

void unregister_key_action(int key) {
    if (key >= 0 && key < MAX_KEYS) {
        key_actions[key].key = 0;
        key_actions[key].action = NULL;
    }
}

void custom_key_handler(InputEvent event) {
    if (event.key >= 0 && event.key < MAX_KEYS && key_actions[event.key].action != NULL) {
        key_actions[event.key].action();
    } else {
        printf("Unknown key pressed: %d\n", event.key);
    }
}

void custom_mouse_handler(InputEvent event) {
    if (event.type == EVENT_MOUSE_CLICK) {
        printf("Custom handler: Mouse clicked at (%d, %d)\n", event.x, event.y);
    }
}

// Example actions
void action_play() {
    printf("Play action triggered\n");
}

void action_stop() {
    printf("Stop action triggered\n");
}

// Initialize key actions
void init_key_actions() {
    register_key_action(10, action_play); // Enter key
    register_key_action(' ', action_stop); // Space key
}