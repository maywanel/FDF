#ifndef FDF_H
#define FDF_H

#include "minilibx/mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include "src/get_next_line.h"

typedef struct s_map {
    int **data;
    int width;
    int height;
} t_map;

typedef struct s_point {
    int x, y, z;
    int transformed_x;
    int transformed_y;
} t_point;

typedef struct s_vars {
    void *mlx;
    void *win;
    t_map map;
    int offset_x;
    int offset_y;
    int scale;
    double angle_x;
    double angle_y;
    double angle_z;
    float z_scale;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    double cos_angle;
    double sin_angle;
    t_point **points;
    int projection;
} t_vars;

typedef struct s_line {
    int x0;  //start line
    int y0;
    int x1;  //end line
    int y1;
} t_line;

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
    PLUS = 65451,
    MINES = 65453
};

int get_height_color(int height);
int is_visible(int x, int y);
char **ft_split(char *str, char delimiter);
int ft_atoi(const char *str);
void update_points(t_vars *vars);
void apply_projection(t_point *p, t_vars *vars);
void rotate_z(int *x, int *y, double angle);
void rotate_y(int *x, int *z, double angle);
void rotate_x(int *y, int *z, double angle);
int read_map(t_map *map, char *filename);
int count_width(char *line);
int handle_keypress(int keysym, t_vars *vars);
void draw_map(t_vars *vars);
void draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int color);
void vertical_lines(t_vars *vars, int x, int y, int color);
void horizontal_lines(t_vars *vars, int x, int y, int color);
void pixel_put(t_vars *vars, int x, int y, int color);
int close_window(t_vars *vars);
void clean_exit(t_vars *vars);

#endif
