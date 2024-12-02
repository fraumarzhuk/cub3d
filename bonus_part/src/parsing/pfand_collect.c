/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfand_collect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:31:01 by mzhukova          #+#    #+#             */
/*   Updated: 2024/12/02 15:50:11 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

//TODO:
//parse the amount of collects - done
//implement a button to collect pfand
// modify the map when pfand is collected
//When all pfand collected, printf the sum to terminal for now
//display pfand on a map 

void find_pfand_amount(t_data *data)
{
	int	x;
	int	y;
	y = 0;
	while (data->map_copy[y])
	{
		x = 0;
		while (data->map_copy[y][x])
		{
			if (data->map_copy[y][x] == 'P')
				data->pfand_available++;
			x++;
		}
		y++;
	}
	printf("Availiable pfand: %d\n", data->pfand_available);
}