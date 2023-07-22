#include "../include/so_long.h"

int ft_check_file_format(char *file)
{
    int i;
    int a;
    // maybe better way to do it that's still ok for the moulinette
    char neededFormat[4];

    neededFormat[0] = '.';
    neededFormat[1] = 'b';
    neededFormat[2] = 'e';
    neededFormat[3] = 'r';

    i = 0;
    a = 0;
    while (file[i] != 0)
        i++;
    i -= 4;
    if (i <= 0)
        return (-2);
    while (file[i] != 0)
    {
        if (file[i] != neededFormat[a])
            return (-1);
        i++;
        a++;
    }
    return (0);
}


//renvoie la longeur sans le /n
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

//use (buffer[0] == '\n' && prevBuffer[0] != '\n') to not count empty lines at the end of the file
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

int ft_check_for_outside_walls(char **map, int nbLines, int lineLength)
{
    int line;
    int raw;

    raw = 0;
    while (raw < lineLength)
    {
        if (map[0][raw] != '1')
        {
            ft_putstr("Probleme mur du haut\n");
            return (-1);
        }
        raw++;
    }
    raw = 0;
    while (raw < lineLength)
    {
        if (map[nbLines - 1][raw] != '1')
        {
            ft_putstr("Probleme mur du bas\n");
            return (-1);
        }
        raw++;
    }
    line = 0;
    while (line < nbLines)
    {
        if (map[line][0] != '1')
        {
            ft_putstr("Probleme mur du gauche\n");
            return (-1);
        }
        line ++;
    }
    line = 0;
    while (line < nbLines)
    {
        if (map[line][lineLength - 1] != '1')
        {
            ft_putstr("Probleme mur de droite\n");
            return (-1);
        }
        line++;
    }
    return (0);
}

int ft_check_map_requirement(char **map, int nbLines, int lineLength)
{
    int line;
    int raw;
    int countPlayerStart;
    int countExits;

    line = 0;
    countExits = 0;
    countPlayerStart = 0;
    while (line < nbLines)
    {
        raw = 0;
        while (raw < lineLength)
        {
            if (map[line][raw] == 'P')
                countPlayerStart++;
            else if (map[line][raw] == 'E')
                countExits++;
            else if (map[line][raw] != '0' && map[line][raw] != '1' && map[line][raw] != 'C')
                return (-1);
            raw++;
        }
        line ++;
    }
    if (countPlayerStart != 1 || countExits != 1)
        return (-1);
    return (0);
}

void ft_putmap(char **map, int nbLines, int lineLength)
{
    int line;
    int raw;

    line = 0;
    while (line < nbLines)
    {
        raw = 0;
        while (raw < lineLength)
        {
            ft_putchar(map[line][raw]);
            raw++;
        }
        ft_putchar('\n');
        line++;
    }
}

void ft_freemap(char **map, int nbLines)
{
    int line;
    
    line = 0;
    while (line < nbLines)
    {
        free(map[line]);
        line++;
    }
    free(map);
}

char **ft_get_map(char *file, int nbLines, int lineLength)
{
    char **map;
    int fd;
    int nbBytesRead;
    int line;
    
    nbBytesRead = 0;
    line = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        exit(EXIT_FAILURE);
    map = malloc(sizeof(char) * ((nbLines * (lineLength + 1))));
    if (!map)
        return (close(fd), NULL);
    while (line < nbLines)
    {
        map[line] = malloc(sizeof(char) * (lineLength + 1));
        if (!map[line])
            return (close(fd), NULL);
        nbBytesRead = read(fd, map[line], lineLength + 1);
        if(nbBytesRead == -1)
            exit(EXIT_FAILURE);
        map[line][lineLength] = 0;
        line++;
    }
    return (close(fd), map);
}

//test main for the functions above
int main(int argc, char **argv)
{
    int nbLines;
    int lineLength;
    char **map;

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
    printf("Lines length is: %d\n", lineLength);
    nbLines = ft_get_number_of_lines(argv[1], lineLength);
    printf("Number of lines: %d\n", nbLines);
    map = ft_get_map(argv[1], nbLines, lineLength);
    if (!map)
        return (3);
    ft_putmap(map, nbLines, lineLength);
    if (ft_check_for_outside_walls(map, nbLines, lineLength) == -1)
    {
        ft_putstr("La map n'est pas entouree de murs\n");
        return (ft_freemap(map, nbLines), 4);
    }
    if (ft_check_map_requirement(map, nbLines, lineLength) == -1)
    {
        ft_putstr("Il y a un probleme avec la carte\n");
        return (ft_freemap(map, nbLines), 5);
    }
    ft_putstr("!!!!!!!!MAP IS GUCCI!!!!!!!!\n");
    ft_freemap(map, nbLines);
    return (0);
}