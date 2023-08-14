#include "../include/so_long.h"


//  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixels, &img.line_length, &img.endian);
typedef struct s_game_data 
{
	void *img;
	char *addr;
	int bits_per_pixels;
	int line_length;
	int endian;
}	t_game_data;

// int main(void)
// {
// 	int width = 32;
// 	int height = 32;

// 	void *mlx_ptr;
// 	void *win_ptr;
// 	void *img_ptr;

// 	mlx_ptr = mlx_init();
// 	win_ptr = mlx_new_window(mlx_ptr, 1280, 720, "Image XPM");
// 	img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/player.xpm", &width, &height);
// 	if (img_ptr == NULL)
// 	{
//         ft_putstr("il y a un probleme!\n");
// 		return (1);
// 	}
// 	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
// 	mlx_loop(mlx_ptr);
// 	// free(img_ptr);
// }

void ft_mlx_pixel_put(t_game_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixels / 8));
	*(unsigned int*)dst = color;
}

void ft_create_empty_square(t_game_data *img, int x, int y, int color)
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

void ft_create_footsteps(t_game_data *img, int pos_x, int pos_y, int size, int color)
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



void ft_create_square(t_game_data *img, int playerPosX, int playerPosY, int size, int color)
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

// mlx_hook(mlx.win, 6, 1L<<6, ft_put_mouse_pos, NULL); // write mouse x and y in terminal 
int ft_put_mouse_pos(int x, int y)
{
	ft_putstr("x: ");
	ft_putnbr(x);
	ft_putchar('\n');
	ft_putstr("y: ");
	ft_putnbr(y);
	ft_putchar('\n');
	return (0);
}

int main(void)
{
	int a = 156;
	ft_putnbr(ft_intlen(a));
	ft_putchar('\n');
	ft_putstr(ft_itoa(a));
}