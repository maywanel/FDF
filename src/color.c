/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:52:08 by moel-mes          #+#    #+#             */
/*   Updated: 2025/02/26 16:35:33 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_stop_height(int index)
{
	int	heights[7];

	heights[0] = -10;
	heights[1] = -5;
	heights[2] = -2;
	heights[3] = 0;
	heights[4] = 2;
	heights[5] = 5;
	heights[6] = 10;
	return (heights[index]);
}

static int	get_stop_color(int index)
{
	int	colors[7];

	colors[0] = 0xFF0000;
	colors[1] = 0xFF8800;
	colors[2] = 0xFFFF00;
	colors[3] = 0x00FF00;
	colors[4] = 0x00FFFF;
	colors[5] = 0x00AAFF;
	colors[6] = 0x0000FF;
	return (colors[index]);
}

static int	find_index(int height)
{
	int	i;
	int	h1;
	int	h2;

	i = 0;
	while (i < 6)
	{
		h1 = get_stop_height(i);
		h2 = get_stop_height(i + 1);
		if (height >= h1 && height <= h2)
			return (i);
		i++;
	}
	if (height < get_stop_height(0))
		return (0);
	return (6);
}

static int	interpolate(int c1, int c2, float t)
{
	int	r;
	int	g;
	int	b;
	int	result;

	r = ((c1 >> 16) & 0xFF) + (int)(t * (((c2 >> 16) & 0xFF)
				- ((c1 >> 16) & 0xFF)));
	g = ((c1 >> 8) & 0xFF) + (int)(t * (((c2 >> 8) & 0xFF)
				- ((c1 >> 8) & 0xFF)));
	b = (c1 & 0xFF) + (int)(t * ((c2 & 0xFF) - (c1 & 0xFF)));
	result = (r << 16) | (g << 8) | b;
	return (result);
}

int	get_height_color(int height)
{
	int		idx;
	int		h1;
	int		h2;
	float	t;

	idx = find_index(height);
	if (idx == 6)
		return (get_stop_color(6));
	h1 = get_stop_height(idx);
	h2 = get_stop_height(idx + 1);
	t = (float)(height - h1) / (h2 - h1);
	return (interpolate(get_stop_color(idx), get_stop_color(idx + 1), t));
}

int	get_elevation_color(int z, int z_min, int z_max)
{
	double	percentage;
	int		r, g, b;

	if (z_min == z_max)
		return (0x0000FF);	
	percentage = (double)(z - z_min) / (z_max - z_min);
	if (percentage < 0.2)
	{
		r = 0;
		g = (int)(255 * (percentage / 0.2));
		b = 255;
	}
	else if (percentage < 0.4)
	{
		r = 0;
		g = 255;
		b = 255 - (int)(255 * ((percentage - 0.2) / 0.2));
	}
	else if (percentage < 0.6)
	{
		r = (int)(255 * ((percentage - 0.4) / 0.2));
		g = 255;
		b = 0;
	}
	else if (percentage < 0.8)
	{
		r = 255;
		g = 255 - (int)(255 * ((percentage - 0.6) / 0.2));
		b = 0;
	}
	else
	{
		r = 255;
		g = (int)(255 * ((percentage - 0.8) / 0.2));
		b = g;
	}	
	return ((r << 16) | (g << 8) | b);
}