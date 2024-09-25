/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:12:38 by mzhukova          #+#    #+#             */
/*   Updated: 2024/09/25 16:16:47 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

void create_Frame(int *Coords, ...);  //Cords=[x][y][z][x'][y'][z']
void p_movement(char *Coords, void *key_pressed);
void m_movement(char *Coords, void *mouse_moved);

