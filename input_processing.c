#include "input_processing.h"
#include "event_handler.h"

void process_key_press(int key) {
    InputEvent event;
    event.type = EVENT_KEY_PRESS;
    event.key = key;
    handle_event(event);
    execute_event_handlers(event);
}

void process_mouse_click(int x, int y) {
    InputEvent event;
    event.type = EVENT_MOUSE_CLICK;
    event.x = x;
    event.y = y;
    handle_event(event);
    execute_event_handlers(event);
}
