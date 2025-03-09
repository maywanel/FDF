#include "fdf.h"

void	draw_ui_panel(t_vars *vars)
{
	int		panel_width;
	int		x, y, i;
	char	*info_str[10];
	
	panel_width = 250;
	for (y = 0; y < vars->screen_height; y++)
	{
		for (x = 0; x < panel_width; x++)
		{
			int original_color = get_pixel_color(vars, x, y);
			int panel_color = vars->background_color_bottom;
			pixel_put(vars, x, y, blend_colors(original_color, panel_color, 0.7));
		}
	}
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
	for (i = 0; i < 10; i++)
	{
		mlx_string_put(vars->mlx, vars->win, 20, 30 + (i * 25), 0xFFFFFF, info_str[i]);
	}
	free(info_str[9]);
}

int	blend_colors(int color1, int color2, double alpha)
{
	int r1, g1, b1;
	int r2, g2, b2;
	int r, g, b;
	
	r1 = (color1 >> 16) & 0xFF;
	g1 = (color1 >> 8) & 0xFF;
	b1 = color1 & 0xFF;
	
	r2 = (color2 >> 16) & 0xFF;
	g2 = (color2 >> 8) & 0xFF;
	b2 = color2 & 0xFF;
	
	r = r1 * (1 - alpha) + r2 * alpha;
	g = g1 * (1 - alpha) + g2 * alpha;
	b = b1 * (1 - alpha) + b2 * alpha;
	
	return ((r << 16) | (g << 8) | b);
}

int	get_pixel_color(t_vars *vars, int x, int y)
{
	int	index;
	
	if (x < 0 || y < 0 || x >= vars->screen_width || y >= vars->screen_height)
		return (0);		
	index = y * vars->line_length + x * (vars->bits_per_pixel / 8);
	return (*(unsigned int *)(vars->addr + index));
}