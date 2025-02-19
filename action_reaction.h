#ifndef ACTION_REACTION_H
#define ACTION_REACTION_H

#include "input_event.h"

typedef void (*Action)();

typedef struct {
    int key;
    Action action;
} KeyAction;

void register_key_action(int key, Action action);
void unregister_key_action(int key);
void custom_key_handler(InputEvent event);
void custom_mouse_handler(InputEvent event); // Added for mouse events
void init_key_actions();

#endif // ACTION_REACTION_H