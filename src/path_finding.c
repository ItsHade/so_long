#include "../include/so_long.h"

char ft_check_next_cell(t_data data, t_cell cell)
{
    char c;

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

int ft_is_visited(char cell_content)
{
    if (cell_content == '#')
        return (1);
    return (0);
}

int ft_is_wall(char cell_content)
{
    if (cell_content == '1')
        return (1);
    return (0);
}

t_cell ft_get_next_cell(t_cell cell)
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

//not over 25 lines without the debuging lines
int ft_check_valid_path(t_data *data_ptr, t_cell cell)
{
    while (cell.rotate < 4)
    {
        data_ptr->map[cell.x][cell.y] = '#';
        if (ft_is_wall(ft_check_next_cell(*data_ptr, cell)) == 1 || ft_is_visited(ft_check_next_cell(*data_ptr, cell)) == 1)
            cell.rotate++;
        else
        {
            if (ft_check_next_cell(*data_ptr, cell) == 'E')
                data_ptr->exitFound++;
            else if (ft_check_next_cell(*data_ptr, cell) == 'C')
                data_ptr->collectibleCounter++;
            ft_check_valid_path(data_ptr, ft_get_next_cell(cell));
        }
        /*
        ft_putstr("x: ");
        ft_putnbr(cell.x);
        ft_putstr(" y: " );
        ft_putnbr(cell.y);
        ft_putstr(" exit: ");
        ft_putnbr(data_ptr->exitFound);
        ft_putstr(" rotate: ");
        ft_putnbr(cell.rotate);
        ft_putchar('\n');
        ft_putmap(*data_ptr);
        */
    }
    if (cell.rotate > 3)
    {
        cell.rotate = 0;
        return (-1);
    }
    return (0);
}


// if this return 0 then all good
int ft_check_args(int argc, char **argv, t_data *data)
{
    t_cell cell;

    if (argc < 2)
    {
        ft_putstr("not enough arguments!\n");
        return (-1);
    }
    if (ft_check_file_format(argv[1]) == -1)
    {
        ft_putstr("Wrong format\n");
        return (-1);
    }
    else if (ft_check_file_format(argv[1]) == -2)
    {
        ft_putstr("file doesn't exist\n");
        return (-1);
    }
    ft_get_line_length(argv[1], data);
    ft_putstr("Lines length is: ");
    ft_putnbr(data->lineLength);
    ft_putchar('\n');
    ft_get_number_of_lines(argv[1], data);
    ft_putstr("Number of lines: ");
    ft_putnbr(data->nbLines);
    ft_putchar('\n');
    if (ft_get_map(argv[1], data) == -1)
        return(ft_putstr("An error has occured!\n"), -1);
    if (!data->map)
        return (-1);
    ft_putmap(*data);
    if (ft_check_for_side_walls(*data) == -1)
    {
        ft_putstr("La map n'est pas entouree de murs\n");
        return (ft_freemap(*data), -1);
    }
    if (ft_check_map_requirement(data) == -1)
    {
        ft_putstr("Il y a un probleme avec la carte\n");
        return (ft_freemap(*data), -1);
    }
    else
        ft_putstr("MAP IS GUD!!!!!!!\n");
    data->collectibleCounter = 0;
    data->exitFound = 0;
    cell.x = data->cellP_x;
    cell.y = data->cellP_y;
    cell.rotate = 0;
    ft_check_valid_path(data, cell);
    if (data->exitFound == 1 && data->collectibleCounter == data->collectibleCount)
        ft_putstr("\033[1;32mMAP IS SOLVABLE!\033[1;0m\n");
    else
        return (ft_putstr("\033[1;31mPATHING PROBLEM!\033[1;0m\n"), -1);
    ft_putdata(*data, cell);
    ft_freemap(*data);
    return (0);
}