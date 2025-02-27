/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:52:22 by moel-mes          #+#    #+#             */
/*   Updated: 2025/02/26 16:08:19 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_rotate_keys(int keysym, t_vars *vars)
{
	if (keysym == Y)
		vars->angle_y += 0.1;
	else if (keysym == Z)
		vars->angle_z += 0.1;
	else if (keysym == X)
		vars->angle_x += 0.1;
	else if (keysym == SPACE)
	{
		vars->angle_x = 0;
		vars->angle_y = 0;
		vars->angle_z = 0;
	}
}

static void	handle_zoom_keys(int keysym, t_vars *vars)
{
	if (keysym == PLUS)
	{
		if (vars->scale < 10000)
		{
			vars->z_scale += 0.5;
			vars->scale += 1;
		}
	}
	else if (keysym == MINES)
	{
		if (vars->z_scale > 1)
			vars->z_scale -= 0.5;
		if (vars->scale > 1)
			vars->scale = vars->scale - 1;
		else
			vars->scale = 1;
	}
	else if (keysym == Q)
	{
		if (vars->z_scale > 0)
			vars->z_scale -= 1;
	}
}

int	handle_keypress(int keysym, t_vars *vars)
{
	if (keysym == ESC)
		close_window(vars);
	else if (keysym == RIGHT)
		vars->offset_x += 10;
	else if (keysym == LEFT)
		vars->offset_x -= 10;
	else if (keysym == DOWN)
		vars->offset_y -= 10;
	else if (keysym == UP)
		vars->offset_y += 10;
	else if (keysym == P)
	{
		if (vars->projection == 1)
			vars->projection = 0;
		else
			vars->projection = 1;
	}
	handle_rotate_keys(keysym, vars);
	handle_zoom_keys(keysym, vars);
	update_points(vars);
	draw_map(vars);
	return (0);
}
