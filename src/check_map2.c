#include "../include/so_long.h"

int ft_get_line_length(char *file, t_data *data_ptr)
{
    char buffer[1];
    int nbBytesRead;
    int fd;

    buffer[0] = 0;
    data_ptr->lineLength = 0;
    nbBytesRead = 1;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (-1);
    while (nbBytesRead != 0)
    {
        nbBytesRead = read(fd, buffer, 1);
        if (buffer[0] == '\n' || nbBytesRead == 0)
            break;
        data_ptr->lineLength++;
    }
    close(fd);
    return (0);
}

//function has more than 25 lines
int ft_get_number_of_lines(char *file, t_data *data_ptr)
{
    char buffer[1];
    int nbBytesRead;
    int fd;
    int currentLength;

    data_ptr->nbLines = 0;
    nbBytesRead = 1;
    currentLength = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (-1);
    if (read(fd, buffer, 1) == 0)
        return (close(fd), 0);
    currentLength++;
    while (nbBytesRead != 0)
    {
        nbBytesRead = read(fd, buffer, 1);
        currentLength++;
        if ((buffer[0] == '\n') || (nbBytesRead == 0))
        {
            if (currentLength != data_ptr->lineLength + 1)
            {
                ft_putstr("La map ne respecte pas les regles!\n");
                close(fd);
                exit(EXIT_FAILURE);
            }
            data_ptr->nbLines++;
            currentLength = 0;
        }
    }
    return (close(fd), 0);
}

int ft_check_for_side_walls(t_data data)
{
    int col;

    col = 0;
    while (col < data.lineLength)
    {
        if (data.map[0][col] != '1')
            return (ft_putstr("Probleme mur du haut\n"), -1);
        col++;
    }
    col = 0;
    while (col < data.lineLength)
    {
        if (data.map[data.nbLines - 1][col] != '1')
            return (ft_putstr("Probleme mur du bas\n"), -1);
        col++;
    }
    if (ft_check_for_opposite_walls(data) == -1)
        return (-1);
    return (0);
}

int ft_check_for_opposite_walls(t_data data)
{
    int line;

    line = 0;
    while (line < data.nbLines)
    {
        if (data.map[line][0] != '1')
            return (ft_putstr("Probleme mur du gauche\n"), -1);
        line++;
    }
    line = 0;
    while (line < data.nbLines)
    {
        if (data.map[line][data.lineLength - 1] != '1')
            return (ft_putstr("Probleme mur de droite\n"), -1);
        line++;
    }
    return (0);
}