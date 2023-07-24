#include "../include/so_long.h"

typedef struct s_cell {
    int pos_x;
    int pos_y;
    int front;
} t_cell;

t_cell ft_go_to_next_cell(t_cell cell)
{
    if (cell.front == 0)
        cell.pos_x -= 1;
    else if (cell.front == 1)
        cell.pos_y += 1;
    else if (cell.front == 2)
        cell.pos_x += 1;
    else if (cell.front == 3)
        cell.pos_y -= 1;
    return (cell);
}

int main(void)
{
    t_cell cell;
    char tab[3][2];
    char tab2[3][2];

    tab[0][0] = '1';
    tab[0][1] = '1';
    tab[1][0] = '1';
    tab[1][1] = '1';
    tab[2][0] = '1';
    tab[2][1] = '1';

    cell.pos_x = 2;
    cell.pos_y = 2;
    cell.front = 3;
    printf("[%d][%d]\n", cell.pos_x, cell.pos_y);
    cell = ft_go_to_next_cell(cell);
    printf("[%d][%d]\n", cell.pos_x, cell.pos_y);
    cell = ft_go_to_next_cell(cell);
    printf("[%d][%d]\n", cell.pos_x, cell.pos_y);
    cell = ft_go_to_next_cell(cell);
    printf("[%d][%d]\n", cell.pos_x, cell.pos_y);
    cell.front = 0;
    cell = ft_go_to_next_cell(cell);
    printf("[%d][%d]\n", cell.pos_x, cell.pos_y);
    cell = ft_go_to_next_cell(cell);
    printf("[%d][%d]\n", cell.pos_x, cell.pos_y);
    tab2[2][1] = tab[2][1];
    ft_putchar(tab2[2][1]); 
}