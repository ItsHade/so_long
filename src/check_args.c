/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:25:43 by hade              #+#    #+#             */
/*   Updated: 2023/09/18 15:50:35 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_check_args2(t_data *data)
{
	t_cell	cell;

	data->collectible_counter = 0;
	data->exitfound = 0;
	cell.x = data->cellp_x;
	cell.y = data->cellp_y;
	cell.rotate = 0;
	ft_check_valid_path(data, cell);
	if (data->exitfound != 1
		|| data->collectible_counter != data->collectible_count)
		return (-1);
	ft_freemap(*data);
	return (0);
}

int	ft_check_args(int argc, char **argv, t_data *data)
{
	if (argc < 2)
		return (ft_putstr("Error\nArguments invalids!\n"), -1);
	if (ft_check_file_format(argv[1]) == -1)
		return (ft_putstr("Error\nFile has wrong format!\n"), -1);
	else if (ft_check_file_format(argv[1]) == -2)
		return (ft_putstr("Error\nFile doesn't exist!\n"), -1);
	if (ft_get_line_length(argv[1], data) < 3
		|| ft_get_number_of_lines(argv[1], data) < 3)
		return (ft_putstr("Error\nInvalid map!\n"), -1);
	if (ft_get_map(argv[1], data) == -1 || data->map == NULL)
		return (ft_putstr("Error\nAn error has occured!\n"), -1);
	if (ft_check_for_side_walls(*data) == -1)
		return (ft_freemap(*data), ft_putstr("Error\nInvalid wall!\n"), -1);
	if (ft_check_map_requirement(data) == -1)
		return (ft_freemap(*data), ft_putstr("Error\nInvalid map!\n"), -1);
	if (ft_check_args2(data) == -1)
		return (ft_freemap(*data), ft_putstr("Error\nNo valid path!\n"), -1);
	return (0);
}
