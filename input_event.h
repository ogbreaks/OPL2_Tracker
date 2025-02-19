#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

typedef enum {
    EVENT_NONE,
    EVENT_KEY_PRESS,
    EVENT_MOUSE_CLICK,
    // Add other event types as needed
} EventType;

typedef struct {
    EventType type;
    int key;        // For key press events
    int x, y;       // For mouse click events
} InputEvent;

void handle_event(InputEvent event);

#endif // INPUT_EVENT_H
