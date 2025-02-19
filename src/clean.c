#include "fdf.h"

void clean_exit(t_vars *vars)
{
    if (vars->points) {
        for (int i = 0; i < vars->map.height; i++) {
            if (vars->points[i])
                free(vars->points[i]);
        }
        free(vars->points);
        vars->points = NULL;
    }
    if (vars->map.data) {
        for (int i = 0; i < vars->map.height; i++) {
            if (vars->map.data[i])
                free(vars->map.data[i]);
        }
        free(vars->map.data);
        vars->map.data = NULL;
    }
    if (vars->img) {
        mlx_destroy_image(vars->mlx, vars->img);
        vars->img = NULL;
    }
    if (vars->win) {
        mlx_destroy_window(vars->mlx, vars->win);
        vars->win = NULL;
    }
    if (vars->mlx) {
        mlx_destroy_display(vars->mlx);
        free(vars->mlx);
        vars->mlx = NULL;
    }
}

int close_window(t_vars *vars)
{
    clean_exit(vars);
    exit(0);
    return 0;
}