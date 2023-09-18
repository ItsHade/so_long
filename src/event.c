/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:06:43 by maburnet          #+#    #+#             */
/*   Updated: 2023/09/18 16:24:55 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_check_player_tile(t_parameters *par)
{
	if (par->data.map[par->playerposy][par->playerposx] == 'M')
	{
		ft_putstr("\033[1;31mYOU LOSE!\033[1;0m\n");
		par->controls = 0;
		par->death = 1;
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
			par->death = -1;
		}
	}
}

void	ft_move_up_down(int keycode, t_parameters *par)
{
	if (keycode == 65362 && par->controls == 1)
	{
		par->direction = 0;
		if (par->playerposy - 1 >= 0
			&& par->data.map[par->playerposy - 1][par->playerposx] != '1')
		{
			par->playerposy--;
			par->playermoves++;
		}
	}
	else if (keycode == 65364 && par->controls == 1)
	{
		par->direction = 1;
		if (par->playerposy + 1 < par->data.nblines
			&& par->data.map[par->playerposy + 1][par->playerposx] != '1')
		{
			par->playerposy++;
			par->playermoves++;
		}
	}
}

void	ft_move_left_right(int keycode, t_parameters *par)
{
	if (keycode == 65361 && par->controls == 1)
	{
		par->direction = 0;
		if (par->playerposx - 1 >= 0
			&& par->data.map[par->playerposy][par->playerposx - 1] != '1')
		{
			par->playerposx--;
			par->playermoves++;
		}
	}
	else if (keycode == 65363 && par->controls == 1)
	{
		par->direction = 1;
		if (par->playerposx + 1 < par->data.linelength
			&& par->data.map[par->playerposy][par->playerposx + 1] != '1')
		{
			par->playerposx++;
			par->playermoves++;
		}
	}
}

int	ft_keyboard_hook(int keycode, t_parameters *par)
{
	int	old_x;
	int	old_y;

	old_x = par->playerposx;
	old_y = par->playerposy;
	if (keycode == 65307)
		ft_exit(par);
	ft_move_up_down(keycode, par);
	ft_move_left_right(keycode, par);
	if (old_x != par->playerposx || old_y != par->playerposy)
	{
		ft_putstr("moves: ");
		ft_putnbr(par->playermoves);
		ft_putchar('\n');
		ft_render_map(par);
		if (par->direction == 0)
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
