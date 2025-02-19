#include "fdf.h"

void pixel_put(t_vars *vars, int x, int y, int color)
{
    char    *dst;

    if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
    {
        dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

void horizontal_lines(t_vars *vars, int x, int y, int color)
{
    t_point *start = &vars->points[y][x];
    t_point *end = &vars->points[y][x + 1];
    
    color = get_height_color(vars->map.data[y][x]);
    draw_line(vars, 
        start->transformed_x + vars->offset_x, 
        start->transformed_y + vars->offset_y,
        end->transformed_x + vars->offset_x, 
        end->transformed_y + vars->offset_y,
        color);
}

void vertical_lines(t_vars *vars, int x, int y, int color)
{
    t_point *start = &vars->points[y][x];
    t_point *end = &vars->points[y + 1][x];
    
    color = get_height_color(vars->map.data[y][x]);
    draw_line(vars,
        start->transformed_x + vars->offset_x, 
        start->transformed_y + vars->offset_y,
        end->transformed_x + vars->offset_x, 
        end->transformed_y + vars->offset_y,
        color);
}

void draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
        pixel_put(vars, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_map(t_vars *vars)
{
    int x;
    int y;
    int color;

    y = 0;
    x = 0;
    color = 0xFFFFFF;
    memset(vars->addr, 0, 1920 * 1080 * (vars->bits_per_pixel / 8));
    mlx_clear_window(vars->mlx, vars->win);
    while (y < vars->map.height)
    {
        x = 0;
        while (x < vars->map.width)
        {
            if (x < vars->map.width - 1)
                horizontal_lines(vars, x, y, color);
            if (y < vars->map.height - 1)
                vertical_lines(vars, x, y, color);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}
