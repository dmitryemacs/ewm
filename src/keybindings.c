#include "../include/keybindings.h"
#include "../include/workspaces.h"
#include "../include/utils.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static KeyBinding bindings[9];
static Display *global_display;

void spawn_terminal(Display *display) {
    (void)display;
    if (fork() == 0) {
        execlp("alacritty", "alacritty", NULL);
        exit(1);
    }
}

void menu(Display *display) {
    (void)display;
    if (fork() == 0) {
        execlp("dmenu_run", "dmenu_run", NULL);
        exit(1);
    }
}

void exit_wm(Display *display) {
    (void)display;
    exit(0);
}

void switch_to_workspace_1(Display *display) {
    (void)display;
    switch_to_workspace(0);
}

void switch_to_workspace_2(Display *display) {
    (void)display;
    switch_to_workspace(1);
}

void move_window_left(Display *display) {
    (void)display;
    printf("Move window left\n");
}

void move_window_right(Display *display) {
    (void)display;
    printf("Move window right\n");
}

void init_keybindings(Display *display, Window root) {
    global_display = display;

    bindings[0].keycode = XKeysymToKeycode(display, XK_Return);
    bindings[0].modmask = Mod4Mask;
    bindings[0].handler = spawn_terminal;

    bindings[1].keycode = XKeysymToKeycode(display, XK_d);
    bindings[1].modmask = Mod4Mask;
    bindings[1].handler = menu;

    bindings[2].keycode = XKeysymToKeycode(display, XK_q);
    bindings[2].modmask = Mod4Mask;
    bindings[2].handler = exit_wm;

    bindings[3].keycode = XKeysymToKeycode(display, XK_1);
    bindings[3].modmask = Mod4Mask;
    bindings[3].handler = switch_to_workspace_1;

    bindings[4].keycode = XKeysymToKeycode(display, XK_2);
    bindings[4].modmask = Mod4Mask;
    bindings[4].handler = switch_to_workspace_2;

    bindings[5].keycode = XKeysymToKeycode(display, XK_Left);
    bindings[5].modmask = Mod4Mask;
    bindings[5].handler = move_window_left;

    bindings[6].keycode = XKeysymToKeycode(display, XK_Right);
    bindings[6].modmask = Mod4Mask;
    bindings[6].handler = move_window_right;

    bindings[7].keycode = XKeysymToKeycode(display, XK_space);
    bindings[7].modmask = Mod4Mask;
    bindings[7].handler = (void (*)(Display *))switch_keyboard_layout;

    bindings[8].keycode = XKeysymToKeycode(display, XK_f);
    bindings[8].modmask = Mod4Mask;
    bindings[8].handler = toggle_fullscreen;

    for (int i = 0; i < 9; i++) {
        XGrabKey(display, bindings[i].keycode, bindings[i].modmask, root, True, GrabModeAsync, GrabModeAsync);
    }
}

void handle_keypress(XEvent *event, Display *display) {
    for (int i = 0; i < 9; i++) {
        if (event->xkey.keycode == bindings[i].keycode && (event->xkey.state & bindings[i].modmask)) {
            bindings[i].handler(display);
        }
    }
}
