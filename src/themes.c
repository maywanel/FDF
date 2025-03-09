#include "fdf.h"

t_theme	*create_themes(void)
{
	static t_theme themes[15];
	
	themes[0] = (t_theme){"Classic", 0x000000, 0x000000, 0x0000FF, 0xFF0000, 0xFFFFFF};
	themes[1] = (t_theme){"Neon", 0x000020, 0x000060, 0x00FF00, 0xFF00FF, 0x00FFFF};
	themes[2] = (t_theme){"Desert", 0x000000, 0x301000, 0xC19A6B, 0x654321, 0xFFD700};
	themes[3] = (t_theme){"Ice", 0x000020, 0x0000A0, 0xADD8E6, 0xFFFFFF, 0x87CEEB};
	themes[4] = (t_theme){"Heat Map", 0x000000, 0x000030, 0x0000FF, 0xFF0000, 0xFFFF00};
	themes[5] = (t_theme){"Forest", 0x000000, 0x001800, 0x228B22, 0x006400, 0x7CFC00};
	themes[6] = (t_theme){"Cyberpunk", 0x000000, 0x000818, 0x00FFFF, 0xFF00FF, 0xFFFF00};
	themes[7] = (t_theme){"Sunset", 0x000000, 0x100010, 0xFF7F00, 0xFF0000, 0xFFD700};
	themes[8] = (t_theme){"Ocean", 0x000000, 0x000030, 0x0077BE, 0x000080, 0x00FFFF};
	themes[9] = (t_theme){"Monochrome", 0x000000, 0x101010, 0x505050, 0xA0A0A0, 0xFFFFFF};
	themes[10] = (t_theme){"Retro", 0x000000, 0x001000, 0x00FF00, 0x00AA00, 0xAAFF00};
	themes[11] = (t_theme){"Volcanic", 0x000000, 0x100000, 0x800000, 0xFF0000, 0xFFAA00};
	themes[12] = (t_theme){"Aurora", 0x000000, 0x000018, 0x00FF00, 0xFF00FF, 0x00FFFF};
	themes[13] = (t_theme){"Midnight", 0x000000, 0x000030, 0x000080, 0x4B0082, 0x9400D3};
	themes[14] = (t_theme){"Cotton Candy", 0x000000, 0x200020, 0xFF80FF, 0x80FFFF, 0xFFFFFF};

	return (themes);
}

void	apply_theme(t_vars *vars, int theme_index)
{
	t_theme	*themes;
	
	themes = create_themes();
	vars->current_theme = theme_index;	
	vars->background_color_top = themes[vars->current_theme].background_top;
	vars->background_color_bottom = themes[vars->current_theme].background_bottom;
	vars->low_color = themes[vars->current_theme].low_color;
	vars->high_color = themes[vars->current_theme].high_color;
	vars->line_color = themes[vars->current_theme].line_color;
	
	draw_map(vars);
}