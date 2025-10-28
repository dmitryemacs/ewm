#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main() {
    Display *display = XOpenDisplay(NULL);
    if (!display) return 1;

    Window root = DefaultRootWindow(display);
    Window window = XCreateSimpleWindow(display, root, 0, 0, 800, 600, 0, 0, 0);

    XMapWindow(display, window);
    XEvent event;
    while (1) {
        XNextEvent(display, &event);
        if (event.type == KeyPress) break;
    }

    XCloseDisplay(display);
    return 0;
}
