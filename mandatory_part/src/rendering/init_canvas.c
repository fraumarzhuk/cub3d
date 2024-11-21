/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_canvas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:48:30 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/12 17:57:37 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	init_canvas_img(t_img *canvas, t_env *env)
{
	canvas->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	if (!canvas->img)
		error_and_exit("Failed to create image");
	canvas->addr = mlx_get_data_addr(canvas->img, &canvas->bpp,
			&canvas->size_line, &canvas->endian);
	if (!canvas->addr)
		error_and_exit("Failed to get image data address");
	canvas->width = WIDTH;
	canvas->height = HEIGHT;
}

void	render_images_on_canvas(t_env *env)
{
	if (!env->player->render_move)
		return ;
	clear_image(env->canvas, WIDTH, HEIGHT);
	mlx_put_image_to_window(env->mlx, env->mlx_win,
		env->scene_canvas->img, 0, 0);
	env->player->render_move = false;
}
