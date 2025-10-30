#include <libguile.h>
#include <X11/Xlib.h>
#include "include/keybindings.h"
#include "include/workspaces.h"
#include "include/utils.h"

static Display *global_display;

SCM switch_to_workspace_wrapper(SCM workspace_index) {
    int index = scm_to_int(workspace_index);
    switch_to_workspace(global_display, index);
    return SCM_UNSPECIFIED;
}

SCM move_window_to_workspace_wrapper(SCM window, SCM workspace_index) {
    int index = scm_to_int(workspace_index);
    unsigned long win = scm_to_ulong(window);
    move_window_to_workspace(global_display, (Window)win, index);
    return SCM_UNSPECIFIED;
}

void init_guile() {
    scm_init_guile();
    scm_c_define_gsubr("switch-to-workspace", 1, 0, 0, (SCM (*)()) switch_to_workspace_wrapper);
    scm_c_define_gsubr("move-window-to-workspace", 2, 0, 0, (SCM (*)()) move_window_to_workspace_wrapper);
    scm_c_primitive_load(".ewm.scm");
}

int main() {
    global_display = XOpenDisplay(NULL);
    if (!global_display) return 1;

    Window root = DefaultRootWindow(global_display);

    XSelectInput(global_display, root, SubstructureNotifyMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask);

    init_guile(); 

    init_keybindings(global_display, root);

    XEvent event;
    while (1) {
        XNextEvent(global_display, &event);
        if (event.type == KeyPress) {
            handle_keypress(&event, global_display);
        } else if (event.type == MapNotify) {
            move_window_to_workspace(global_display, event.xmap.window, current_workspace);
            XMapWindow(global_display, event.xmap.window);
        }
    }

    XCloseDisplay(global_display);
    return 0;
}
