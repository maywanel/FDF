/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:23:04 by moel-mes          #+#    #+#             */
/*   Updated: 2025/02/27 10:59:50 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx/mlx.h"
# include "src/get_next_line.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

typedef struct s_map
{
	int		**data;
	int		width;
	int		height;
}			t_map;

typedef struct s_line
{
	int		x0;
	int		x1;
	int		y0;
	int		y1;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
}			t_line;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		transformed_x;
	int		transformed_y;
}			t_point;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_map	map;
	int		offset_x;
	int		offset_y;
	int		scale;
	double	angle_x;
	double	angle_y;
	double	angle_z;
	float	z_scale;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	cos_angle;
	double	sin_angle;
	t_point	**points;
	int		projection;
	int		screen_width;
	int		screen_height;
}			t_vars;

enum
{
	ESC = 65307,
	P = 112,
	Y = 121,
	Q = 113,
	Z = 122,
	X = 120,
	UP = 65364,
	DOWN = 65362,
	LEFT = 65361,
	RIGHT = 65363,
	PLUS = 61,
	MINES = 45,
	SPACE = 32
};

int			get_height_color(int height);
char		**ft_split(char *s, char c);
int			ft_atoi(const char *str);
void		update_points(t_vars *vars);
void		apply_projection(t_point *p, t_vars *vars);
void		rotate_z(int *x, int *y, double angle);
void		rotate_y(int *x, int *z, double angle);
void		rotate_x(int *y, int *z, double angle);
int			read_map(t_map *map, char *filename);
int			count_width(char *line);
int			handle_keypress(int keysym, t_vars *vars);
void		draw_map(t_vars *vars);
void		draw_line(t_vars *vars, t_line *l, int color);
void		vertical_lines(t_vars *vars, int x, int y);
void		horizontal_lines(t_vars *vars, int x, int y);
void		init_line(t_line *l, t_point *start, t_point *end, t_vars *vars);
void		pixel_put(t_vars *vars, int x, int y, int color);
int			close_window(t_vars *vars);
void		clean_exit(t_vars *vars);
int			fdf_strstr(char *s);
void		isometric_projection(t_point *p);
void		perspective_projection(t_point *p);
void		initialize_vars(t_vars *vars);
int			initialize_image(t_vars *vars);
int			initialize_window(t_vars *vars);

#endif
