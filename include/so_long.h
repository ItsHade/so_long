/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:08:58 by maburnet          #+#    #+#             */
/*   Updated: 2023/09/06 18:31:29 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"
//mlx system wide installed
// #include <mlx.h>

typedef struct s_data
{
	char	**map;
	int		cellp_x;
	int		cellp_y;
	int		collectible_counter;
	int		collectible_count;
	int		nblines;
	int		linelength;
	int		exitfound;
}	t_data;

typedef struct s_cell
{
	int	x;
	int	y;
	int	rotate;
}	t_cell;

typedef struct s_parameters
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*player;
	void	*background;
	void	*wall;
	void	*exit;
	void	*collectible;
	t_data	data;
	int		playerposx;
	int		playerposy;
	int		width;
	int		height;
	int		playermoves;
	int		controls;
	int		texture_height;
	int		texture_width;
}	t_parameters;

void	ft_putchar(char c);

void	ft_putstr(char *s);

void	ft_putmap(t_data data);

void	ft_putnbr(int nb);

int		ft_check_file_format(char *file);

int		ft_check_map_requirement(t_data *data_ptr);

void	ft_freemap(t_data data);

int		ft_get_map(char *file, t_data *data_ptr);

int		ft_check_map_requirement(t_data *data_ptr);

int		ft_check_file_format(char *file);

int		ft_check_for_side_walls(t_data data);

int		ft_check_for_opposite_walls(t_data data);

int		ft_get_number_of_lines(char *file, t_data *data_ptr);

int		ft_get_line_length(char *file, t_data *data_ptr);

char	ft_check_next_cell(t_data data, t_cell cell);

t_cell	ft_get_next_cell(t_cell cell);

int		ft_is_wall(char cell_content);

int		ft_is_visited(char cell_content);

int		ft_check_valid_path(t_data *data_ptr, t_cell cell);

//
void	ft_putdata(t_data data, t_cell cell);

int		ft_check_args(int argc, char **argv, t_data *data);

char	*ft_itoa(int num);

int		ft_intlen(int num);

void	ft_render_map(t_parameters *par);

#endif