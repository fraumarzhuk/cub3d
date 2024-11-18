#include "../../inc/cub.h"
#include "../Math-functions/xMath.h"

/*
#define Ceiling 0x0087CEEB
#define Floor 0x00666666
#define NO 0x00FF0000
#define SO 0x0000FF00
#define WE 0x000000FF
#define EA 0x00FFFF00*/

int get_image_pixel(t_img *img, double x, double y)
{
	int nx;
	int ny;

	nx = (1-x) * img->width;
	ny = y * img->height;

	return(*(int*)(img->addr + 4 * nx + ( 4* ny * img->width)));
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void put_bg(t_img *frame, int i, t_env *env)
{
    int j = 0;
    while (j < HEIGHT)
    {
        if(j < HEIGHT / 2)
            my_mlx_pixel_put(frame, i, j, env->data->floor->r * 0x10000 + env->data->floor->g * 0x100 + env->data->floor->b);//get_image_pixel(env->ceiling,0,0));
        else
            my_mlx_pixel_put(frame, i, j, env->data->ceiling->r * 0x10000 + env->data->ceiling->g * 0x100 + env->data->ceiling->b);//get_image_pixel(env->floor,0,0));
        j++;
    }
}

void key_image_onto_walls(t_img *frame, t_img *image, int i, double w_pos, int wall_height)
{
    int j;
    double image_top;
    double image_height;
    int pixel_color;
    int height;

    height = fmax(0, HEIGHT / 2 - wall_height / 2);
    if(height)
        image_top = 0; 
    else 
        image_top = (wall_height - HEIGHT) / (2.0 * wall_height); 
    image_height = 1 - image_top * 2; 

    j = height;
    while ( j < HEIGHT - height && j < HEIGHT )
    {
        pixel_color = get_image_pixel(image, (double)w_pos - (int)w_pos, ((j - height) / (double)(HEIGHT - 2 * height)) * image_height + image_top);
        my_mlx_pixel_put(frame, i, j, pixel_color);
        j++;
    }
}

void put_wall_slice(t_img *frame, int i, double* pos, double *wall_pos, t_env *env)
{
    put_bg(frame, i, env);
    if(env->data->frame_dist < 0)
        env->data->frame_dist *= -1;

    double wall_height;
    if (!(fabs(env->data->frame_dist) < 1e-6))  
        wall_height = (HEIGHT / env->data->frame_dist) * (FOV_Mod / ((double)yFOV * 2) * M_PI / 2.0);
    else 
        wall_height = HEIGHT;
    if (is_whole_t(wall_pos[0], 1e-6) && wall_pos[0] >= pos[0])
		key_image_onto_walls(frame, env->west_wall, i, ceil(wall_pos[1]) - wall_pos[1], wall_height);
	else if (is_whole_t(wall_pos[0], 1e-6) && wall_pos[0] <= pos[0])
		key_image_onto_walls(frame, env->east_wall, i, wall_pos[1],  wall_height);
	else if (is_whole_t(wall_pos[1], 1e-6) && wall_pos[1] <= pos[2])
		key_image_onto_walls(frame, env->south_wall, i, ceil(wall_pos[0]) - wall_pos[0],  wall_height);
	else if (is_whole_t(wall_pos[1], 1e-6) && wall_pos[1] >= pos[2])
		key_image_onto_walls(frame, env->north_wall, i, wall_pos[0],  wall_height);
    else
        printf("%lf, %lf\n", wall_pos[0], wall_pos[1]);
}

int is_touching_wall(t_data *data, double *pos, double *new_pos)
{
    if(new_pos[0] < 0.9 || new_pos[2] < 0.9 || new_pos[2] >= data->true_lines)
        return (0);
    if(is_whole_t(new_pos[0], 1e-6))
    {
        if(data->map_copy[(int)floor(new_pos[2])][(int)round(new_pos[0])- (pos[0]>new_pos[0])] == '1')
            return (1);
    }
    if(is_whole_t(new_pos[2], 1e-6))
    {
        if(data->map_copy[(int)round(new_pos[2])- (pos[2]>new_pos[2])][(int)floor(new_pos[0])] == '1')
            return (1);
    }
    return (0);
}

int get_Wall_dist(double *pos, double dirx, double *wall_pos, t_env *env)
{
    double new_pos[3] = {pos[0], pos[1], pos[2]};
    double dir[2] = {dirx, 0.0};
    double step;
    double distance;

    step = 1e-6;
    distance = 0;
    while (1)
    {
        to_border(new_pos, dir, new_pos);
        if (is_touching_wall(env->data, pos, new_pos) != 0)
            break;
        get_new_pos3(new_pos, dir, step, new_pos);
        distance = get_distance3(pos, new_pos);
        if (Render_Distance - distance < 0)
            return 0;
    }
    if(is_whole_t(new_pos[0], 1e-6) && is_whole_t(new_pos[2], 1e-6))
        return(get_Wall_dist(pos, dirx+1e-6, wall_pos, env));
    distance = get_distance3(pos, new_pos);
    env->data->frame_dist = distance;
    wall_pos[0] = new_pos[0];
    wall_pos[1] = new_pos[2];
    return(1);
}


void	Make_frame(t_img *frame, double *pos, double dir, t_env *env)
{
	int		i;
    double *wall_pos;
    double dirx;
	
	i = 0;
    wall_pos = ft_malloc(2 * sizeof(double));
    dirx = dir - xFOV/2;
    
	while (i < WIDTH )
	{
        while(dirx < 0)
            dirx += 360;
        while(dirx >= 360)
            dirx -= 360;
        if(get_Wall_dist(pos, dirx, wall_pos, env))
        {
            env->data->frame_dist *= cos(degrees_to_radians(dirx - dir)); 
            put_wall_slice(frame, WIDTH - i, pos, wall_pos, env);
            dirx = atan2(WIDTH/2 - (i - 0.5), (int)((WIDTH / 2) / tan(M_PI / 180 * (xFOV / 2)))) * (180.0 / M_PI) + dir;
        }
		i++;
	}
	ft_free(wall_pos);
}
