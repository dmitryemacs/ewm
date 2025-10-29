#include <X11/Xlib.h>
#include "keybindings.h"

int main() {
    Display *display = XOpenDisplay(NULL);
    if (!display) return 1;

    Window root = DefaultRootWindow(display);

    init_keybindings(display, root);

    XEvent event;
    while (1) {
        XNextEvent(display, &event);
        if (event.type == KeyPress) {
            handle_keypress(&event);
        }
    }

    XCloseDisplay(display);
    return 0;
}
