// this means its install system-wide so maybe you have to search for library system-wide while compiling ? 
#include "so_long.h"
#include <stdio.h>

#define RED 0X00FF0000
#define BLUE 0X000000FF
#define GREEN 0x0000FF00

typedef struct s_data 
{
	void *img;
	char *addr;
	int bits_per_pixels;
	int line_length;
	int endian;
}	t_data;

void ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixels / 8));
	*(unsigned int*)dst = color;
}

void ft_create_empty_square(t_data *img, int x, int y, int color)
{
	ft_mlx_pixel_put(img, x, y, color);
	ft_mlx_pixel_put(img, x, y + 1, color);
	ft_mlx_pixel_put(img, x, y + 2, color);
	ft_mlx_pixel_put(img, x, y + 3, color);
	ft_mlx_pixel_put(img, x + 1, y + 3, color);
	ft_mlx_pixel_put(img, x + 2, y + 3, color);
	ft_mlx_pixel_put(img, x + 3, y + 3, color);
	ft_mlx_pixel_put(img, x + 3, y + 2, color);
	ft_mlx_pixel_put(img, x + 3, y + 1, color);
	ft_mlx_pixel_put(img, x + 3, y, color);
	ft_mlx_pixel_put(img, x + 2, y, color);
	ft_mlx_pixel_put(img, x + 1, y, color);
}

void ft_create_square(t_data *img, int pos_x, int pos_y, int size, int color)
{
	int x;
	int y;

	x = 0;
	while (x <= size)
	{
		y = 0;
		while (y <= size)
		{
			ft_mlx_pixel_put(img, pos_x + x, pos_y + y, color);
			y++;
		}
		x++;
	}
}

int main(void)
{
	void *mlx;
	int i;
	void *mlx_win;
	t_data img;

	i = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1280, 720, "Hello world!");
	img.img = mlx_new_image(mlx, 1280, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixels, &img.line_length, &img.endian);
	
	// while (i < 100)
	// {
	// 	ft_create_square(&img, 5, 5, i, RED);
	// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// 	usleep(500000);
	// 	i++;
	// }
	// i = 0;
	while (i < 100)
	{
		printf("%d\n", i);
		printf("RED\n");
		ft_create_square(&img, 5, 5, 100, RED);
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		usleep(500000);
		printf("BLUE\n");
		ft_create_square(&img, 5, 5, 100, GREEN);
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		usleep(500000);
		printf("GREEN\n");
		ft_create_square(&img, 5, 5, 100, BLUE);
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		usleep(500000);
		i++;
	}
	mlx_loop(mlx);
}