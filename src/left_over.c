/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:18:32 by moel-mes          #+#    #+#             */
/*   Updated: 2025/03/09 16:18:32 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_elevation_color(int z, int z_min, int z_max)
{
	double	percentage;

	if (z_min == z_max)
		return (0x0000FF);
	percentage = (double)(z - z_min) / (z_max - z_min);
	if (percentage < 0.2)
		return (get_color_first_range(percentage));
	else if (percentage < 0.4)
		return (get_color_second_range(percentage));
	else if (percentage < 0.6)
		return (get_color_third_range(percentage));
	else if (percentage < 0.8)
		return (get_color_fourth_range(percentage));
	else
		return (get_color_fifth_range(percentage));
}

int	get_pixel_color(t_vars *vars, int x, int y)
{
	int	index;

	if (x < 0 || y < 0 || x >= vars->screen_width || y >= vars->screen_height)
		return (0);
	index = y * vars->line_length + x * (vars->bits_per_pixel / 8);
	return (*(unsigned int *)(vars->addr + index));
}
