/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Xmlx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:12:03 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/07 15:12:03 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx_int.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned int	get_screen_color(t_xvar *xvar, t_win_list *win, int x, int y)
{
	unsigned int	hexcolor;
	XColor			c;
	XImage			*image;

	image = XGetImage(xvar->display, win->window, x, y, 1, 1, AllPlanes,
			XYPixmap);
	c.pixel = XGetPixel(image, 0, 0);
	XFree(image);
	XQueryColor(xvar->display, DefaultColormap(xvar->display,
			DefaultScreen(xvar->display)), &c);
	hexcolor = ((c.red / 256) << 16) | ((c.green / 256) << 8) | (c.blue / 256);
	return (hexcolor);
}

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
