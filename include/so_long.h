/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:08:58 by maburnet          #+#    #+#             */
/*   Updated: 2023/09/18 16:19:40 by maburnet         ###   ########.fr       */
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

//0XAARRGGBB
//AA = alpha, RR = red, GG = green, BB = blue
//00 = 0 | FF = 255
# define RED 0X00FF0000
# define BLUE 0X000000FF
# define GREEN 0X0000FF00
# define BLACK 0X00000000
# define WHITE 0X00FFFFFF

# define TILE 64

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

typedef struct s_textures
{
	void	*player;
	void	*player1;
	void	*floor;
	void	*wall;
	void	*wallside;
	void	*exit;
	void	*end;
	void	*col;
	void	*col1;
	void	*col2;
	void	*monster;
	void	*img;
}	t_textures;

typedef struct s_parameters
{
	t_textures	txt;
	t_data		data;
	void		*mlx;
	void		*win;
	int			playerposx;
	int			playerposy;
	int			width;
	int			height;
	int			playermoves;
	int			controls;
	int			death;
	int			direction;
	int			texture_height;
	int			texture_width;
}	t_parameters;

// UTILS FUNCTIONS

void	ft_putchar(char c);

void	ft_putstr(char *s);

void	ft_putmap(t_data data);

void	ft_putnbr(int nb);

char	*ft_itoa(int num);

int		ft_intlen(int num);

// PARSING FUNCTIONS

int		ft_check_file_format(char *file);

int		ft_check_args(int argc, char **argv, t_data *data);

void	ft_get_starting_pos(t_data *data);

int		ft_check_map_requirement(t_data *data_ptr);

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

int		ft_check_args(int argc, char **argv, t_data *data);

// MLX FUNCTIONS

void	ft_initialize_textures(t_parameters *par);

void	ft_render_map(t_parameters *par);

void	ft_display_text(t_parameters *par);

int		ft_keyboard_hook(int keycode, t_parameters *par);

void	ft_initialize(t_parameters *par, char *file);

// CLEANING UP FUNCTIONS

int		ft_exit(t_parameters *par);

void	ft_freemap(t_data data);

#endif
