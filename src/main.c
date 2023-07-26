// this means its install system-wide so maybe you have to search for library system-wide while compiling ? 
// #include <mlx.h>
#include "../include/so_long.h"

//0XAARRGGBB
//AA = alpha, RR = red, GG = green, BB = blue
//00 = 0 | FF = 255
#define RED 0X00FF0000
#define BLUE 0X000000FF
#define GREEN 0X0000FF00
#define BLACK 0X00000000

#define WIDTH 1000
#define HEIGHT 700

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
	void *player;
	char *player_filename;
	void *footstep;
	char *footstep_filename;
	int texture_width;
	int texture_height;
} parameters;

void ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixels / 8));
	*(unsigned int*)dst = color;
}

// void ft_create_empty_square(t_data *img, int x, int y, int color)
// {
// 	ft_mlx_pixel_put(img, x, y, color);
// 	ft_mlx_pixel_put(img, x, y + 1, color);
// 	ft_mlx_pixel_put(img, x, y + 2, color);
// 	ft_mlx_pixel_put(img, x, y + 3, color);
// 	ft_mlx_pixel_put(img, x + 1, y + 3, color);
// 	ft_mlx_pixel_put(img, x + 2, y + 3, color);
// 	ft_mlx_pixel_put(img, x + 3, y + 3, color);
// 	ft_mlx_pixel_put(img, x + 3, y + 2, color);
// 	ft_mlx_pixel_put(img, x + 3, y + 1, color);
// 	ft_mlx_pixel_put(img, x + 3, y, color);
// 	ft_mlx_pixel_put(img, x + 2, y, color);
// 	ft_mlx_pixel_put(img, x + 1, y, color);
// }

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

void ft_create_footsteps(t_data *img, int pos_x, int pos_y, int size, int color)
{
	int x;
	int y;
	static int footsteps[10][10] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	x = 0;
	while (x <= size)
	{
		y = 0;
		while (y <= size)
		{
			if (footsteps[x][y] == 1)
				ft_mlx_pixel_put(img, pos_x + x, pos_y + y, color);
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
		if (par->playerPosX - 32 > 0)
			par->playerPosX -= 32;
	}
	else if (keycode == 65362)
	{
		//up
		if (par->playerPosY - 32 > 0)
			par->playerPosY -= 32;
	}
	else if (keycode == 65363)
	{
		//right
		if (par->playerPosX + 32 < WIDTH)
			par->playerPosX += 32;
		
	}
	else if (keycode == 65364)
	{
		//down
		if (par->playerPosY + 32 < HEIGHT)
			par->playerPosY += 32;
	}
	//clear window doesn't work ??? --> so i just draw a black square over the old square
	// mlx_clear_window(par->mlx->mlx, par->mlx->win);
	// ft_create_square(par->img, par->playerPosX, par->playerPosY, 10, GREEN);
	// if (old_x != par->playerPosX || old_y != par->playerPosY)
	ft_create_square(par->img, old_x, old_y, 32, BLACK);
	// ft_create_footsteps(par->img, old_x, old_y, 32, 0X8CFF0000);
	mlx_put_image_to_window(par->mlx->mlx, par->mlx->win, par->img->img, 0, 0);
	// mlx_put_image_to_window(par->mlx->mlx, par->mlx->win, par->footstep, old_x, old_y);
	mlx_put_image_to_window(par->mlx->mlx, par->mlx->win, par->player, par->playerPosX, par->playerPosY);

}

void ft_fill_background(parameters *par)
{
	
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


	par.player_filename = "./textures/daseldrawing.xpm";
	// par.footstep_filename = "./textures/footstep.xpm";
	par.texture_height = 64;
	par.texture_width = 64;
	mlx.mlx = mlx_init();
	par.player = mlx_xpm_file_to_image(mlx.mlx, par.player_filename, &par.texture_width, &par.texture_height);
	// par.footstep = mlx_xpm_file_to_image(mlx.mlx, par.footstep_filename, &par.texture_width, &par.texture_height);
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "DASELLLLLL JE T'AIIIMMEEEEEEEEE!");
	img.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixels, &img.line_length, &img.endian);
	par.mlx = &mlx;
	par.img = &img;
	par.playerPosX = 500;
	par.playerPosY = 500;
	// ft_create_square(&img, par.playerPosX, par.playerPosY, 10, GREEN);
	// mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_put_image_to_window(mlx.mlx, mlx.win, par.player, par.playerPosX, par.playerPosY);
	mlx_loop_hook(mlx.mlx, NULL, NULL);
	mlx_hook(mlx.win, 17, 0, ft_exit, &mlx);
	mlx_hook(mlx.win, 2, 1L<<0, ft_keyboard_hook, &par);
	mlx_hook(mlx.win, 6, 1L<<6, ft_put_mouse_pos, NULL);
	mlx_loop(mlx.mlx);
	free(mlx.mlx);
}