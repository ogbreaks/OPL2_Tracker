#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "stuff.h"
#include "input_lib.h"
#include "input_processing.h"
#include "event_handler.h"

const u16 instrptr[] = {
    0, 1
};

const u8 instrdata[] = {
    0, 0,
    'v', 255, 'm', 0x11, '+', 0, 'w', WF_PUL, 'f', 0xef, 't', 8, 'f', 0xfc, 0, 0, // lead
    'v', 255, 'w', WF_NOI, 't', 2, '+', 0, 'w', WF_SAW, 'f', 0xef, 't', 8, 'f', 0, 't', 12, '~', 0x37, 'f', 0xfc, 0, 0, // lead+vibr
    'v', 255, 'w', WF_NOI, 't', 2, 'm', 0x11, '+', 12, 'w', WF_PUL, 'f', 0xfc, 't', 2, '+', 7, 't', 2, '+', 3, 't', 2, '+', 0, 't', 2, 'j', 5, 0, 0, // arp
    'v', 255, 'w', WF_NOI, 't', 2, 'd', 0x80, '+', 0, 'w', WF_PUL, 'l', 0x80, 't', 12, 'v', 0, 0, 0    // bass drum
};

const struct track trackdata = {
    {
        {12*3+0,    1,    {'i',    0},    {0xff,    0}},
        {12*2+0,    1,    {0,    0},    {0,    0}},
        {12*3+0,    1,    {0,    0},    {0,    0}},
        {12*3+3,    1,    {0,    0},    {0,    0}},
        {12*2+0,    1,    {0,    0},    {0,    0}},
        {12*3+3,    1,    {0,    0},    {0,    0}},
        {12*3+2,    1,    {0,    0},    {0,    0}},
        {12*2+0,    1,    {0,    0},    {0,    0}},
        {12*3+7,    1,    {0,    0},    {0,    0}},
        {12*2+0,    1,    {0,    0},    {0,    0}},
        {12*3+3,    1,    {0,    0},    {0,    0}},
        {12*2+0,    1,    {0,    0},    {0,    0}},
        {12*3+2,    1,    {0,    0},    {0,    0}},
        {12*2+0,    1,    {0,    0},    {0,    0}},
        {12*2+10,    1,    {0,    0},    {0,    0}},
        {12*2+0,    1,    {0,    0},    {0,    0}},
        {12*3+0,    1,    {0,    0},    {0,    0}},
        {12*2+0,    1,    {0,    0},    {0,    0}},
        {12*3+0,    1,    {0,    0},    {0,    0}},
        {12*3+3,    1,    {0,    0},    {0,    0}},
        {12*2+0,    1,    {0,    0},    {0,    0}},
        {12*3+3,    1,    {0,    0},    {0,    0}},
        {12*3+7,    1,    {0,    0},    {0,    0}},
        {12*3+8,    1,    {0,    0},    {0,    0}},
        {12*3+5,    1,    {0,    0},    {0,    0}},
        {12*3+7,    1,    {0,    0},    {0,    0}},
        {12*3+3,    1,    {0,    0},    {0,    0}},
        {12*3+2,    1,    {0,    0},    {0,    0}},
        {12*2+0,    1,    {0,    0},    {0,    0}},
        {12*2+10,    1,    {0,    0},    {0,    0}},
        {12*2+7,    1,    {0,    0},    {0,    0}},
        {12*3+2,    1,    {0,    0},    {0,    0}},
    }
};

void audiocb(void *userdata, Uint8 *buf, int len) {
    int i;

    for(i = 0; i < len; i++) {
        buf[i] = interrupthandler();
    }
}

// Custom event handlers

void custom_key_handler(InputEvent event) {
    if (event.type == EVENT_KEY_PRESS) {
        printf("Custom handler: Key pressed: %d\n", event.key);
    }
}

void custom_mouse_handler(InputEvent event) {
    if (event.type == EVENT_MOUSE_CLICK) {
        printf("Custom handler: Mouse clicked at (%d, %d)\n", event.x, event.y);
    }
}

int main(int argc, char **argv) {

    // Initialize input library
    init_input();

    // Register custom event handlers
    register_event_handler(custom_key_handler);
    register_event_handler(custom_mouse_handler);

    // Simulate some input events
    process_key_press(65); // A key
    process_mouse_click(100, 200);



    SDL_AudioSpec requested, obtained;

    if(argc != 2) {
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);

    requested.freq = 16000;
    requested.format = AUDIO_U8;
    requested.samples = 256;
    requested.callback = audiocb;
    requested.channels = 1;
    if(SDL_OpenAudio(&requested, &obtained) == -1) {
        fprintf(stderr, "SDL_OpenAudio Error: %s\n", SDL_GetError());
        exit(1);
    }

    fprintf(stderr, "freq %d\n", obtained.freq);
    fprintf(stderr, "samples %d\n", obtained.samples);

    initchip();
    initgui();

    loadfile(argv[1]);

    SDL_PauseAudio(0);

    guiloop();

    // Unregister custom event handlers if no longer needed
    unregister_event_handler(custom_key_handler);
    unregister_event_handler(custom_mouse_handler);

    cleanup_input();

    return 0;
}
