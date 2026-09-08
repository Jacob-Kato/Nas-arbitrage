#include <stdio.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

int main(void)
{
    Display *display = XOpenDisplay(NULL);

    if (display == NULL) {
        fprintf(stderr, "Could not open X display\n");
        return 1;
    }

    printf("Starting in 3 seconds...\n");
    sleep(3);

    // Move mouse to (500, 500)
    XTestFakeMotionEvent(
        display,
        -1,
        900,
        900,
        CurrentTime
    );

    XFlush(display);

    sleep(1);

    // Get the X11 keycode for 'a'
    KeyCode keycode = XKeysymToKeycode(display, XK_a);

    // Press 'a'
    XTestFakeKeyEvent(
        display,
        keycode,
        True,
        CurrentTime
    );

    XFlush(display);

    sleep(1);

    // Release 'a'
    XTestFakeKeyEvent(
        display,
        keycode,
        False,
        CurrentTime
    );

    XFlush(display);

    XCloseDisplay(display);

    return 0;
}
