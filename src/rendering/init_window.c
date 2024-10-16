/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:24:53 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/16 10:34:09 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void init_mlx(t_env *env)
{
	env->mlx = mlx_init();
	env->mlx_win = mlx_new_window(env->mlx, 1000, 1000, "Cub 3D");
	mlx_hook(env->mlx_win, 17, 1L << 17, destroy, env);
	mlx_key_hook(env->mlx_win, key_press, env);
	mlx_loop(env->mlx);
}
void init_minimap(t_img *img, t_data *data, t_env *env)
{
	if (data->pic_floor)
		img->img = mlx_xpm_file_to_image(env->mlx, data->pic_floor, &img->width, &img->height);
	//if (data->floor);
}

void init_img(t_img *img)
{
	img->width = mini_m_w;
	img->height = mini_m_h;
	img->addr = NULL;
	img->img = NULL;

}