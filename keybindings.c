#include "keybindings.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <unistd.h>

// save keybindings
static KeyBinding bindings[2];
static Display *global_display;

// start terminal
void spawn_terminal() {
    if (fork() == 0) {
        execlp("alacritty", "alacritty", NULL);
        exit(1);
    }
}

// exit
void exit_wm() {
    exit(0);
}

// init keybindings
void init_keybindings(Display *display, Window root) {
    global_display = display;

    bindings[0].keycode = XKeysymToKeycode(display, XK_Return);
    bindings[0].modmask = Mod4Mask;
    bindings[0].handler = spawn_terminal;

    bindings[1].keycode = XKeysymToKeycode(display, XK_q);
    bindings[1].modmask = Mod4Mask;
    bindings[1].handler = exit_wm;

    for (int i = 0; i < 2; i++) {
        XGrabKey(
            display,
            bindings[i].keycode,
            bindings[i].modmask,
            root,
            True,
            GrabModeAsync,
            GrabModeAsync
        );
    }
}

// keypress
void handle_keypress(XEvent *event) {
    for (int i = 0; i < 2; i++) {
        if (
            event->xkey.keycode == bindings[i].keycode &&
            (event->xkey.state & bindings[i].modmask)
        ) {
            bindings[i].handler();
        }
    }
}
