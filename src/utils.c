#include "../include/utils.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void toggle_fullscreen(Display *display) {
    Window focus_window;
    int revert_to;

    XGetInputFocus(display, &focus_window, &revert_to);

    if (focus_window != None && focus_window != PointerRoot) {
        XWindowAttributes attrs;
        Status status = XGetWindowAttributes(display, focus_window, &attrs);

        if (status != 0 && attrs.map_state == IsViewable && focus_window != DefaultRootWindow(display)) {
            int screen = DefaultScreen(display);
            unsigned int width = DisplayWidth(display, screen);
            unsigned int height = DisplayHeight(display, screen);

            Window root_return, parent_return, *children;
            unsigned int nchildren;
            if (XQueryTree(display, focus_window, &root_return, &parent_return, &children, &nchildren) != 0) {
                if (parent_return != DefaultRootWindow(display)) {
                    printf("Window is an internal window, cannot resize\n");
                    XFree(children);
                    return;
                }
                XFree(children);
            }

            XMoveResizeWindow(display, focus_window, 0, 0, width, height);
            XRaiseWindow(display, focus_window);
            XFlush(display);
        }
    }
}

void switch_keyboard_layout() {
    system("setxkbmap -layout us,ru");
}
