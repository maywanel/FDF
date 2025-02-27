/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:52:28 by moel-mes          #+#    #+#             */
/*   Updated: 2025/02/27 10:59:42 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	allocate_map_data(t_map *map)
{
	int	i;

	map->data = (int **)malloc(sizeof(int *) * map->height);
	if (!map->data)
		return (0);
	i = 0;
	while (i < map->height)
	{
		map->data[i] = (int *)malloc(sizeof(int) * map->width);
		if (!map->data[i])
		{
			free(map->data);
			exit(1);
		}
		i++;
	}
	return (1);
}

static void	fill_map_row(t_map *map, char *line, int row)
{
	char	**split;
	int		j;
	int		k;

	split = ft_split(line, ' ');
	j = 0;
	k = 0;
	while (split[k] != NULL)
	{
		if (split[k][0] != '\0')
		{
			map->data[row][j] = ft_atoi(split[k]);
			j++;
		}
		free(split[k]);
		k++;
	}
	free(split);
}

static int	count_map_size(t_map *map, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDWR);
	if (fd < 0)
		return (0);
	map->height = 0;
	map->width = 0;
	line = get_next_line(fd);
	if (!line || !line[0])
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
	return (1);
}

static int	fill_map_data(t_map *map, char *filename)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		fill_map_row(map, line, i);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	read_map(t_map *map, char *filename)
{
	if (!count_map_size(map, filename))
		return (0);
	if (!allocate_map_data(map))
		return (0);
	if (!fill_map_data(map, filename))
		return (0);
	return (1);
}
