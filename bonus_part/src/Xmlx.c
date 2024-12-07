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
