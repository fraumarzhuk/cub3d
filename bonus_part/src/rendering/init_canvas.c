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
	//add_allocnode();
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
	int	offset_x;
	int	offset_y;

	clear_image(env->canvas, WIDTH, HEIGHT);
	offset_x = WIDTH - MINI_M_SIZE;
	offset_y = HEIGHT - MINI_M_SIZE;

	display_player_pos(env);
	if (env->player->display_rules)
		put_image_to_image(env->rules, env->scene_canvas, 250, 0);	
	draw_ui(env, env->scene_canvas, 0);
	mlx_put_image_to_window(env->mlx, env->mlx_win,
		env->scene_canvas->img, 0, 0);
	mlx_put_image_to_window(env->mlx, env->mlx_win,
		env->mini_map->img, offset_x, offset_y);
	if (env->player->display_bon)
		display_pfandbon(env);
	env->player->render_move = false;
}

void	display_player_pos(t_env *env)
{
	if (env->player->player_pos == HIDEPLAYER)
		return ;
	if (env->player->player_pos == HANDS)
		put_image_to_image(env->enjoyer, env->scene_canvas,
			WIDTH / 2 - 250, HEIGHT - 500);
	else if (env->player->player_pos == BEER)
		put_image_to_image(env->enj_beer, env->scene_canvas,
			WIDTH / 2 - 250, HEIGHT - 500);
	else if (env->player->player_pos == BREZEL)
		put_image_to_image(env->enj_brezel, env->scene_canvas,
			WIDTH / 2 - 250, HEIGHT - 500);
}

void	put_image_to_image(t_img *src, t_img *dst, int offset_x, int offset_y)
{
	int		x;
	int		y;
	char	*src_pixel;
	char	*dst_pixel;

	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			src_pixel = src->addr + (y * src->size_line + x * (src->bpp / 8));
			if (is_correct_pixel(dst, src_pixel, x + offset_x, y + offset_y))
			{
				dst_pixel = dst->addr + ((y + offset_y) * dst->size_line
						+ (x + offset_x) * (dst->bpp / 8));
				*(unsigned int *)dst_pixel = *(unsigned int *)src_pixel;
			}
			x++;
		}
		y++;
	}
}

int	is_correct_pixel(t_img *dst, char *src_pixel, int offs_x, int offs_y)
{
	return (offs_x >= 0 && offs_x < dst->width && offs_y >= 0
		&& offs_y < dst->height
		&& (*(unsigned int *)src_pixel != 0xFF000000));
}
