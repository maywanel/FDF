#include "fdf.h"

void rotate_x(int *y, int *z, double angle)
{
    int previous_y = *y;
    int previous_z = *z;

    *y = previous_y * cos(angle) - previous_z * sin(angle);
    *z = previous_y * sin(angle) + previous_z * cos(angle);
}

void rotate_y(int *x, int *z, double angle)
{
    int previous_x = *x;
    int previous_z = *z;

    *x = previous_x * cos(angle) - previous_z * sin(angle);
    *z = previous_x * sin(angle) + previous_z * cos(angle);
}

void rotate_z(int *x, int *y, double angle)
{
    int previous_x = *x;
    int previous_y = *y;

    *x = previous_x * cos(angle) - previous_y * sin(angle);
    *y = previous_x * sin(angle) + previous_y * cos(angle);
}

void apply_projection(t_point *p, t_vars *vars)
{
    if (vars->projection == 0) {
        double iso_angle = 0.523599;
        int prev_x = p->x;
        int prev_y = p->y;
        int prev_z = p->z;
        
        p->x = (prev_x - prev_y) * cos(iso_angle);
        p->y = (prev_x + prev_y) * sin(iso_angle) - prev_z;
    } 
    else if (vars->projection == 1) {
        double camera_distance = 1000.0;
        double depth = p->z + camera_distance;
        
        if (depth > 0) {
            p->x = (p->x * camera_distance) / depth;
            p->y = (p->y * camera_distance) / depth;
        }
    }
}


void update_points(t_vars *vars, char rotation_axis)
{
    int x;
    int y;

    vars->offset_x = 1920 / 2 - (vars-smap.width) * vars->scale / 2;
    vars->offset_y = 1080 / 2 - (vars->map.height - 1) * vars->scale / 2;
    for (y = 0; y < vars->map.height; y++) {
        for (x = 0; x < vars->map.width; x++) {
            vars->points[y][x].x = x * vars->scale;
            vars->points[y][x].y = y * vars->scale;
            vars->points[y][x].z = vars->map.data[y][x] * vars->z_scale;

            apply_projection(&vars->points[y][x], vars);
            if (rotation_axis == 'x')
                rotate_x(&vars->points[y][x].y, &vars->points[y][x].z, vars->angle);
            else if (rotation_axis == 'y')
                rotate_y(&vars->points[y][x].x, &vars->points[y][x].z, vars->angle);
            else if (rotation_axis == 'z')
                rotate_z(&vars->points[y][x].x, &vars->points[y][x].y, vars->angle);

            vars->points[y][x].transformed_x = vars->points[y][x].x;
            vars->points[y][x].transformed_y = vars->points[y][x].y;
        }
    }
}
