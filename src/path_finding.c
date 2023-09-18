/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:58:19 by maburnet          #+#    #+#             */
/*   Updated: 2023/09/18 15:55:13 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	ft_check_next_cell(t_data data, t_cell cell)
{
	char	c;

	c = 0;
	if (cell.rotate == 0)
		c = data.map[cell.x - 1][cell.y];
	else if (cell.rotate == 1)
		c = data.map[cell.x][cell.y + 1];
	else if (cell.rotate == 2)
		c = data.map[cell.x + 1][cell.y];
	else if (cell.rotate == 3)
		c = data.map[cell.x][cell.y - 1];
	if (cell.rotate > 3)
	{
		ft_putstr("CHECK WARNING!\n");
	}
	return (c);
}

int	ft_is_visited(char cell_content)
{
	if (cell_content == '#')
		return (1);
	return (0);
}

int	ft_is_wall(char cell_content)
{
	if (cell_content == '1' || cell_content == 'M')
		return (1);
	return (0);
}

t_cell	ft_get_next_cell(t_cell cell)
{
	if (cell.rotate == 0)
		cell.x -= 1;
	else if (cell.rotate == 1)
		cell.y += 1;
	else if (cell.rotate == 2)
		cell.x += 1;
	else if (cell.rotate == 3)
		cell.y -= 1;
	else
	{
		ft_putstr("GET WARNING!\n");
	}
	cell.rotate = 0;
	return (cell);
}

int	ft_check_valid_path(t_data *data_ptr, t_cell cell)
{
	while (cell.rotate < 4)
	{
		data_ptr->map[cell.x][cell.y] = '#';
		if (ft_is_wall(ft_check_next_cell(*data_ptr, cell)) == 1
			|| ft_is_visited(ft_check_next_cell(*data_ptr, cell)) == 1)
			cell.rotate++;
		else
		{
			if (ft_check_next_cell(*data_ptr, cell) == 'E')
				data_ptr->exitfound++;
			else if (ft_check_next_cell(*data_ptr, cell) == 'C')
				data_ptr->collectible_counter++;
			ft_check_valid_path(data_ptr, ft_get_next_cell(cell));
		}
	}
	if (cell.rotate > 3)
	{
		cell.rotate = 0;
		return (-1);
	}
	return (0);
}
