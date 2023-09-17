/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:58:24 by maburnet          #+#    #+#             */
/*   Updated: 2023/09/17 14:58:24 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_exit(t_parameters *par)
{
	mlx_destroy_image(par->mlx, par->txt.floor);
	mlx_destroy_image(par->mlx, par->txt.player);
	mlx_destroy_image(par->mlx, par->txt.player1);
	mlx_destroy_image(par->mlx, par->txt.wall);
	mlx_destroy_image(par->mlx, par->txt.wallside);
	mlx_destroy_image(par->mlx, par->txt.exit);
	mlx_destroy_image(par->mlx, par->txt.end);
	mlx_destroy_image(par->mlx, par->txt.col);
	mlx_destroy_image(par->mlx, par->txt.col1);
	mlx_destroy_image(par->mlx, par->txt.col2);
	mlx_destroy_image(par->mlx, par->txt.monster)
	mlx_destroy_image(par->mlx, par->txt.img);
	mlx_destroy_window(par->mlx, par->win);
	mlx_destroy_display(par->mlx);
	free(par->mlx);
	ft_freemap(par->data);
	exit(0);
	return (0);
}

void	ft_display_text(t_parameters *par)
{
	char	*str;

	mlx_put_image_to_window(par->mlx, par->win, par->txt.img, 0, par->height);
	mlx_string_put(par->mlx, par->win, 20, par->height + 32, WHITE, "moves: ");
	str = ft_itoa(par->playermoves);
	mlx_string_put(par->mlx, par->win, 60, par->height + 32, WHITE, str);
	free(str);
	mlx_string_put(par->mlx, par->win, 120, par->height + 32, WHITE,
		"collected: ");
	str = ft_itoa(par->data.collectible_counter);
	mlx_string_put(par->mlx, par->win, 185, par->height + 32, WHITE, str);
	free(str);
}

void	ft_check_player_tile(t_parameters *par)
{
	if (par->data.map[par->playerposy][par->playerposx] == 'M')
	{
		ft_putstr("\033[1;32mYOU LOSE!\033[1;0m\n");
		par->controls = 0;
	}
	else if (par->data.map[par->playerposy][par->playerposx] == 'C')
	{
		par->data.collectible_counter++;
		par->data.map[par->playerposy][par->playerposx] = 'V';
	}
	else if (par->data.map[par->playerposy][par->playerposx] == 'E')
	{
		mlx_put_image_to_window(par->mlx, par->win, par->txt.end,
			par->playerposx * TILE, par->playerposy * TILE);
		if (par->data.collectible_counter == par->data.collectible_count)
		{
			ft_putstr("\033[1;32mCONGRATULATION YOU WON!\033[1;0m\n");
			par->controls = 0;
		}
	}
	// else
	// {
	// 	mlx_put_image_to_window(par->mlx, par->win, par->txt.player,
	// 		par->playerposx * TILE, par->playerposy * TILE);
	// }
}

void	ft_render_walls(t_parameters *par, int line, int col)
{
	if (par->data.map[line][col - 1] == '1'
		&& par->data.map[line][col + 1] == '1')
		mlx_put_image_to_window(par->mlx, par->win, par->txt.wallside,
			col * TILE, line * TILE);
	else
		mlx_put_image_to_window(par->mlx, par->win, par->txt.wall,
			col * TILE, line * TILE);

}

void	ft_render_map(t_parameters *par)
{
	int	line;
	int	col;

	line = 0;
	while (line < par->data.nblines)
	{
		col = 0;
		while (col < par->data.linelength)
		{
			if (par->data.map[line][col] == '1')
			{
				mlx_put_image_to_window(par->mlx, par->win, par->txt.wall, col * TILE, line * TILE);
				// ft_render_walls(par, line, col);
			}
			else if (par->data.map[line][col] == 'E')
			{
				mlx_put_image_to_window(par->mlx, par->win, par->txt.exit, col * TILE, line * TILE);
			}
			else if (par->data.map[line][col] == 'C')
			{
				mlx_put_image_to_window(par->mlx, par->win, par->txt.col1, col * TILE, line * TILE);
			}
			else if (par->data.map[line][col] == 'V')
			{
				mlx_put_image_to_window(par->mlx, par->win, par->txt.col2, col * TILE, line * TILE);
			}
			else if (par->data.map[line][col] == 'M')
			{
				mlx_put_image_to_window(par->mlx, par->win, par->txt.monster, col * TILE, line * TILE);
			}
			else
			{
				mlx_put_image_to_window(par->mlx, par->win, par->txt.floor, col * TILE, line * TILE);
			}
			col++;
		}
		line++;
	}
}

int	ft_keyboard_hook(int keycode, t_parameters *par)
{
	int	old_x;
	int	old_y;
	int	direction;

	old_x = par->playerposx;
	old_y = par->playerposy;
	direction = 0;
	if (keycode == 65307)
		ft_exit(par);
	else if (keycode == 65361 && par->controls == 1)
	{
		direction = 0;
		if (par->playerposx - 1 >= 0 && par->data.map[par->playerposy][par->playerposx - 1] != '1')
		{
			par->playerposx--;
			par->playermoves++;
		}
	}
	else if (keycode == 65362 && par->controls == 1)
	{
		direction = 0;
		if (par->playerposy - 1 >= 0 && par->data.map[par->playerposy - 1][par->playerposx] != '1')
		{
			par->playerposy--;
			par->playermoves++;
		}

	}
	else if (keycode == 65363 && par->controls == 1)
	{
		direction = 1;
		if (par->playerposx + 1 < par->data.linelength && par->data.map[par->playerposy][par->playerposx + 1] != '1')
		{
			par->playerposx++;
			par->playermoves++;
		}

	}
	else if (keycode == 65364 && par->controls == 1)
	{
		direction = 1;
		if (par->playerposy + 1 < par->data.nblines &&
			par->data.map[par->playerposy + 1][par->playerposx] != '1')
		{
			par->playerposy++;
			par->playermoves++;
		}
	}
	if (old_x != par->playerposx || old_y != par->playerposy)
	{
		ft_putstr("moves: ");
		ft_putnbr(par->playermoves);
		ft_putchar('\n');
		ft_render_map(par);
		if (direction == 0)
			mlx_put_image_to_window(par->mlx, par->win, par->txt.player,
				par->playerposx * TILE, par->playerposy * TILE);
		else
			mlx_put_image_to_window(par->mlx, par->win, par->txt.player1,
				par->playerposx * TILE, par->playerposy * TILE);
		ft_check_player_tile(par);
		ft_display_text(par);
	}
	return (0);
}

void	ft_initialize_textures(t_parameters *par)
{
	par->txt.floor = mlx_xpm_file_to_image(par->mlx, "./textures/floor.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.player = mlx_xpm_file_to_image(par->mlx, "./textures/player1.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.player1 = mlx_xpm_file_to_image(par->mlx, "./textures/player2.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.wall = mlx_xpm_file_to_image(par->mlx, "./textures/wall.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.wallside = mlx_xpm_file_to_image(par->mlx, "./textures/wallside.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.exit = mlx_xpm_file_to_image(par->mlx, "./textures/exit.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.end = mlx_xpm_file_to_image(par->mlx, "./textures/end.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.col = mlx_xpm_file_to_image(par->mlx, "./textures/col.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.col1 = mlx_xpm_file_to_image(par->mlx, "./textures/col1.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.col2 = mlx_xpm_file_to_image(par->mlx, "./textures/col2.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.monster = mlx_xpm_file_to_image(par->mlx, "./textures/monster.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.img = mlx_new_image(par->mlx, par->width, TILE);
}

int	main(int argc, char **argv)
{
	t_parameters	par;

	if (ft_check_args(argc, argv, &par.data) == -1)
		return (0);
	par.controls = 1;
	ft_get_map(argv[1], &par.data);
	par.playermoves = 0;
	par.data.collectible_counter = 0;
	par.width = TILE * par.data.linelength;
	par.height = TILE * par.data.nblines;
	par.texture_height = TILE;
	par.texture_width = TILE;
	par.mlx = mlx_init();
	par.win = mlx_new_window(par.mlx, par.width, par.height + TILE, "so_long");
	par.playerposx = par.data.cellp_y;
	par.playerposy = par.data.cellp_x;
	ft_initialize_textures(&par);
	ft_render_map(&par);
	ft_display_text(&par);
	mlx_put_image_to_window(par.mlx, par.win, par.txt.player, par.playerposx * TILE,
		par.playerposy * TILE);
	mlx_loop_hook(par.mlx, NULL, NULL);
	mlx_hook(par.win, 17, 0, ft_exit, &par);
	mlx_hook(par.win, 2, 1L<<0, ft_keyboard_hook, &par);
	mlx_loop(par.mlx);
	ft_exit(&par);
}
