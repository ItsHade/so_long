#include "../include/so_long.h"

void ft_freemap(t_data data)
{
    int line;

    line = 0;
    while (line < data.nbLines)
    {
        free(data.map[line]);
        line++;
    }
    free(data.map);
}

int ft_get_map(char *file, t_data *data_ptr)
{
    int fd;
    int nbBytesRead;
    int line;

    nbBytesRead = 0;
    line = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        exit(EXIT_FAILURE);
    data_ptr->map = malloc(sizeof(char *) * ((data_ptr->nbLines)));
    if (!data_ptr->map)
        return (close(fd), -1);
    while (line < data_ptr->nbLines)
    {
        data_ptr->map[line] = malloc(sizeof(char) * (data_ptr->lineLength + 1));
        if (!data_ptr->map[line])
            return (close(fd), -1);
        nbBytesRead = read(fd, data_ptr->map[line], data_ptr->lineLength + 1);
        if (nbBytesRead == -1)
            exit(EXIT_FAILURE);
        data_ptr->map[line][data_ptr->lineLength] = 0;
        line++;
    }
    return (close(fd), 0);
}

//function has more than 25 lines
int ft_check_map_requirement(t_data *data_ptr)
{
    int line;
    int col;
    int countPlayerStart;
    int countExits;

    line = 0;
    countExits = 0;
    countPlayerStart = 0;
    data_ptr->collectibleCount = 0;
    while (line < data_ptr->nbLines)
    {
        col = 0;
        while (col < data_ptr->lineLength)
        {
            if (data_ptr->map[line][col] == 'P')
            {
                data_ptr->cellP_x = line;
                data_ptr->cellP_y = col;
                countPlayerStart++;
            }
            else if (data_ptr->map[line][col] == 'E')
                countExits++;
            else if (data_ptr->map[line][col] == 'C')
                data_ptr->collectibleCount++;
            else if (data_ptr->map[line][col] != '0' && data_ptr->map[line][col] != '1')
                return (-1);
            col++;
        }
        line++;
    }
    if (countPlayerStart != 1 || countExits != 1 || data_ptr->collectibleCount < 1)
        return (-1);
    return (0);
}

int ft_check_file_format(char *file)
{
    int i_file;
    int i_neededFormat;
    int fd;
    char *neededFormat;

    i_file = 0;
    i_neededFormat = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (-1);
    close(fd);
    neededFormat = malloc(sizeof(char) * 5);
    neededFormat = ".ber";
    while (file[i_file] != 0)
        i_file++;
    i_file -= 4;
    while (file[i_file] != 0)
    {
        if (file[i_file] != neededFormat[i_neededFormat])
            return (-1);
        i_file++;
        i_neededFormat++;
    }
    return (0);
}