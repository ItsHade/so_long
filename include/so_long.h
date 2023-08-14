#ifndef SO_LONG
# define SO_LONG

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"
//mlx system wide installed
// #include <mlx.h>

// position x and y of the cell and rotate represent wich side we will check next 0 - top, 1 - right, 2 - bottom, 3 - left
typedef struct s_data
{
    char **map;
    int cellP_x;
    int cellP_y;
    int collectibleCounter;
    int collectibleCount;
    int nbLines;
    int lineLength;
    int exitFound;
} t_data;

typedef struct s_cell
{
    int x;
    int y;
    int rotate;
} t_cell;

typedef struct s_mlx 
{
    void *mlx;
    void *win;
}   t_mlx;

void ft_putchar(char c);

void ft_putstr(char *s);

void ft_putmap(t_data data);

void ft_putnbr(int nb);

int ft_check_file_format(char *file);

int ft_check_map_requirement(t_data *data_ptr);

void ft_freemap(t_data data);

int ft_get_map(char *file, t_data *data_ptr);

int ft_check_map_requirement(t_data *data_ptr);

int ft_check_file_format(char *file);

int ft_check_for_side_walls(t_data data);

int ft_check_for_opposite_walls(t_data data);

int ft_get_number_of_lines(char *file, t_data *data_ptr);

int ft_get_line_length(char *file, t_data *data_ptr);

char ft_check_next_cell(t_data data, t_cell cell);

t_cell ft_get_next_cell(t_cell cell);

int ft_is_wall(char cell_content);

int ft_is_visited(char cell_content);

int ft_check_valid_path(t_data *data_ptr, t_cell cell);

//
void ft_putdata(t_data data, t_cell cell);

int ft_check_args(int argc, char **argv, t_data *data);

#endif