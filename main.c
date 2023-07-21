// this means its install system-wide so maybe you have to search for library system-wide while compiling ? 
#include "so_long.h"
#include <stdio.h>

#define RED 0X00FF0000
#define BLUE 0X000000FF
#define GREEN 0X0000FF00
#define BLACK 0X00000000

//use 'xev' command to check keycodes

typedef struct s_data 
{
	void *img;
	char *addr;
	int bits_per_pixels;
	int line_length;
	int endian;
}	t_data;

typedef struct {
	t_mlx *mlx;
	t_data *img;
	int playerPosX;
	int playerPosY;
} parameters;

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

void ft_create_square(t_data *img, int playerPosX, int playerPosY, int size, int color)
{
	int x;
	int y;

	x = 0;
	while (x <= size)
	{
		y = 0;
		while (y <= size)
		{
			ft_mlx_pixel_put(img, playerPosX + x, playerPosY + y, color);
			y++;
		}
		x++;
	}
}

void ft_putkeycode(int keycode)
{
	ft_putstr("keycode: ");
	ft_putnbr(keycode);
	ft_putchar('\n');
}

int ft_put_mouse_pos(int x, int y)
{
	ft_putstr("x: ");
	ft_putnbr(x);
	ft_putchar('\n');
	ft_putstr("y: ");
	ft_putnbr(y);
	ft_putchar('\n');
}

int ft_keyboard_hook(int keycode, parameters *par)
{
	int old_x;
	int old_y;

	old_x = par->playerPosX;
	old_y = par->playerPosY;
	ft_putkeycode(keycode);
	if (keycode == 65307)
	{
		mlx_destroy_window(par->mlx->mlx, par->mlx->win);
		exit(0);
	}
	else if (keycode == 32)
	{
		ft_putstr("'Screen Cleared!'\n");
	}
	else if (keycode == 65361)
	{
		//left
		par->playerPosX -= 10;
	}
	else if (keycode == 65362)
	{
		//up
		par->playerPosY -= 10;
	}
	else if (keycode == 65363)
	{
		//right
		par->playerPosX += 10;
		
	}
	else if (keycode == 65364)
	{
		//down
		par->playerPosY += 10;
	}
	//clear window doesn't work ??? --> so i just draw a black square over the old square
	// mlx_clear_window(par->mlx->mlx, par->mlx->win);
	ft_create_square(par->img, par->playerPosX, par->playerPosY, 10, GREEN);
	ft_create_square(par->img, old_x, old_y, 10, BLACK);
	mlx_put_image_to_window(par->mlx->mlx, par->mlx->win, par->img->img, 0, 0);
}

int ft_exit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

int main(void)
{
	t_mlx mlx;
	t_data img;
	parameters par;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1280, 720, "Hello world!");
	img.img = mlx_new_image(mlx.mlx, 1280, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixels, &img.line_length, &img.endian);
	par.mlx = &mlx;
	par.img = &img;
	par.playerPosX = 500;
	par.playerPosY = 500;
	ft_create_square(&img, par.playerPosX, par.playerPosY, 10, GREEN);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	//hooks for the same events have to be in the same call of mlx_hook
	mlx_loop_hook(mlx.mlx, NULL, NULL);
	mlx_hook(mlx.win, 17, 0, ft_exit, &mlx);
	mlx_key_hook(mlx.win, ft_keyboard_hook, &par);
	mlx_hook(mlx.win, 6, 1L<<6, ft_put_mouse_pos, NULL);

	// 	ft_create_square(&img, 5, 5, a, GREEN);
	// 	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_loop(mlx.mlx);
}