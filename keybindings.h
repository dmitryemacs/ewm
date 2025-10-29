#ifndef KEYBINDINGS_H
#define KEYBINDINGS_H

#include <X11/Xlib.h>

typedef struct {
    KeyCode keycode;
    unsigned int modmask;
    void (*handler)();
} KeyBinding;

void init_keybindings(Display *display, Window root);

void handle_keypress(XEvent *event);

#endif
