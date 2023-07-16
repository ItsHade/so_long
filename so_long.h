#ifndef SO_LONG
# define SO_LONG

typedef struct s_mlx 
{
    void *mlx;
    void *win;
}   t_mlx;

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
//mlx system wide installed
// #include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
# include "minilibx-linux/mlx.h"

void ft_putstr(char *s);

void ft_putnbr(int nb);

void ft_putchar(char c);
#endif