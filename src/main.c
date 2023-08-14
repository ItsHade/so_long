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
#define WHITE 0X00FFFFFF

#define TILE 64

//use 'xev' command to check keycodes

typedef struct s_game_data 
{
	void *img;
	char *addr;
	int bits_per_pixels;
	int line_length;
	int endian;
}	t_game_data;

typedef struct {
	//simplifier en mettant direct mlx ptr et mlx win sans utiliser la struct t_mlx
	t_mlx *mlx;
	t_game_data *img;
	t_data data;
	int playerPosX;
	int playerPosY;
	int WIDTH;
	int HEIGHT;
	void *player;
	void *background;
	void *wall;
	void *exit;
	void *collectible;
	int texture_width;
	int texture_height;
	int playerMoves;
} parameters;

void ft_mlx_pixel_put(t_game_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixels / 8));
	*(unsigned int*)dst = color;
}

int ft_exit(parameters *par)
{
	mlx_destroy_image(par->mlx->mlx, par->img->img);
	mlx_destroy_image(par->mlx->mlx, par->background);
	mlx_destroy_image(par->mlx->mlx, par->player);
	mlx_destroy_image(par->mlx->mlx, par->wall);
	mlx_destroy_image(par->mlx->mlx, par->exit);
	mlx_destroy_image(par->mlx->mlx, par->collectible);
	mlx_destroy_window(par->mlx->mlx, par->mlx->win);
	mlx_destroy_display(par->mlx->mlx);
	free(par->mlx->mlx);
	ft_freemap(par->data);
	exit(0);
	return (0);
}

// void ft_create_empty_square(t_game_data *img, int x, int y, int color)
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

void ft_display_text(parameters *par)
{
	char *str;
	mlx_put_image_to_window(par->mlx->mlx, par->mlx->win, par->img->img, 0, par->HEIGHT);
	mlx_string_put(par->mlx->mlx, par->mlx->win, 20, par->HEIGHT + 32, 0X00FFFFFF, "moves: ");
	str = ft_itoa(par->playerMoves);
	mlx_string_put(par->mlx->mlx, par->mlx->win, 60, par->HEIGHT + 32, 0X00FFFFFF, str);
	free(str);
	mlx_string_put(par->mlx->mlx, par->mlx->win, 120, par->HEIGHT + 32, 0X00FFFFFF, "collected: ");
	str = ft_itoa(par->data.collectibleCounter);
	mlx_string_put(par->mlx->mlx, par->mlx->win, 185, par->HEIGHT + 32, 0X00FFFFFF, str);
	free(str);
}

void ft_check_player_tile(parameters *par)
{
	if (par->data.map[par->playerPosY][par->playerPosX] == 'C')
	{
		par->data.collectibleCounter++;
		par->data.map[par->playerPosY][par->playerPosX] = '0';
	}
	else if (par->data.map[par->playerPosY][par->playerPosX] == 'E')
	{
		if (par->data.collectibleCounter == par->data.collectibleCount)
		{
			ft_putstr("\033[1;32mCONGRATULATION YOU WON!\033[1;0m\n");
		}
	}
}

void ft_render_map(parameters *par)
{
	int line;
	int col;

	line = 0;
	while (line < par->data.nbLines)
	{
		col = 0;
		while (col < par->data.lineLength)
		{
			if (par->data.map[line][col] == '1')
				mlx_put_image_to_window(par->mlx->mlx, par->mlx->win, par->wall, col * TILE, line * TILE);
			else if (par->data.map[line][col] == 'E')
				mlx_put_image_to_window(par->mlx->mlx, par->mlx->win, par->exit, col * TILE, line * TILE);
			else if (par->data.map[line][col] == 'C')
				mlx_put_image_to_window(par->mlx->mlx, par->mlx->win, par->collectible, col * TILE, line * TILE);
			else
				mlx_put_image_to_window(par->mlx->mlx, par->mlx->win, par->background, col * TILE, line * TILE);
			col++;
		}
		line++;
	}
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
	return (0);
}

int ft_keyboard_hook(int keycode, parameters *par)
{
	int old_x;
	int old_y;

	old_x = par->playerPosX;
	old_y = par->playerPosY;
	// ft_putkeycode(keycode); //uncomment to write keycode in terminal when key is pressed
	if (keycode == 65307)
	{
		ft_exit(par);
	}
	else if (keycode == 32)
	{
		mlx_clear_window(par->mlx->mlx, par->mlx->win);
		ft_putstr("Screen Cleared!\n");
	}
	else if (keycode == 65361)
	{
		//left
		if (par->playerPosX - 1 >= 0 && par->data.map[par->playerPosY][par->playerPosX - 1] != '1')
		{
			par->playerPosX--;
			par->playerMoves++;
		}
	}
	else if (keycode == 65362)
	{
		//up
		if (par->playerPosY - 1 >= 0 && par->data.map[par->playerPosY - 1][par->playerPosX] != '1')
		{
			par->playerPosY--;
			par->playerMoves++;
		}
	}
	else if (keycode == 65363)
	{
		//right
		if (par->playerPosX + 1 < par->data.lineLength && par->data.map[par->playerPosY][par->playerPosX + 1] != '1')
		{
			par->playerPosX++;
			par->playerMoves++;
		}
		
	}
	else if (keycode == 65364)
	{
		//down
		if (par->playerPosY + 1 < par->data.nbLines && par->data.map[par->playerPosY + 1][par->playerPosX] != '1')
		{
			par->playerPosY++;
			par->playerMoves++;
		}
	}

	// ft_create_square(par->img, par->playerPosX, par->playerPosY, 10, GREEN);
	if (old_x != par->playerPosX || old_y != par->playerPosY)
	{
		ft_render_map(par);
		mlx_put_image_to_window(par->mlx->mlx, par->mlx->win, par->player, par->playerPosX * TILE, par->playerPosY * TILE);\
		ft_putstr("moves: ");
		ft_putnbr(par->playerMoves);
		ft_putchar('\n');
		ft_check_player_tile(par);
		ft_display_text(par);
	}
	// ft_create_square(par->img, old_x, old_y, 32, BLACK);
	// ft_create_footsteps(par->img, old_x, old_y, 32, 0X8CFF0000);
	// ft_render_background(par); // need a way to render stuff on top of other
	return (0);
}

int main(int argc, char **argv)
{
	t_mlx mlx;
	t_game_data img;
	parameters par;
	// int background_height = TILE;
	// int background_width = TILE;

	if (ft_check_args(argc, argv, &par.data) == -1)
		return (0);
	ft_get_map(argv[1], &par.data);
	par.playerMoves = 0;
	par.data.collectibleCounter = 0;
	par.WIDTH = TILE * par.data.lineLength;
	par.HEIGHT = TILE * par.data.nbLines;
	par.texture_height = TILE;
	par.texture_width = TILE;
	mlx.mlx = mlx_init();
	par.mlx = &mlx;
	mlx.win = mlx_new_window(mlx.mlx, par.WIDTH, par.HEIGHT + TILE, "so_long");
	par.background = mlx_xpm_file_to_image(mlx.mlx, "./textures/background.xpm", &par.texture_width, &par.texture_height);
	par.player = mlx_xpm_file_to_image(mlx.mlx, "./textures/player.xpm", &par.texture_width, &par.texture_height);
	par.wall = mlx_xpm_file_to_image(mlx.mlx, "./textures/wall.xpm", &par.texture_width, &par.texture_height);
	par.exit = mlx_xpm_file_to_image(mlx.mlx, "./textures/exit.xpm", &par.texture_width, &par.texture_height);
	par.collectible = mlx_xpm_file_to_image(mlx.mlx, "./textures/collectible.xpm", &par.texture_width, &par.texture_height);
	img.img = mlx_new_image(mlx.mlx, par.WIDTH, TILE);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixels, &img.line_length, &img.endian);
	par.img = &img;
	par.playerPosX = par.data.cellP_y;
	par.playerPosY = par.data.cellP_x;
	// ft_create_square(&img, par.playerPosX, par.playerPosY, 10, GREEN);
	// mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	// mlx_put_image_to_window(mlx.mlx, mlx.win, par.background, 64 , 64);
	// ft_render_background(&par);
	ft_render_map(&par);
	ft_display_text(&par);
	mlx_put_image_to_window(mlx.mlx, mlx.win, par.player, par.playerPosX * TILE, par.playerPosY * TILE);
	mlx_loop_hook(mlx.mlx, NULL, NULL);
	mlx_hook(mlx.win, 17, 0, ft_exit, &par);
	mlx_hook(mlx.win, 2, 1L<<0, ft_keyboard_hook, &par);
	// mlx_hook(mlx.win, 6, 1L<<6, ft_put_mouse_pos, NULL); // write mouse x and y in terminal 
	mlx_loop(mlx.mlx);
	ft_exit(&par);
}