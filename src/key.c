#include "fdf.h"

int handle_keypress(int keysym, t_vars *vars)
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
    else if (keysym == Q)
        vars->z_scale = vars->z_scale - 1;
    else if (keysym == Y)
        vars->angle_y += 0.1;
    else if (keysym == Z)
        vars->angle_z += 0.1;
    else if (keysym == X)
        vars->angle_x += 0.1;
    else if (keysym == PLUS) {
        vars->z_scale += 0.5;
        vars->scale += 1;
    }
    else if (keysym == MINES)
    {
      if (vars->z_scale)
        vars->z_scale -= 0.5;
    vars->scale = (vars->scale > 1) ? vars->scale - 1 : 1;
    }
    else if (keysym == P)
    {
    if (vars->projection == 1)
        vars->projection = 0;
    else
        vars->projection = 1;
    }
    update_points(vars);
    draw_map(vars);
    return 0;
}
