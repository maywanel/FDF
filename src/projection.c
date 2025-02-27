/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:52:30 by moel-mes          #+#    #+#             */
/*   Updated: 2025/02/26 16:17:05 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_projection(t_point *p, t_vars *vars)
{
	if (vars->projection == 0)
		isometric_projection(p);
	else if (vars->projection == 1)
		perspective_projection(p);
}

static void	transform_point(t_point *point, t_vars *vars, int x, int y)
{
	point->x = x * vars->scale;
	point->y = y * vars->scale;
	point->z = vars->map.data[y][x] * vars->z_scale;
	rotate_z(&point->x, &point->y, vars->angle_z);
	rotate_y(&point->x, &point->z, vars->angle_y);
	rotate_x(&point->y, &point->z, vars->angle_x);
	apply_projection(point, vars);
	point->transformed_x = point->x;
	point->transformed_y = point->y;
}

void	update_points(t_vars *vars)
{
	int	x;
	int	y;

	if (!vars || !vars->points || vars->map.height <= 0 || vars->map.width <= 0)
		return ;
	y = 0;
	while (y < vars->map.height)
	{
		x = 0;
		while (x < vars->map.width)
		{
			transform_point(&vars->points[y][x], vars, x, y);
			x++;
		}
		y++;
	}
}
