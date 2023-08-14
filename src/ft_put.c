#include "../include/so_long.h"

void ft_putchar(char c)
{
    write (1, &c, 1);
}

void ft_putstr(char *s)
{
	int i;
	
	i = 0;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
}

void ft_putmap(t_data data)
{
    int line;
    int col;

    line = 0;
    while (line < data.nbLines)
    {
        col = 0;
        while (col < data.lineLength)
        {
            ft_putchar('[');
            ft_putchar(data.map[line][col]);
            ft_putchar(']');
            col++;
        }
        ft_putchar('\n');
        line++;
    }
}

void ft_putnbr(int nb)
{
    int num;

    if (nb < 0)
    {
        num = -nb;
        ft_putchar('-');
    }
    else
        num = nb;
    if (num <= 9)
        ft_putchar(num + 48);
    else
    {
        ft_putnbr(num / 10);
        ft_putchar(num % 10 + 48);
    }
}

// not usefull in the final build
void ft_putdata(t_data data, t_cell cell)
{
    ft_putstr("------PRINTING DATA------\n");
    // i thing pos x and y are always just the starting pos x and y
    ft_putstr("pos_x: ");
    ft_putnbr(cell.x);
    ft_putstr("\npos_y: ");
    ft_putnbr(cell.y);
    ft_putchar('\n');
    ft_putstr("starting pos x: ");
    ft_putnbr(data.cellP_x);
    ft_putstr("\nstarting pos y: ");
    ft_putnbr(data.cellP_y);
    ft_putchar('\n');
    ft_putnbr(data.collectibleCounter);
    ft_putchar('/');
    ft_putnbr(data.collectibleCount);
    ft_putstr(" collectibles\nExit found: ");
    ft_putnbr(data.exitFound);
    ft_putchar('\n');
    ft_putmap(data);
    ft_putstr("-------------------------\n");
}