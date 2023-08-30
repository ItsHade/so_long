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

int ft_exit(parameters *par)
{
	mlx_destroy_image(par->mlx, par->img);
	mlx_destroy_image(par->mlx, par->background);
	mlx_destroy_image(par->mlx, par->player);
	mlx_destroy_image(par->mlx, par->wall);
	mlx_destroy_image(par->mlx, par->exit);
	mlx_destroy_image(par->mlx, par->collectible);
	mlx_destroy_window(par->mlx, par->win);
	mlx_destroy_display(par->mlx);
	free(par->mlx);
	ft_freemap(par->data);
	exit(0);
	return (0);
}

void ft_display_text(parameters *par)
{
	char *str;
	mlx_put_image_to_window(par->mlx, par->win, par->img, 0, par->HEIGHT);
	mlx_string_put(par->mlx, par->win, 20, par->HEIGHT + 32, 0X00FFFFFF, "moves: ");
	str = ft_itoa(par->playerMoves);
	mlx_string_put(par->mlx, par->win, 60, par->HEIGHT + 32, 0X00FFFFFF, str);
	free(str);
	mlx_string_put(par->mlx, par->win, 120, par->HEIGHT + 32, 0X00FFFFFF, "collected: ");
	str = ft_itoa(par->data.collectibleCounter);
	mlx_string_put(par->mlx, par->win, 185, par->HEIGHT + 32, 0X00FFFFFF, str);
	free(str);
}

void ft_check_player_tile(parameters *par)
{
	if (par->data.map[par->playerPosY][par->playerPosX] == 'C')
	{
		par->data.collectibleCounter++;
		par->data.map[par->playerPosY][par->playerPosX] = 'V';
	}
	else if (par->data.map[par->playerPosY][par->playerPosX] == 'E')
	{
		mlx_destroy_image(par->mlx, par->player);
		par->player = mlx_xpm_file_to_image(par->mlx, "./textures/end.xpm", &par->texture_width, &par->texture_height);
		mlx_put_image_to_window(par->mlx, par->win, par->player, par->playerPosX * TILE, par->playerPosY * TILE);
		if (par->data.collectibleCounter == par->data.collectibleCount)
		{
			ft_putstr("\033[1;32mCONGRATULATION YOU WON!\033[1;0m\n");
			par->controls = 0;
		}
	}
	else
	{
		mlx_destroy_image(par->mlx, par->player);
		par->player = mlx_xpm_file_to_image(par->mlx, "./textures/player1.xpm", &par->texture_width, &par->texture_height);
		mlx_put_image_to_window(par->mlx, par->win, par->player, par->playerPosX * TILE, par->playerPosY * TILE);
	}

}

void ft_render_walls(parameters *par, int line, int col)
{
	mlx_destroy_image(par->mlx, par->wall);
	if (par->data.map[line][col - 1] == '1' && par->data.map[line][col + 1] == '1')
		par->wall = mlx_xpm_file_to_image(par->mlx, "./textures/wallside.xpm", &par->texture_width, &par->texture_height);
	// else if (par->data.map[line - 1][col] == '1' && par->data.map[line + 1][col] == '1')
	// 	par->wall = mlx_xpm_file_to_image(par->mlx, "./textures/wallup.xpm", &par->texture_width, &par->texture_height);
	else
		par->wall = mlx_xpm_file_to_image(par->mlx, "./textures/wall.xpm", &par->texture_width, &par->texture_height);
	mlx_put_image_to_window(par->mlx, par->win, par->wall, col * TILE, line * TILE);
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
				ft_render_walls(par, line, col);
			else if (par->data.map[line][col] == 'E')
				mlx_put_image_to_window(par->mlx, par->win, par->exit, col * TILE, line * TILE);
			else if (par->data.map[line][col] == 'C')
			{
				mlx_destroy_image(par->mlx, par->collectible);
				par->collectible = mlx_xpm_file_to_image(par->mlx, "./textures/collectible1.xpm", &par->texture_width, &par->texture_height);
				mlx_put_image_to_window(par->mlx, par->win, par->collectible, col * TILE, line * TILE);
			}
			else if (par->data.map[line][col] == 'V')
			{
				mlx_destroy_image(par->mlx, par->collectible);
				par->collectible = mlx_xpm_file_to_image(par->mlx, "./textures/collectible2.xpm", &par->texture_width, &par->texture_height);
				mlx_put_image_to_window(par->mlx, par->win, par->collectible, col * TILE, line * TILE);
			}
			else
				mlx_put_image_to_window(par->mlx, par->win, par->background, col * TILE, line * TILE);
			col++;
		}
		line++;
	}
	// mlx_destroy_image(par->mlx, par->player);
	// par->player = mlx_xpm_file_to_image(par->mlx, "./textures/player1.xpm", &par->texture_width, &par->texture_height);
	// mlx_put_image_to_window(par->mlx, par->win, par->player, par->playerPosX * TILE, par->playerPosY * TILE);
}

int ft_keyboard_hook(int keycode, parameters *par)
{
	int old_x;
	int old_y;

	old_x = par->playerPosX;
	old_y = par->playerPosY;
	if (keycode == 65307)
		ft_exit(par);
	else if (keycode == 65361 && par->controls == 1)
	{
		//left
		if (par->playerPosX - 1 >= 0 && par->data.map[par->playerPosY][par->playerPosX - 1] != '1')
		{
			par->playerPosX--;
			par->playerMoves++;
			mlx_destroy_image(par->mlx, par->player);
			par->player = mlx_xpm_file_to_image(par->mlx, "./textures/player1.xpm", &par->texture_width, &par->texture_height);
		}
	}
	else if (keycode == 65362 && par->controls == 1)
	{
		//up
		if (par->playerPosY - 1 >= 0 && par->data.map[par->playerPosY - 1][par->playerPosX] != '1')
		{
			par->playerPosY--;
			par->playerMoves++;
		}
	}
	else if (keycode == 65363 && par->controls == 1)
	{
		//right
		if (par->playerPosX + 1 < par->data.lineLength && par->data.map[par->playerPosY][par->playerPosX + 1] != '1')
		{
			par->playerPosX++;
			par->playerMoves++;
			mlx_destroy_image(par->mlx, par->player);
			par->player = mlx_xpm_file_to_image(par->mlx, "./textures/player2.xpm", &par->texture_width, &par->texture_height);
		}
		
	}
	else if (keycode == 65364 && par->controls == 1)
	{
		//down
		if (par->playerPosY + 1 < par->data.nbLines && par->data.map[par->playerPosY + 1][par->playerPosX] != '1')
		{
			par->playerPosY++;
			par->playerMoves++;
		}
	}
	if (old_x != par->playerPosX || old_y != par->playerPosY)
	{
		ft_putstr("moves: ");
		ft_putnbr(par->playerMoves);
		ft_putchar('\n');
		ft_render_map(par);
		mlx_put_image_to_window(par->mlx, par->win, par->player, par->playerPosX * TILE, par->playerPosY * TILE);
		ft_check_player_tile(par);
		ft_display_text(par);
	}
	return (0);
}

int main(int argc, char **argv)
{
	parameters par;

	if (ft_check_args(argc, argv, &par.data) == -1)
		return (0);
	par.controls = 1;
	ft_get_map(argv[1], &par.data);
	par.playerMoves = 0;
	par.data.collectibleCounter = 0;
	par.WIDTH = TILE * par.data.lineLength;
	par.HEIGHT = TILE * par.data.nbLines;
	par.texture_height = TILE;
	par.texture_width = TILE;
	par.mlx = mlx_init();
	par.win = mlx_new_window(par.mlx, par.WIDTH, par.HEIGHT + TILE, "so_long");
	par.background = mlx_xpm_file_to_image(par.mlx, "./textures/background.xpm", &par.texture_width, &par.texture_height);
	par.player = mlx_xpm_file_to_image(par.mlx, "./textures/player1.xpm", &par.texture_width, &par.texture_height);
	par.wall = mlx_xpm_file_to_image(par.mlx, "./textures/wall.xpm", &par.texture_width, &par.texture_height);
	par.exit = mlx_xpm_file_to_image(par.mlx, "./textures/exit.xpm", &par.texture_width, &par.texture_height);
	par.collectible = mlx_xpm_file_to_image(par.mlx, "./textures/collectible1.xpm", &par.texture_width, &par.texture_height);
	par.img = mlx_new_image(par.mlx, par.WIDTH, TILE);
	par.playerPosX = par.data.cellP_y;
	par.playerPosY = par.data.cellP_x;
	ft_render_map(&par);
	ft_display_text(&par);
	mlx_put_image_to_window(par.mlx, par.win, par.player, par.playerPosX * TILE, par.playerPosY * TILE);
	mlx_loop_hook(par.mlx, NULL, NULL);
	mlx_hook(par.win, 17, 0, ft_exit, &par);
	mlx_hook(par.win, 2, 1L<<0, ft_keyboard_hook, &par);
	mlx_loop(par.mlx);
	ft_exit(&par);
}