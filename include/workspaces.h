#ifndef WORKSPACES_H
#define WORKSPACES_H

#include <X11/Xlib.h>

#define WORKSPACE_COUNT 10

extern int current_workspace;
extern Window workspace_windows[WORKSPACE_COUNT][100];
extern int window_count[WORKSPACE_COUNT];

void switch_to_workspace(Display *display, int workspace_index);
void move_window_to_workspace(Display *display, Window window, int workspace_index);

#endif
