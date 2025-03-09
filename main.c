/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:52:25 by moel-mes          #+#    #+#             */
/*   Updated: 2025/02/27 10:59:23 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	allocate_points(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	vars->points = malloc(sizeof(t_point *) * vars->map.height);
	while (i < vars->map.height)
	{
		vars->points[i] = malloc(sizeof(t_point) * vars->map.width);
		j = 0;
		while (j < vars->map.width)
		{
			vars->points[i][j].z = vars->map.data[i][j];
			j++;
		}
		i++;
	}
}

static void	calculate_scale(t_vars *vars)
{
	vars->scale = 1000 / vars->map.width;
	if (vars->scale > 20)
		vars->z_scale = 5 + (vars->scale - 20) / 2;
	else if (vars->scale < 20)
		vars->z_scale = 5 - (20 - vars->scale) / 2;
	else
		vars->z_scale = 5;
	if (vars->z_scale < 1)
		vars->z_scale = 1;
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac != 2)
	{
		write(2, "Usage: ./fdf map_file\n", 22);
		return (1);
	}
	initialize_vars(&vars);
	if (fdf_strstr(av[1]) || !read_map(&vars.map, av[1]))
	{
		write(2, "Error reading map\n", 18);
		clean_exit(&vars);
		return (1);
	}
	(calculate_scale(&vars), allocate_points(&vars), update_points(&vars));
	if (!initialize_window(&vars) || !initialize_image(&vars))
	{
		clean_exit(&vars);
		return (1);
	}
	vars.current_theme = 0;
	apply_theme(&vars, vars.current_theme);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_hook(vars.win, 2, 1L << 0, handle_keypress, &vars);
	mlx_loop(vars.mlx), clean_exit(&vars);
	return (0);
}
