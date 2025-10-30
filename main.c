#include <X11/Xlib.h>
#include "include/keybindings.h"
#include "include/workspaces.h"
#include "include/utils.h"

int main() {
    Display *display = XOpenDisplay(NULL);
    if (!display) return 1;

    Window root = DefaultRootWindow(display);

    init_keybindings(display, root);

    XEvent event;
    while (1) {
        XNextEvent(display, &event);
        if (event.type == KeyPress) {
            handle_keypress(&event, display);
        } else if (event.type == MapNotify) {
            move_window_to_workspace(event.xmap.window, current_workspace);
        }
    }

    XCloseDisplay(display);
    return 0;
}
