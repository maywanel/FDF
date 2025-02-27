/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:16:29 by moel-mes          #+#    #+#             */
/*   Updated: 2025/02/26 16:52:28 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(int *y, int *z, double angle)
{
	double	previous_y;
	double	previous_z;

	previous_y = *y;
	previous_z = *z;
	*y = previous_y * cos(angle) - previous_z * sin(angle);
	*z = previous_y * sin(angle) + previous_z * cos(angle);
}

void	rotate_y(int *x, int *z, double angle)
{
	double	previous_x;
	double	previous_z;

	previous_x = *x;
	previous_z = *z;
	*x = previous_x * cos(angle) - previous_z * sin(angle);
	*z = previous_x * sin(angle) + previous_z * cos(angle);
}

void	rotate_z(int *x, int *y, double angle)
{
	double	previous_x;
	double	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(angle) - previous_y * sin(angle);
	*y = previous_x * sin(angle) + previous_y * cos(angle);
}

void	isometric_projection(t_point *p)
{
	double	iso_angle;
	int		prev_x;
	int		prev_y;
	int		prev_z;

	iso_angle = 0.523599;
	prev_x = p->x;
	prev_y = p->y;
	prev_z = p->z;
	p->x = (prev_x - prev_y) * cos(iso_angle);
	p->y = (prev_x + prev_y) * sin(iso_angle) - prev_z;
}

void	perspective_projection(t_point *p)
{
	double	camera_distance;
	double	depth;

	camera_distance = 1000.0;
	depth = p->z + camera_distance;
	if (depth > 0)
	{
		p->x = (p->x * camera_distance) / depth;
		p->y = (p->y * camera_distance) / depth;
	}
}
