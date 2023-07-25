#include "../include/so_long.h"

// position x and y of the cell and rotate represent wich side we will check next 0 - top, 1 - right, 2 - bottom, 3 - left
typedef struct s_data
{
    char **map;
    int cellP_x;
    int cellP_y;
    int collectibleCounter;
    int collectibleCount;
    int exitFound;
    int isValid;
    int validPath;
    int rotate;
} t_data;

typedef struct s_cell
{
    int x;
    int y;
    int rotate;
} t_cell;

void ft_putmap(t_data data, int nbLines, int lineLength);


//
void ft_putdata(t_data data, t_cell cell, int nbLines, int lineLength)
{
    ft_putstr("------PRINTING DATA------\n");
    ft_putstr("pos_x: ");
    ft_putnbr(cell.x);
    ft_putstr("\npos_y: ");
    ft_putnbr(cell.y);
    ft_putchar('\n');
    ft_putnbr(data.collectibleCounter);
    ft_putchar('/');
    ft_putnbr(data.collectibleCount);
    ft_putstr(" collectibles\nExit found: ");
    ft_putnbr(data.exitFound);
    ft_putstr("\nMap requirements: ");
    ft_putnbr(data.isValid);
    ft_putstr("\nMap has valid path: ");
    ft_putnbr(data.validPath);
    ft_putchar('\n');
    ft_putmap(data, nbLines, lineLength);
    ft_putstr("-------------------------\n");
}

void ft_putmap(t_data data, int nbLines, int lineLength)
{
    int line;
    int col;

    line = 0;
    while (line < nbLines)
    {
        col = 0;
        while (col < lineLength)
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

int ft_check_file_format(char *file)
{
    int i;
    int a;
    int fd;
    // maybe better way to do it that's still ok for the moulinette
    char neededFormat[4];

    neededFormat[0] = '.';
    neededFormat[1] = 'b';
    neededFormat[2] = 'e';
    neededFormat[3] = 'r';

    i = 0;
    a = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (-2);
    close(fd);
    while (file[i] != 0)
        i++;
    i -= 4;
    while (file[i] != 0)
    {
        if (file[i] != neededFormat[a])
            return (-1);
        i++;
        a++;
    }
    return (0);
}

// renvoie la longeur sans le /n
int ft_get_line_length(char *file)
{
    char buffer[1];
    int length;
    int nbBytesRead;
    int fd;

    buffer[0] = 0;
    length = 0;
    nbBytesRead = 1;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (-1);
    while (nbBytesRead != 0)
    {
        nbBytesRead = read(fd, buffer, 1);
        if (buffer[0] == '\n' || nbBytesRead == 0)
            break;
        length++;
    }
    close(fd);
    return (length);
}

// use (buffer[0] == '\n' && prevBuffer[0] != '\n') to not count empty lines at the end of the file
int ft_get_number_of_lines(char *file, int lineLength)
{
    char buffer[1];
    int nbNewLines;
    int nbBytesRead;
    int fd;
    int currentLength;

    buffer[0] = 0;
    nbNewLines = 0;
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
            if (currentLength != lineLength + 1)
            {
                ft_putstr("La map n'est pas un rectangle\n");
                close(fd);
                exit(EXIT_FAILURE);
            }
            nbNewLines++;
            currentLength = 0;
        }
    }
    return (close(fd), nbNewLines);
}

int ft_check_for_outside_walls(t_data data, int nbLines, int lineLength)
{
    int line;
    int col;

    col = 0;
    while (col < lineLength)
    {
        if (data.map[0][col] != '1')
        {
            ft_putstr("Probleme mur du haut\n");
            return (-1);
        }
        col++;
    }
    col = 0;
    while (col < lineLength)
    {
        if (data.map[nbLines - 1][col] != '1')
        {
            ft_putstr("Probleme mur du bas\n");
            return (-1);
        }
        col++;
    }
    line = 0;
    while (line < nbLines)
    {
        if (data.map[line][0] != '1')
        {
            ft_putstr("Probleme mur du gauche\n");
            return (-1);
        }
        line++;
    }
    line = 0;
    while (line < nbLines)
    {
        if (data.map[line][lineLength - 1] != '1')
        {
            ft_putstr("Probleme mur de droite\n");
            return (-1);
        }
        line++;
    }
    return (0);
}

// and returns the number of collectibles
t_data ft_check_map_requirement(t_data data, int nbLines, int lineLength)
{
    int line;
    int col;
    int countPlayerStart;
    int countExits;

    line = 0;
    countExits = 0;
    countPlayerStart = 0;
    data.collectibleCount = 0;
    data.isValid = 0;
    while (line < nbLines)
    {
        col = 0;
        while (col < lineLength)
        {
            if (data.map[line][col] == 'P')
            {
                data.cellP_x = line;
                data.cellP_y = col;
                countPlayerStart++;
            }
            else if (data.map[line][col] == 'E')
                countExits++;
            else if (data.map[line][col] == 'C')
                data.collectibleCount++;
            else if (data.map[line][col] != '0' && data.map[line][col] != '1')
                return (data);
            col++;
        }
        line++;
    }
    if (countPlayerStart != 1 || countExits != 1 || data.collectibleCount < 1)
        return (data);
    data.isValid = 1;
    return (data);
}

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

t_data ft_check_valid_path(t_data data, t_cell cell, int nbLines, int lineLength)
{
    while (cell.rotate < 4)
    {
        data.map[cell.x][cell.y] = '#';
        if (ft_is_wall(ft_check_next_cell(data, cell)) == 1 || ft_is_visited(ft_check_next_cell(data, cell)) == 1)
            cell.rotate++;
        else
        {
            if (ft_check_next_cell(data, cell) == 'E')
                data.exitFound++;
            else if (ft_check_next_cell(data, cell) == 'C')
                data.collectibleCounter++;
            data = ft_check_valid_path(data, ft_get_next_cell(cell), nbLines, lineLength);
        }
        //
        ft_putstr("x: ");
        ft_putnbr(cell.x);
        ft_putstr(" y: " );
        ft_putnbr(cell.y);
        ft_putstr(" exits: ");
        ft_putnbr(data.exitFound);
        ft_putstr(" rotate: ");
        ft_putnbr(cell.rotate);
        ft_putchar('\n');
        ft_putmap(data, nbLines, lineLength);
    }
    if (data.rotate > 3)
    {
        //
        ft_putstr("\033[1;31mstuck\033[1;0m\n");
        cell.rotate = 0;
        return (data);
    }
    return (data);
}

void ft_freemap(t_data data, int nbLines)
{
    int line;

    line = 0;
    while (line < nbLines)
    {
        free(data.map[line]);
        line++;
    }
    free(data.map);
}

t_data ft_get_map(char *file, int nbLines, int lineLength)
{
    t_data data;
    int fd;
    int nbBytesRead;
    int line;

    nbBytesRead = 0;
    line = 0;
    data.rotate = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        exit(EXIT_FAILURE);
    data.map = malloc(sizeof(char *) * ((nbLines)));
    if (!data.map)
        return (close(fd), data);
    while (line < nbLines)
    {
        data.map[line] = malloc(sizeof(char) * (lineLength + 1));
        if (!data.map[line])
            return (close(fd), data);
        nbBytesRead = read(fd, data.map[line], lineLength + 1);
        if (nbBytesRead == -1)
            exit(EXIT_FAILURE);
        data.map[line][lineLength] = 0;
        line++;
    }
    return (close(fd), data);
}

// test main for the functions above
int main(int argc, char **argv)
{
    int nbLines;
    int lineLength;
    t_data data;
    t_cell cell;

    if (argc < 2)
    {
        ft_putstr("not enough arguments!\n");
        return (0);
    }
    if (ft_check_file_format(argv[1]) == -1)
    {
        ft_putstr("Wrong format\n");
        return (1);
    }
    else if (ft_check_file_format(argv[1]) == -2)
    {
        ft_putstr("file doesn't exist\n");
        return (2);
    }
    lineLength = ft_get_line_length(argv[1]);
    ft_putstr("Lines length is: ");
    ft_putnbr(lineLength);
    ft_putchar('\n');
    nbLines = ft_get_number_of_lines(argv[1], lineLength);
    ft_putstr("Number of lines: \n");
    ft_putnbr(nbLines);
    ft_putchar('\n');
    data = ft_get_map(argv[1], nbLines, lineLength);
    if (!data.map)
        return (3);
    ft_putmap(data, nbLines, lineLength);
    if (ft_check_for_outside_walls(data, nbLines, lineLength) == -1)
    {
        ft_putstr("La map n'est pas entouree de murs\n");
        return (ft_freemap(data, nbLines), 4);
    }
    data = ft_check_map_requirement(data, nbLines, lineLength);
    if (data.isValid == 0)
    {
        ft_putstr("Il y a un probleme avec la carte\n");
        return (ft_freemap(data, nbLines), 5);
    }
    else
        ft_putstr("MAP IS GUD!!!!!!!\n");
    data.validPath = 0;
    data.collectibleCounter = 0;
    data.exitFound = 0;
    cell.x = data.cellP_x;
    cell.y = data.cellP_y;
    cell.rotate = 0;
    data = ft_check_valid_path(data, cell, nbLines, lineLength);
    if (data.exitFound == 1 && data.collectibleCounter == data.collectibleCount)
    {
        ft_putstr("\033[1;32mFound everything\n");
        data.validPath = 1;
    }
    if (data.validPath == 1)
    {
        ft_putstr("MAP IS SOLVABLE!\033[1;0m\n");
    }
    else
        ft_putstr("\033[1;31mPATHING PROBLEM!\033[1;0m\n");
    ft_putdata(data, cell, nbLines, lineLength);
    ft_putstr("FREEING\n");
    ft_freemap(data, nbLines);
    return (0);
}