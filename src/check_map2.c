/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:58:10 by maburnet          #+#    #+#             */
/*   Updated: 2023/09/18 16:27:02 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_get_line_length(char *file, t_data *data_ptr)
{
	char	buffer[1];
	int		bytes;
	int		fd;

	buffer[0] = 0;
	data_ptr->linelength = 0;
	bytes = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (bytes != 0)
	{
		bytes = read(fd, buffer, 1);
		if (buffer[0] == '\n' || bytes == 0)
			break ;
		data_ptr->linelength++;
	}
	close(fd);
	return (data_ptr->linelength);
}

int	ft_get_number_of_lines(char *file, t_data *data_ptr)
{
	char	buffer[1];
	int		fd;
	int		length;

	data_ptr->nblines = 1;
	length = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (read(fd, buffer, 1) != 0)
	{
		length++;
		if ((buffer[0] == '\n'))
		{
			if (length != data_ptr->linelength + 1)
				return (ft_putstr("La map ne respecte pas les regles!\n"),
					close(fd), -1);
			data_ptr->nblines++;
			length = 0;
		}
	}
	if (buffer[0] == '\n')
		data_ptr->nblines--;
	return (close(fd), data_ptr->nblines);
}

int	ft_check_for_side_walls(t_data data)
{
	int	col;

	col = 0;
	while (col < data.linelength)
	{
		if (data.map[0][col] != '1')
			return (ft_putstr("Probleme mur du haut\n"), -1);
		col++;
	}
	col = 0;
	while (col < data.linelength)
	{
		if (data.map[data.nblines - 1][col] != '1')
			return (ft_putstr("Probleme mur du bas\n"), -1);
		col++;
	}
	if (ft_check_for_opposite_walls(data) == -1)
		return (-1);
	return (0);
}

int	ft_check_for_opposite_walls(t_data data)
{
	int	line;

	line = 0;
	while (line < data.nblines)
	{
		if (data.map[line][0] != '1')
			return (ft_putstr("Probleme mur du gauche\n"), -1);
		line++;
	}
	line = 0;
	while (line < data.nblines)
	{
		if (data.map[line][data.linelength - 1] != '1')
			return (ft_putstr("Probleme mur de droite\n"), -1);
		line++;
	}
	return (0);
}

void	ft_get_starting_pos(t_data *data)
{
	int	line;
	int	col;

	line = 0;
	while (line < data->nblines)
	{
		col = 0;
		while (col < data->linelength)
		{
			if (data->map[line][col] == 'P')
			{
				data->cellp_x = line;
				data->cellp_y = col;
			}
			col++;
		}
		line++;
	}
}
