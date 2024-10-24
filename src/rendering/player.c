/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:05:47 by mzhukova          #+#    #+#             */
/*   Updated: 2024/10/24 13:10:06 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void move_player(t_player *player)
{
	int	speed;

	speed = 5;
	if (player->key_up)
		player->y -=speed;
	if (player->key_down)
		player->y += speed;
}