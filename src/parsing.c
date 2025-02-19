#include "fdf.h"

int count_width(char *line)
{
    int width = 0;
    int i = 0;
    
    while (line[i]) {
        while (line[i] && line[i] == ' ')
            i++;
        if (line[i])
            width++;
        while (line[i] && line[i] != ' ')
            i++;
    }
    return width;
}

int read_map(t_map *map, char *filename)
{
    char *line;
    int fd;
    int i;
    int j;
    char **split;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);    
    map->height = 0;
    map->width = 0;
    line = get_next_line(fd);
    if (!line)
    {
        close(fd);
        return (0);
    }
    while (line != NULL)
    {
        if (map->height == 0)
            map->width = count_width(line);
        map->height++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    map->data = (int **)malloc(sizeof(int *) * map->height);
    if (!map->data)
        return (0);
    for (i = 0; i < map->height; i++) {
        map->data[i] = (int *)malloc(sizeof(int) * map->width);
        if (!map->data[i])
            (free(map->data), exit(1));
    }
    fd = open(filename, O_RDONLY);
    i = 0;
    while ((line = get_next_line(fd)) != NULL) {
        split = ft_split(line, ' ');
        j = 0;
        for (int k = 0; split[k] != NULL; k++) {
            if (split[k][0] != '\0')
                map->data[i][j++] = ft_atoi(split[k]);
            free(split[k]);
        }
        free(split);
        free(line);
        i++;
    }
    close(fd);
    return 1;
}