#include "fdf.h"


void	draw_background(t_vars *vars)
{
	int		x, y;
	int		color;
	double	percentage;
	
	y = 0;
	while (y < vars->screen_height)
	{
		percentage = (double)y / vars->screen_height;
		color = create_gradient(vars->background_color_top, vars->background_color_bottom, percentage);
		
		x = 0;
		while (x < vars->screen_width)
		{
			pixel_put(vars, x, y, color);
			x++;
		}
		y++;
	}
}

int		create_gradient(int color1, int color2, double percentage)
{
	int	r1, g1, b1;
	int	r2, g2, b2;
	int	r, g, b;
	
	r1 = (color1 >> 16) & 0xFF;
	g1 = (color1 >> 8) & 0xFF;
	b1 = color1 & 0xFF;
	
	r2 = (color2 >> 16) & 0xFF;
	g2 = (color2 >> 8) & 0xFF;
	b2 = color2 & 0xFF;
	
	r = r1 + ((r2 - r1) * percentage);
	g = g1 + ((g2 - g1) * percentage);
	b = b1 + ((b2 - b1) * percentage);
	
	return ((r << 16) | (g << 8) | b);
}