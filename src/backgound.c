/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backgound.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:22:54 by moel-mes          #+#    #+#             */
/*   Updated: 2025/03/09 16:22:54 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_background(t_vars *vars)
{
	int		color;
	double	percentage;
	int		x;
	int		y;

	y = 0;
	while (y < vars->screen_height)
	{
		percentage = (double)y / vars->screen_height;
		color = create_gradient(vars->background_color_top,
				vars->background_color_bottom, percentage);
		x = 0;
		while (x < vars->screen_width)
		{
			pixel_put(vars, x, y, color);
			x++;
		}
		y++;
	}
}

int	create_gradient(int color1, int color2, double percentage)
{
	t_rgb	rgb;

	rgb.r1 = (color1 >> 16) & 0xFF;
	rgb.g1 = (color1 >> 8) & 0xFF;
	rgb.b1 = color1 & 0xFF;
	rgb.r2 = (color2 >> 16) & 0xFF;
	rgb.g2 = (color2 >> 8) & 0xFF;
	rgb.b2 = color2 & 0xFF;
	rgb.r = rgb.r1 + ((rgb.r2 - rgb.r1) * percentage);
	rgb.g = rgb.g1 + ((rgb.g2 - rgb.g1) * percentage);
	rgb.b = rgb.b1 + ((rgb.b2 - rgb.b1) * percentage);
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}
