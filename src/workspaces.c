#include "../include/workspaces.h"
#include <X11/Xlib.h>
#include <stdio.h>

int current_workspace = 0;
Window workspace_windows[WORKSPACE_COUNT][100] = {0};
int window_count[WORKSPACE_COUNT] = {0};

void switch_to_workspace(Display *display, int workspace_index) {
    if (workspace_index >= 0 && workspace_index < WORKSPACE_COUNT && workspace_index != current_workspace) {
        for (int i = 0; i < window_count[current_workspace]; i++) {
            XUnmapWindow(display, workspace_windows[current_workspace][i]);
        }

        for (int i = 0; i < window_count[workspace_index]; i++) {
            XMapWindow(display, workspace_windows[workspace_index][i]);
        }

        current_workspace = workspace_index;
        printf("Switched to workspace %d\n", workspace_index);
    }
}

void move_window_to_workspace(Display *display, Window window, int workspace_index) {
    if (workspace_index >= 0 && workspace_index < WORKSPACE_COUNT) {
        for (int i = 0; i < window_count[current_workspace]; i++) {
            if (workspace_windows[current_workspace][i] == window) {
                for (int j = i; j < window_count[current_workspace] + 1; j++) {
                    workspace_windows[current_workspace][j] = workspace_windows[current_workspace][j + 1];
                }
                window_count[current_workspace]--;
                break;
            }
        }

        workspace_windows[workspace_index][window_count[workspace_index]] = window;
        window_count[workspace_index]++;

        if (workspace_index != current_workspace) {
            XUnmapWindow(display, window);
        } else {
            XMapWindow(display, window);
        }

        printf("Moved window to workspace %d\n", workspace_index);
    }
}
