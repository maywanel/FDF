/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   themes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:41:40 by moel-mes          #+#    #+#             */
/*   Updated: 2025/03/09 15:41:40 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_theme	*create_themes(void)
{
	static t_theme	ts[15];

	ts[0] = (t_theme){"Cc", 0x000000, 0x000000, 0x0000FF, 0xFF0000, 0xFFFFFF};
	ts[1] = (t_theme){"Nn", 0x000020, 0x000060, 0x00FF00, 0xFF00FF, 0x00FFFF};
	ts[2] = (t_theme){"Ds", 0x000000, 0x301000, 0xC19A6B, 0x654321, 0xFFD700};
	ts[3] = (t_theme){"Ice", 0x000020, 0x0000A0, 0xADD8E6, 0xFFFFFF, 0x87CEEB};
	ts[4] = (t_theme){"HM", 0x000000, 0x000030, 0x0000FF, 0xFF0000, 0xFFFF00};
	ts[5] = (t_theme){"Fr", 0x000000, 0x001800, 0x228B22, 0x006400, 0x7CFC00};
	ts[6] = (t_theme){"Cb", 0x000000, 0x000818, 0x00FFFF, 0xFF00FF, 0xFFFF00};
	ts[7] = (t_theme){"Ss", 0x000000, 0x100010, 0xFF7F00, 0xFF0000, 0xFFD700};
	ts[8] = (t_theme){"On", 0x000000, 0x000030, 0x0077BE, 0x000080, 0x00FFFF};
	ts[9] = (t_theme){"Mn", 0x000000, 0x101010, 0x505050, 0xA0A0A0, 0xFFFFFF};
	ts[10] = (t_theme){"Rt", 0x000000, 0x001000, 0x00FF00, 0x00AA00, 0xAAFF00};
	ts[11] = (t_theme){"Vc", 0x000000, 0x100000, 0x800000, 0xFF0000, 0xFFAA00};
	ts[12] = (t_theme){"Ar", 0x000000, 0x000018, 0x00FF00, 0xFF00FF, 0x00FFFF};
	ts[13] = (t_theme){"Md", 0x000000, 0x000030, 0x000080, 0x4B0082, 0x9400D3};
	ts[14] = (t_theme){"CC", 0x000000, 0x200020, 0xFF80FF, 0x80FFFF,
		0xFFFFFF};
	return (ts);
}

void	apply_theme(t_vars *vars, int theme_index)
{
	t_theme	*themes;
	int		current;

	themes = create_themes();
	current = vars->current_theme;
	current = theme_index;
	vars->background_color_top = themes[current].background_top;
	vars->background_color_bottom = themes[current].background_bottom;
	vars->low_color = themes[current].low_color;
	vars->high_color = themes[current].high_color;
	vars->line_color = themes[current].line_color;
	draw_map(vars);
}
