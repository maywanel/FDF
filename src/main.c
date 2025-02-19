#include "fdf.h"

int main(int argc, char **argv) {
    t_vars vars;

    if (argc != 2) {
        write(2, "Usage: ./fdf map_file\n", 22);
        return 1;
    }
    vars.mlx = NULL;
    vars.win = NULL;
    vars.map.data = NULL;
    vars.offset_x = 800; 
    vars.offset_y = 400;
    vars.scale = 20;
    vars.angle = 0.523599;
    vars.z_scale = 5;     
    vars.cos_angle = cos(vars.angle);
    vars.sin_angle = sin(vars.angle);
    vars.projection = 0;
    if (!read_map(&vars.map, argv[1]))
    {
        write(2, "Error reading map\n", 17);
        clean_exit(&vars);
        return 1;
    }
    vars.points = malloc(sizeof(t_point*) * vars.map.height);
    for (int i = 0; i < vars.map.height; i++) {
        vars.points[i] = malloc(sizeof(t_point) * vars.map.width);
        for (int j = 0; j < vars.map.width; j++) {
            vars.points[i][j].z = vars.map.data[i][j];
        }
    }
    update_points(&vars, 's');
    srand(time(NULL));
    vars.mlx = mlx_init();
    if (!vars.mlx) {
        write(2, "Failed to initialize mlx\n", 24);
        clean_exit(&vars);
        return 1;
    }
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "FDF");
    if (!vars.win) {
        write(2, "Failed to create window\n", 23);
        clean_exit(&vars);
        return 1;
    }
    vars.img = mlx_new_image(vars.mlx, 1920, 1080);
    vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, 
                             &vars.line_length, &vars.endian);
    draw_map(&vars);
    mlx_hook(vars.win, 17, 0, close_window, &vars);
    mlx_hook(vars.win, 2, 1L<<0, handle_keypress, &vars);
    mlx_loop(vars.mlx);
    clean_exit(&vars);
    return 0;
}
