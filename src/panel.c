/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:51:40 by moel-mes          #+#    #+#             */
/*   Updated: 2025/03/09 15:51:40 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fill_panel_background(t_vars *vars, int panel_width)
{
	int	x;
	int	y;
	int	original_color;
	int	panel_color;

	y = 0;
	while (y < vars->screen_height)
	{
		x = 0;
		while (x < panel_width)
		{
			original_color = get_pixel_color(vars, x, y);
			panel_color = vars->background_color_bottom;
			pixel_put(vars, x, y, blend_colors(original_color, panel_color,
					0.7));
			x++;
		}
		y++;
	}
}

static void	init_info_strings(char **info_str, t_vars *vars)
{
	info_str[0] = "FDF Controls:";
	info_str[1] = "Zoom: + / -";
	info_str[2] = "Move: Arrow Keys";
	info_str[3] = "Rotate: Z X Y";
	info_str[4] = "Projection: P";
	info_str[5] = "themes: T";
	info_str[6] = "Reset View: space";
	info_str[7] = "";
	info_str[8] = "Map Info:";
	info_str[9] = ft_strjoin("Size: ", ft_itoa(vars->map.width), 0);
	info_str[9] = ft_strjoin(info_str[9], " x ", 1);
	info_str[9] = ft_strjoin(info_str[9], ft_itoa(vars->map.height), 2);
}

static void	draw_info_text(t_vars *vars, char **info_str)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		mlx_string_put(vars->mlx, vars->win, 20, 30 + (i * 25), 0xFFFFFF,
			info_str[i]);
		i++;
	}
}

void	draw_ui_panel(t_vars *vars)
{
	int		panel_width;
	char	*info_str[10];

	panel_width = 250;
	fill_panel_background(vars, panel_width);
	init_info_strings(info_str, vars);
	draw_info_text(vars, info_str);
	free(info_str[9]);
}

int	blend_colors(int color1, int color2, double alpha)
{
	t_rgb	rgb;

	rgb.r1 = (color1 >> 16) & 0xFF;
	rgb.g1 = (color1 >> 8) & 0xFF;
	rgb.b1 = color1 & 0xFF;
	rgb.r2 = (color2 >> 16) & 0xFF;
	rgb.g2 = (color2 >> 8) & 0xFF;
	rgb.b2 = color2 & 0xFF;
	rgb.r = rgb.r1 * (1 - alpha) + rgb.r2 * alpha;
	rgb.g = rgb.g1 * (1 - alpha) + rgb.g2 * alpha;
	rgb.b = rgb.b1 * (1 - alpha) + rgb.b2 * alpha;
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}
