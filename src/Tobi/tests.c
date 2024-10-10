#include "../../inc/cub.h"

//make test

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int terminate(int keycode, t_vars *vars)
{
    if(keycode == 65307)
        mlx_destroy_window(vars->mlx, vars->win);
    exit (keycode);
}

typedef struct	s_datax {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_datax;

int	closex(int keycode, t_vars *vars)
{
    //printf("Keycode : %d\n", keycode);
    if(keycode == 65307)
            terminate(keycode, vars);
    return(0);
	
}

void	my_mlx_pixel_put(t_datax *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}




int main (void)
{
    t_vars vars;
    t_datax	img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
    img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    for (int j = 0; j < 1080; j++)
        {
            for (int i = 0; i < 1920; i++)
	            {
                    my_mlx_pixel_put(&img, i, j,(j/5)*0x00000100+((i)/8)*0x00010001); // ((j)/((int)1080/(int)254)*0x00000001) + ((i)/((int)1920/(int)255)*0x00000001)
                    if(i==0 && j>= 1070)
                        printf("%X\n",((j)/5)*0x00000001);
                }
        }
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
    mlx_hook(vars.win, 2, 1L<<0, closex, &vars);
    mlx_hook(vars.win, 17, 0, terminate, &vars);
	mlx_loop(vars.mlx);
}