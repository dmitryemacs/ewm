#ifndef KEYBINDINGS_H
#define KEYBINDINGS_H

#include <X11/Xlib.h>

#define WORKSPACE_COUNT 10
#define BINDING_COUNT 4

extern int current_workspace;

typedef struct {
    KeyCode keycode;
    unsigned int modmask;
    void (*handler)(void);
} KeyBinding;

void init_keybindings(Display *display, Window root);
void handle_keypress(XEvent *event);

void switch_to_workspace(int workspace_index);
void move_window_to_workspace(Window window, int workspace_index);

void switch_to_workspace_1(void);
void switch_to_workspace_2(void);
void exit_wm(void);

#endif
