#include "event_handler.h"
#include "input_event.h"
#include <stdlib.h>

static EventHandlerNode *handlers = NULL;

void register_event_handler(EventHandler handler) {
    EventHandlerNode *new_node = (EventHandlerNode *)malloc(sizeof(EventHandlerNode));
    new_node->handler = handler;
    new_node->next = handlers;
    handlers = new_node;
}

void unregister_event_handler(EventHandler handler) {
    EventHandlerNode **current = &handlers;
    while (*current) {
        if ((*current)->handler == handler) {
            EventHandlerNode *to_remove = *current;
            *current = (*current)->next;
            free(to_remove);
            return;
        }
        current = &(*current)->next;
    }
}

void execute_event_handlers(InputEvent event) {
    EventHandlerNode *current = handlers;
    while (current) {
        current->handler(event);
        current = current->next;
    }
}
