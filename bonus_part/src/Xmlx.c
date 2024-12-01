#include "../minilibx-linux/mlx_int.h"
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	grab_mouse(t_xvar *xvar, t_win_list *win)
{
	XGrabPointer(xvar->display, win->window, True,
		PointerMotionMask | ButtonPressMask | ButtonReleaseMask, GrabModeAsync,
		GrabModeAsync, win->window, None, CurrentTime);
}

void	ungrab_mouse(t_xvar *xvar)
{
	XUngrabPointer(xvar->display, CurrentTime);
}