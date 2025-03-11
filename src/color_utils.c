/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:28:05 by moel-mes          #+#    #+#             */
/*   Updated: 2025/03/09 15:28:05 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color_first_range(double percentage)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = (int)(255 * (percentage / 0.2));
	b = 255;
	return ((r << 16) | (g << 8) | b);
}

int	get_color_second_range(double percentage)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 255;
	b = 255 - (int)(255 * ((percentage - 0.2) / 0.2));
	return ((r << 16) | (g << 8) | b);
}

int	get_color_third_range(double percentage)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255 * ((percentage - 0.4) / 0.2));
	g = 255;
	b = 0;
	return ((r << 16) | (g << 8) | b);
}

int	get_color_fourth_range(double percentage)
{
	int	r;
	int	g;
	int	b;

	r = 255;
	g = 255 - (int)(255 * ((percentage - 0.6) / 0.2));
	b = 0;
	return ((r << 16) | (g << 8) | b);
}

int	get_color_fifth_range(double percentage)
{
	int	r;
	int	g;
	int	b;

	r = 255;
	g = (int)(255 * ((percentage - 0.8) / 0.2));
	b = g;
	return ((r << 16) | (g << 8) | b);
}
