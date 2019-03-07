#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  Display *d;
  Window w;
  XEvent e;
  const char *msg = "Hello, World!";
  int s;

  XColor colors;
  colors.red = 65535; colors.green = 65535; colors.blue = 65535;

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 100, 100, 600, 400, 1, BlackPixel(d, s), BlackPixel(d,s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapWindow(d, w);

  while (1) {
    XNextEvent(d, &e);
    if (e.type == Expose) {
      XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
      XSetForeground(d, DefaultGC(d, s), colors.pixel);
      XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));
    }
    if (e.type == KeyPress)
      break;
  }

  XCloseDisplay(d);
  return 0;
  
}
