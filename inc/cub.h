/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:12:38 by mzhukova          #+#    #+#             */
/*   Updated: 2024/09/26 15:16:00 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#define N 78
#define S 83
#define E 69
#define W 87

typedef struct s_data
{
	char **map;
	char **map_copy;
	char *north;
	char *south;
	char *west;
	char *east;
	char *pic_ceiling;
	char *pic_floor;
	t_rgb *ceiling;
	t_rgb *floor;
	
}	t_data;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		img_width;
	int		img_height;
} t_img;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_player
{
	t_pos *position;
	int orientation;
}	t_player;


typedef struct s_pos
{
	double x;
	double y;
} t_pos;


// void create_Frame(int *Coords, ...);  //Cords=[x][y][z][x'][y'][z']
// void p_movement(char *Coords, void *key_pressed);
// void m_movement(char *Coords, void *mouse_moved);

//check_args(int argc, char **argv);
//map_validation(char *argv, t_data *map_data);
	//name_check(format)
	//open check
	//copy_map to 2d_array
	//check_walls
	//check_lines
	
//check_walls();
//check_map_lines();
	//check for empty lines between map rows
	//check for characters that are no N,S,E or W

