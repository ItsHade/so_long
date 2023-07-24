#include "../include/so_long.h"

//position x and y of the cell and front represent wich side we will check next 0 - top, 1 - right, 2 - bottom, 3 - left
typedef struct s_pos {
    int pos_x;
    int pos_y;
    int front;
} t_cell;

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
    int col;

    col = 0;
    while (col < lineLength)
    {
        if (map[0][col] != '1')
        {
            ft_putstr("Probleme mur du haut\n");
            return (-1);
        }
        col++;
    }
    col = 0;
    while (col < lineLength)
    {
        if (map[nbLines - 1][col] != '1')
        {
            ft_putstr("Probleme mur du bas\n");
            return (-1);
        }
        col++;
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

//and returns the number of collectibles
int ft_check_map_requirement(char **map, int nbLines, int lineLength)
{
    int line;
    int col;
    int countPlayerStart;
    int countExits;
    int countCollectibles;

    line = 0;
    countExits = 0;
    countPlayerStart = 0;
    countCollectibles = 0;
    while (line < nbLines)
    {
        col = 0;
        while (col < lineLength)
        {
            if (map[line][col] == 'P')
                countPlayerStart++;
            else if (map[line][col] == 'E')
                countExits++;
            else if (map[line][col] == 'C')
                countCollectibles++;
            else if (map[line][col] != '0' && map[line][col] != '1')
                return (-1);
            col++;
        }
        line ++;
    }
    if (countPlayerStart != 1 || countExits != 1 || countCollectibles < 1)
        return (-1);
    return (countCollectibles);
}

t_cell ft_get_start_pos(char **map, int nbLines, int lineLength)
{
    int line;
    int col;
    t_cell pos;

    line = 0;
    pos.pos_x = -1;
    pos.pos_y = -1;
    //means we will got to the top first
    pos.front = 0;
    while (line < nbLines)
    {
        col = 0;
        while (col < lineLength)
        {
            if (map[line][col] == 'P')
            {
                pos.pos_x = line;
                pos.pos_y = col;
                return (pos);
            }
            col++;
        }
        line++;
    }
    return (pos);    
}

char ft_check_next_cell(char **map, t_cell cell)
{
    char c;

    c = 0;
    if (cell.front == 0)
        c = map[cell.pos_x - 1][cell.pos_y];
    else if (cell.front == 1)
        c = map[cell.pos_x][cell.pos_y + 1];
    else if (cell.front == 2)
        c = map[cell.pos_x + 1][cell.pos_y];
    else if (cell.front == 3)
        c = map[cell.pos_x][cell.pos_y - 1];
    return (c);
}

// int ft_is_collectible_found(char **map, t_cell cell, int **alreadyFound)
// {
    
// }

t_cell ft_get_next_cell(t_cell cell)
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

//function/functions to verify is there is a existing path from P to E passing by all the C can only go on 0 (P and C count as 0) (not specified what happens if player goes on E before collecting every C ? does the game finish or does it do nothing ?)(obviously blocked by 1)
int ft_check_valid_path(char **map, int nbLines, int lineLength, int countCollectibles)
{
    // int i;
    // int countC;
    // int alreadyFound[countCollectibles][2];
    (void) countCollectibles;
    t_cell cell;
    t_cell lastCell;
    t_cell nextCell;

    // i = 0;
    cell = ft_get_start_pos(map, nbLines, lineLength);
    //
    printf("indexes of starting pos [%d][%d]\n", cell.pos_x, cell.pos_y);
    while (map[cell.pos_x][cell.pos_y] != 'E')
    {
        nextCell = ft_get_next_cell(cell);
        printf("pos [%d][%d]\n", cell.pos_x, cell.pos_y);
        while (ft_check_next_cell(map, cell) == '1' || (lastCell.pos_x == nextCell.pos_x && lastCell.pos_y == nextCell.pos_y))
        {
            cell.front += 1;
            nextCell = ft_get_next_cell(cell);
            printf("Turning: %d\n", cell.front);
            if (cell.front >= 4)
                return (-1);
            sleep(1);
        }

        if (ft_check_next_cell(map, cell) == '0' || ft_check_next_cell(map, cell) == 'C' || ft_check_next_cell(map, cell) == 'E' )
        {
                printf("%d\n", cell.front);
                lastCell = cell;
                cell = ft_get_next_cell(cell);
                ft_putstr("Going forward!\n");
                cell.front = 0;
        }    
    }
    return (0);
}

void ft_putmap(char **map, int nbLines, int lineLength)
{
    int line;
    int col;

    line = 0;
    while (line < nbLines)
    {
        col = 0;
        while (col < lineLength)
        {
            ft_putchar(map[line][col]);
            col++;
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
    map = malloc(sizeof(char *) * ((nbLines)));
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
    int countCollectibles;
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
    countCollectibles = ft_check_map_requirement(map, nbLines, lineLength);
    if (countCollectibles == -1)
    {
        ft_putstr("Il y a un probleme avec la carte\n");
        return (ft_freemap(map, nbLines), 5);
    }
    ft_putstr("!!!!!!!!MAP IS GUCCI!!!!!!!!\n");
    if (ft_check_valid_path(map, nbLines, lineLength, countCollectibles) == -1)
    {
        ft_putstr("Bloqueeeee!\n");
    }
    ft_putstr("FINISHED ??\n");
    ft_freemap(map, nbLines);
    return (0);
}