/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 01:56:43 by tlaukat           #+#    #+#             */
/*   Updated: 2024/12/09 01:56:43 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int	put_text_line_one(t_env *env)
{
	char	str[50];

	if (env->data->pfand_amount > 0)
		snprintf(str, sizeof(str), "Pfand left: %d/%d",
			env->data->pfand_collected, env->data->pfand_amount);
	else
		snprintf(str, sizeof(str), "Pfand left: None");
	mlx_string_put(env->mlx, env->mlx_win, WIDTH / 40, HEIGHT - UI_HEIGHT
		+ UI_HEIGHT * 0.3, UI_TEXT_C, str);
	snprintf(str, sizeof(str), "Money: %.2f EURO", env->player->pfand_sum);
	mlx_string_put(env->mlx, env->mlx_win, WIDTH / 40, HEIGHT - UI_HEIGHT
		+ UI_HEIGHT * 0.5, UI_TEXT_C, str);
    return 1;
}

int	put_text_line_two(t_env *env)
{
	char		str[50];

	if (env->player->player_pos == BEER && BEER_SPRINT == 1)
		snprintf(str, sizeof(str), "Holding: Beer (Makes you faster)");
	if (env->player->player_pos == BEER && BEER_SPRINT == 0)
		snprintf(str, sizeof(str), "Holding: Beer");
	if (env->player->player_pos == BREZEL)
		snprintf(str, sizeof(str), "Holding: Brezel");
	if (env->player->player_pos == HANDS
		|| env->player->player_pos == HIDEPLAYER)
		snprintf(str, sizeof(str), "Holding: Nothing");
	mlx_string_put(env->mlx, env->mlx_win, WIDTH / 40, HEIGHT - UI_HEIGHT
		+ UI_HEIGHT * 0.7, UI_TEXT_C, str);
    return 1;
}

int	put_text_line_three(t_env *env)
{
	char		str[50];

	if (env->data->looking_at == 'B' && SHOP_BEER == 1)
		snprintf(str, sizeof(str), "Press 'E' to buy a beer");
	else if (env->data->looking_at == 'M' && SHOP_BREZEL == 1)
		snprintf(str, sizeof(str), "Press 'E' to buy a brezel");
	else if (env->data->looking_at == 'A')
		snprintf(str, sizeof(str), "Press 'X' to get 'Pfand Money'");
	else
		snprintf(str, sizeof(str), "Press 'space' to view Controls");
	mlx_string_put(env->mlx, env->mlx_win, WIDTH / 40, HEIGHT - UI_HEIGHT
		+ UI_HEIGHT * 0.9, UI_TEXT_C, str);
    return 1;
}

void	put_ui_bg(t_img *canvas)
{
	int	x;
	int	y;

	x = 0;
	y = HEIGHT - UI_HEIGHT;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (y - (HEIGHT - UI_HEIGHT) < UI_HEIGHT / 20)
				my_mlx_pixel_put(canvas, x, y, UI_BORDER_C);
			else
				my_mlx_pixel_put(canvas, x, y, UI_BACKGROUND_C);
			x++;
		}
		x = 0;
		y++;
	}
}

int	draw_ui(t_env *env)
{

	if (UI_TEXT == 0 || env->player->display_bon == 1)
		return (0);
	put_ui_bg(env->scene_canvas);
	mlx_set_font(env->mlx, env->mlx_win,
		"-misc-fixed-bold-r-normal--40-0-100-100-c-0-iso10646-1");
	put_text_line_one(env);
	put_text_line_two(env);
	put_text_line_three(env);
	return(0);
}
