/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:52:17 by moel-mes          #+#    #+#             */
/*   Updated: 2025/02/26 16:03:36 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < vars->screen_width && y >= 0 && y < vars->screen_height)
	{
		dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_line(t_vars *vars, t_line *l, int color)
{
	while (1)
	{
		pixel_put(vars, l->x0, l->y0, color);
		if (l->x0 == l->x1 && l->y0 == l->y1)
			break ;
		l->e2 = 2 * l->err;
		if (l->e2 >= l->dy)
		{
			l->err += l->dy;
			l->x0 += l->sx;
		}
		if (l->e2 <= l->dx)
		{
			l->err += l->dx;
			l->y0 += l->sy;
		}
	}
}

void	horizontal_lines(t_vars *vars, int x, int y)
{
	t_line	line;

	init_line(&line, &vars->points[y][x], &vars->points[y][x + 1], vars);
	draw_line(vars, &line, get_height_color(vars->map.data[y][x]));
}

void	vertical_lines(t_vars *vars, int x, int y)
{
	t_line	line;

	init_line(&line, &vars->points[y][x], &vars->points[y + 1][x], vars);
	draw_line(vars, &line, get_height_color(vars->map.data[y][x]));
}

void	draw_map(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	memset(vars->addr, 0, vars->screen_width * vars->screen_height
		* (vars->bits_per_pixel / 8));
	mlx_clear_window(vars->mlx, vars->win);
	while (y < vars->map.height)
	{
		x = 0;
		while (x < vars->map.width)
		{
			if (x < vars->map.width - 1)
				horizontal_lines(vars, x, y);
			if (y < vars->map.height - 1)
				vertical_lines(vars, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}
