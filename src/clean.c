/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:52:14 by moel-mes          #+#    #+#             */
/*   Updated: 2025/02/27 10:58:39 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map_data(t_vars *vars)
{
	int	i;

	if (vars->map.data)
	{
		i = 0;
		while (i < vars->map.height)
		{
			if (vars->map.data[i])
				free(vars->map.data[i]);
			i++;
		}
		free(vars->map.data);
		vars->map.data = NULL;
	}
}

void	free_points(t_vars *vars)
{
	int	i;

	if (vars->points)
	{
		i = 0;
		while (i < vars->map.height)
		{
			if (vars->points[i])
				free(vars->points[i]);
			i++;
		}
		free(vars->points);
		vars->points = NULL;
	}
}

void	clean_exit(t_vars *vars)
{
	free_points(vars);
	free_map_data(vars);
	if (vars->img)
	{
		mlx_destroy_image(vars->mlx, vars->img);
		vars->img = NULL;
	}
	if (vars->win)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
	}
	if (vars->mlx)
	{
		(mlx_destroy_display(vars->mlx), free(vars->mlx));
		vars->mlx = NULL;
	}
}

int	close_window(t_vars *vars)
{
	clean_exit(vars);
	exit(0);
	return (0);
}
