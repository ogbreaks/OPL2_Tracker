#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "input_event.h" // Include the header file where InputEvent is defined

typedef void (*EventHandler)(InputEvent event);

typedef struct EventHandlerNode {
    EventHandler handler;
    struct EventHandlerNode *next;
} EventHandlerNode;

void register_event_handler(EventHandler handler);
void unregister_event_handler(EventHandler handler);
void execute_event_handlers(InputEvent event);

#endif // EVENT_HANDLER_H
