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
    static int	pfand_collected;
	char	str[50];

    if (env->data->pfand_collected == pfand_collected)
        return 0;
    pfand_collected = env->data->pfand_collected;
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
	static int	player_pos;
	char		str[50];

	if (env->player->player_pos == player_pos)
		return 0;
	player_pos = env->player->player_pos;
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
	static char	looking_at;
	char		str[50];

	if (env->data->looking_at == looking_at)
		return 0;
	looking_at = env->data->looking_at;
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

void	draw_ui(t_env *env, t_img *canvas, int mode)
{
    int ret;

	if (UI_TEXT == 0 || env->player->display_bon == 1)
		return ;
	mlx_set_font(env->mlx, env->mlx_win,
		"-mutt-clearlyu-medium-r-normal--17-120-100-100-p-123-iso10646-1");
	if (mode == 0)
		put_ui_bg(canvas);
	else
	{
        ret = 0;
		ret += put_text_line_one(env);
		ret += put_text_line_two(env);
		ret += put_text_line_three(env);
        if(ret == 0)
            put_image_to_image(env->screen_shot, canvas, 0, HEIGHT-UI_HEIGHT);
        else
            get_screenshot_image(env);
	}
}
