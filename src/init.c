/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:25:19 by moel-mes          #+#    #+#             */
/*   Updated: 2025/02/26 16:30:25 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_line(t_line *l, t_point *start, t_point *end, t_vars *vars)
{
	l->x0 = start->transformed_x + vars->offset_x;
	l->y0 = start->transformed_y + vars->offset_y;
	l->x1 = end->transformed_x + vars->offset_x;
	l->y1 = end->transformed_y + vars->offset_y;
	l->dx = abs(l->x1 - l->x0);
	l->dy = -abs(l->y1 - l->y0);
	l->sx = -1;
	if (l->x0 < l->x1)
		l->sx = 1;
	l->sy = -1;
	if (l->y0 < l->y1)
		l->sy = 1;
	l->err = l->dx + l->dy;
}

void	initialize_vars(t_vars *vars)
{
	memset(vars, 0, sizeof(t_vars));
	vars->projection = 0;
	vars->angle_x = 0;
	vars->angle_y = 0;
	vars->angle_z = 0;
}

int	initialize_image(t_vars *vars)
{
	vars->img = mlx_new_image(vars->mlx, vars->screen_width,
			vars->screen_height);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_length, &vars->endian);
	if (!vars->img || !vars->addr)
	{
		write(2, "Failed to create image\n", 23);
		return (0);
	}
	return (1);
}

int	initialize_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		write(2, "Failed to initialize mlx\n", 24);
		return (0);
	}
	mlx_get_screen_size(vars->mlx, &vars->screen_width, &vars->screen_height);
	vars->offset_x = vars->screen_width / 2;
	vars->offset_y = vars->screen_height / 5;
	vars->win = mlx_new_window(vars->mlx, vars->screen_width,
			vars->screen_height, "FDF");
	if (!vars->win)
	{
		write(2, "Failed to create window\n", 23);
		return (0);
	}
	return (1);
}
