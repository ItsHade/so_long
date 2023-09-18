/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:56:44 by maburnet          #+#    #+#             */
/*   Updated: 2023/09/18 16:29:39 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_display_text(t_parameters *par)
{
	char	*str;

	mlx_put_image_to_window(par->mlx, par->win, par->txt.img, 0, par->height);
	mlx_string_put(par->mlx, par->win, 20, par->height + 32, WHITE, "moves: ");
	str = ft_itoa(par->playermoves);
	mlx_string_put(par->mlx, par->win, 60, par->height + 32, WHITE, str);
	free(str);
	mlx_string_put(par->mlx, par->win, 110, par->height + 32, WHITE,
		"collected: ");
	str = ft_itoa(par->data.collectible_counter);
	mlx_string_put(par->mlx, par->win, 175, par->height + 32, WHITE, str);
	free(str);
	mlx_string_put(par->mlx, par->win, 190, par->height + 32, WHITE, "/");
	str = ft_itoa(par->data.collectible_count);
	mlx_string_put(par->mlx, par->win, 200, par->height + 32, WHITE, str);
	free(str);
	if (par->death == 1)
	{
		mlx_put_image_to_window(par->mlx, par->win, par->txt.monster,
			par->playerposx * TILE, par->playerposy * TILE);
		mlx_put_image_to_window(par->mlx, par->win, par->txt.img,
			0, par->height);
		mlx_string_put(par->mlx, par->win, 70, par->height + 32,
			RED, "YOU LOSE!");
	}
}

void	ft_render_map2(t_parameters *par, int line, int col)
{
	if (par->data.map[line][col] == '1')
		mlx_put_image_to_window(par->mlx, par->win, par->txt.wall,
			col * TILE, line * TILE);
	else if (par->data.map[line][col] == 'E')
		mlx_put_image_to_window(par->mlx, par->win, par->txt.exit,
			col * TILE, line * TILE);
	else if (par->data.map[line][col] == 'C')
		mlx_put_image_to_window(par->mlx, par->win, par->txt.col1,
			col * TILE, line * TILE);
	else if (par->data.map[line][col] == 'V')
		mlx_put_image_to_window(par->mlx, par->win, par->txt.col2,
			col * TILE, line * TILE);
	else if (par->data.map[line][col] == 'M')
		mlx_put_image_to_window(par->mlx, par->win, par->txt.monster,
			col * TILE, line * TILE);
	else
		mlx_put_image_to_window(par->mlx, par->win, par->txt.floor,
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
			ft_render_map2(par, line, col);
			col++;
		}
		line++;
	}
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
	par->txt.exit = mlx_xpm_file_to_image(par->mlx, "./textures/exit.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.end = mlx_xpm_file_to_image(par->mlx, "./textures/end.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.col1 = mlx_xpm_file_to_image(par->mlx, "./textures/col1.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.col2 = mlx_xpm_file_to_image(par->mlx, "./textures/col2.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.monster = mlx_xpm_file_to_image(par->mlx, "./textures/monster.xpm",
			&par->texture_width, &par->texture_height);
	par->txt.img = mlx_new_image(par->mlx, par->width, TILE);
}

void	ft_initialize(t_parameters *par, char *file)
{
	par->controls = 1;
	par->death = 0;
	par->direction = 0;
	ft_get_map(file, &par->data);
	par->playermoves = 0;
	par->data.collectible_counter = 0;
	par->width = TILE * par->data.linelength;
	par->height = TILE * par->data.nblines;
	par->texture_height = TILE;
	par->texture_width = TILE;
}
