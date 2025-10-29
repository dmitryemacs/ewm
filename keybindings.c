#include "keybindings.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// workspace
int current_workspace = 0;
static Window workspace_windows[WORKSPACE_COUNT][100];
static int window_count[WORKSPACE_COUNT] = {0};
static KeyBinding bindings[7];
static Display *global_display;

// switch to workspace
void switch_to_workspace(int workspace_index) {
    if (workspace_index >= 0 && workspace_index < WORKSPACE_COUNT && workspace_index != current_workspace) {
        for (int i = 0; i < window_count[current_workspace]; i++) {
            XUnmapWindow(global_display, workspace_windows[current_workspace][i]);
        }

        for (int i = 0; i < window_count[workspace_index]; i++) {
            XMapWindow(global_display, workspace_windows[workspace_index][i]);
        }

        current_workspace = workspace_index;
        printf("Switched to workspace %d\n", workspace_index);
    }
}

// move window
void move_window_to_workspace(Window window, int workspace_index) {
    if (workspace_index >= 0 && workspace_index < WORKSPACE_COUNT) {
        // Удаляем окно с текущего рабочего стола
        for (int i = 0; i < window_count[current_workspace]; i++) {
            if (workspace_windows[current_workspace][i] == window) {
                for (int j = i; j < window_count[current_workspace] - 1; j++) {
                    workspace_windows[current_workspace][j] = workspace_windows[current_workspace][j + 1];
                }
                window_count[current_workspace]--;
                break;
            }
        }

        // Добавляем окно на новый рабочий стол
        workspace_windows[workspace_index][window_count[workspace_index]] = window;
        window_count[workspace_index]++;

        // Скрываем окно, если перемещаем на неактивный рабочий стол
        if (workspace_index != current_workspace) {
            XUnmapWindow(global_display, window);
        }

        printf("Moved window to workspace %d\n", workspace_index);
    }
}

// start terminal
void spawn_terminal() {
    if (fork() == 0) {
        execlp("alacritty", "alacritty", NULL);
        exit(1);
    }
}

// menu
void menu() {
    if (fork() == 0) {
        execlp("dmenu_run", "dmenu_run", NULL);
        exit(1);
    }
}

// exit
void exit_wm() {
    exit(0);
}

void switch_to_workspace_1() { switch_to_workspace(0); }
void switch_to_workspace_2() { switch_to_workspace(1); }

void move_window_left() {
    if (current_workspace > 0) {
        switch_to_workspace(current_workspace - 1);
    }
}

void move_window_right() {
    if (current_workspace < WORKSPACE_COUNT - 1) {
        switch_to_workspace(current_workspace + 1);
    }
}


// init keybindings
void init_keybindings(Display *display, Window root) {
    global_display = display;

    bindings[0].keycode = XKeysymToKeycode(display, XK_Return);
    bindings[0].modmask = Mod4Mask;
    bindings[0].handler = (void (*)(void))spawn_terminal;

    bindings[1].keycode = XKeysymToKeycode(display, XK_d);
    bindings[1].modmask = Mod4Mask;
    bindings[1].handler = (void (*)(void))menu;

    bindings[2].keycode = XKeysymToKeycode(display, XK_q);
    bindings[2].modmask = Mod4Mask;
    bindings[2].handler = (void (*)(void))exit_wm;

    bindings[3].keycode = XKeysymToKeycode(display, XK_1);
    bindings[3].modmask = Mod4Mask;
    bindings[3].handler = (void (*)(void))switch_to_workspace_1;

    bindings[4].keycode = XKeysymToKeycode(display, XK_2);
    bindings[4].modmask = Mod4Mask;
    bindings[4].handler = (void (*)(void))switch_to_workspace_2;

    bindings[5].keycode = XKeysymToKeycode(display, XK_Left);
    bindings[5].modmask = Mod4Mask;
    bindings[5].handler = (void (*)(void))move_window_left;

    bindings[6].keycode = XKeysymToKeycode(display, XK_Right);
    bindings[6].modmask = Mod4Mask;
    bindings[6].handler = (void (*)(void))move_window_right;

    for (int i = 0; i < 7; i++) {
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
    for (int i = 0; i < 7; i++) {
        if (
            event->xkey.keycode == bindings[i].keycode &&
            (event->xkey.state & bindings[i].modmask)
        ) {
            bindings[i].handler();
        }
    }
}
