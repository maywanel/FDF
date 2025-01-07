#include "../minilibx-linux/mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>

typedef struct s_map {
    int **data;      // 2D array to store height values
    int width;       // number of columns
    int height;     // number of rows
} t_map;

typedef struct s_point {
    int x;
    int y;
    int z;
    int transformed_x;
    int transformed_y;
} t_point;

typedef struct s_vars {
    void *mlx;
    void *win;
    t_map map;
    int offset_x;    // For moving the map left/right
    int offset_y;    // For moving the map up/down
    int scale;       // For zooming
    double angle;    // For rotation
    int z_scale;     // For height adjustment
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    double cos_angle;
    double sin_angle;
    t_point **points;
} t_vars;

typedef struct s_line {
    int x0;  //start line
    int y0;
    int x1;  //end line
    int y1;
} t_line;

int should_exit = 0;

enum
{
    ESC = 65307,
    E = 101,
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

void iso(int *x, int *y, int z, t_vars *vars) {
    int previous_x = *x;
    int previous_y = *y;
    
    *x = (previous_x - previous_y) * vars->cos_angle;
    *y = -z + (previous_x + previous_y) * vars->sin_angle;
}

void update_points(t_vars *vars)
{
    int x;
    int y;
    
    for (y = 0; y < vars->map.height; y++) {
        for (x = 0; x < vars->map.width; x++) {
            vars->points[y][x].x = x * vars->scale;
            vars->points[y][x].y = y * vars->scale;
            vars->points[y][x].z = vars->map.data[y][x] * vars->z_scale;
            vars->points[y][x].transformed_x = vars->points[y][x].x;
            vars->points[y][x].transformed_y = vars->points[y][x].y;
            iso(&vars->points[y][x].transformed_x, 
                &vars->points[y][x].transformed_y, 
                vars->points[y][x].z, vars);
        }
    }
}

void pixel_put(t_vars *vars, int x, int y, int color)
{
    char    *dst;

    if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
    {
        dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

// Split function implementation
char **ft_split(char *str, char delimiter) {
    int count = 1;
    for (int i = 0; str[i]; i++)
        if (str[i] == delimiter) count++;
    
    char **result = (char**)malloc(sizeof(char*) * (count + 1));
    if (!result) return NULL;
    
    int i = 0;
    char *start = str;
    char *end = str;
    int idx = 0;
    
    while (1) {
        if (*end == delimiter || *end == '\0') {
            int len = end - start;
            result[idx] = (char*)malloc(len + 1);
            if (!result[idx]) return NULL;
            strncpy(result[idx], start, len);
            result[idx][len] = '\0';
            idx++;
            if (*end == '\0') break;
            start = end + 1;
        }
        end++;
    }
    result[idx] = NULL;
    return result;
}

// Simple atoi implementation
int ft_atoi(const char *str) {
    int result = 0;
    int sign = 1;
    
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    
    if (*str == '-' || *str == '+') {
        sign = (*str == '-') ? -1 : 1;
        str++;
    }
    
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    
    return sign * result;
}

// Get next line implementation
char *get_next_line(int fd) {
    char *line = malloc(1024);
    int i = 0;
    char c;
    
    if (!line) return NULL;
    
    while (read(fd, &c, 1) > 0) {
        if (c == '\n') break;
        line[i++] = c;
    }
    
    if (i == 0) {
        free(line);
        return NULL;
    }
    
    line[i] = '\0';
    return line;
}

int is_visible(int x, int y)
{
    return (x >= 0 && x < 1920 && y >= 0 && y < 1080);
}

void draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    if ((!is_visible(x0, y0) && !is_visible(x1, y1)))
        return;
    while (!should_exit) {
        pixel_put(vars, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

int count_width(char *line) {
    int width = 0;
    int i = 0;
    
    while (line[i]) {
        while (line[i] && line[i] == ' ')
            i++;
        if (line[i])
            width++;
        while (line[i] && line[i] != ' ')
            i++;
    }
    return width;
}

int read_map(t_map *map, char *filename) {
    char *line;
    int fd;
    int i;
    int j;
    char **split;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return 0;
    
    // count rows and validate width
    map->height = 0;
    map->width = 0;
    while ((line = get_next_line(fd)) != NULL) {
        if (map->height == 0)
            map->width = count_width(line);
        else if (count_width(line) != map->width) {
            free(line);
            close(fd);
            return 0;
        }
        map->height++;
        free(line);
    }
    close(fd);

    // Allocate memory for the map
    map->data = (int **)malloc(sizeof(int *) * map->height);
    if (!map->data)
        return 0;
    for (i = 0; i < map->height; i++) {
        map->data[i] = (int *)malloc(sizeof(int) * map->width);
        if (!map->data[i])
            return 0;
    }

    // fill the map
    fd = open(filename, O_RDONLY);
    i = 0;
    while ((line = get_next_line(fd)) != NULL) {
        split = ft_split(line, ' ');
        j = 0;
        for (int k = 0; split[k] != NULL; k++) {
            if (split[k][0] != '\0')
                map->data[i][j++] = ft_atoi(split[k]);
            free(split[k]);
        }
        free(split);
        free(line);
        i++;
    }
    close(fd);
    return 1;
}

int get_height_color(int height)
{
    // Define color stops with more vibrant colors
    const int color_stops[][2] = {
        {-10, 0x0000FF},  // Pure bright blue for deep points
        {-5,  0x00AAFF},  // Bright sky blue
        {-2,  0x00FFFF},  // Cyan
        {0,   0x00FF00},  // Pure bright green for ground level
        {2,   0xFFFF00},  // Bright yellow
        {5,   0xFF8800},  // Bright orange
        {10,  0xFF0000},  // Pure bright red for peaks
    };
    int num_stops = sizeof(color_stops) / sizeof(color_stops[0]);

    // Find the appropriate color stops for interpolation
    int i;
    for (i = 0; i < num_stops - 1; i++) {
        if (height <= color_stops[i + 1][0])
            break;
    }
    if (i == num_stops - 1)
        return color_stops[num_stops - 1][1];

    // Get the two colors to interpolate between
    int color1 = color_stops[i][1];
    int color2 = color_stops[i + 1][1];
    int height1 = color_stops[i][0];
    int height2 = color_stops[i + 1][0];

    // Calculate interpolation factor (0.0 to 1.0)
    float factor = (float)(height - height1) / (height2 - height1);
    
    // Extract RGB components
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;
    
    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;

    // Interpolate RGB values
    int r = r1 + (r2 - r1) * factor;
    int g = g1 + (g2 - g1) * factor;
    int b = b1 + (b2 - b1) * factor;

    // Combine RGB components
    return (r << 16) | (g << 8) | b;
}

void horizontal_lines(t_vars *vars, int x, int y, int color) {
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

void vertical_lines(t_vars *vars, int x, int y, int color) {
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

void clean_exit(t_vars *vars) {
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

int close_window(t_vars *vars) {
    should_exit = 1;
    clean_exit(vars);
    exit(0);
    return 0;
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
    while (y < vars->map.height && !should_exit)
    {
        x = 0;
        while (x < vars->map.width && !should_exit)
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
    if (should_exit)
        close_window(vars);
}


int handle_keypress(int keysym, t_vars *vars) {
    if (keysym == ESC)
        should_exit = 1;
    else if (keysym == RIGHT)
        vars->offset_x += 10;
    else if (keysym == LEFT)
        vars->offset_x -= 10;
    else if (keysym == DOWN)
        vars->offset_y -= 10;
    else if (keysym == UP)
        vars->offset_y += 10;
    else if (keysym == Q) {
        vars->angle -= 0.1;
        vars->cos_angle = cos(vars->angle);
        vars->sin_angle = sin(vars->angle);
        update_points(vars);
    }
    else if (keysym == E) {
        vars->angle += 0.1;
        vars->cos_angle = cos(vars->angle);
        vars->sin_angle = sin(vars->angle);
        update_points(vars);
    }
    else if (keysym == Z) {
        vars->z_scale += 1;
        update_points(vars);
    }
    else if (keysym == X) {
        vars->z_scale = vars->z_scale - 1;
        update_points(vars);
    }
    else if (keysym == PLUS) {
        vars->scale += 1;
        update_points(vars);
    }
    else if (keysym == MINES) {
        vars->scale = (vars->scale > 1) ? vars->scale - 1 : 1;
        update_points(vars);
    }
    
    draw_map(vars);
    return 0;
}

int main(int argc, char **argv) {
    t_vars vars;

    if (argc != 2) {
        write(2, "Usage: ./fdf map_file\n", 22);
        return 1;
    }

    // Initialize all variables
    vars.mlx = NULL;
    vars.win = NULL;
    vars.map.data = NULL;
    vars.offset_x = 800;    // Starting position
    vars.offset_y = 400;    // Starting position
    vars.scale = 20;        // Starting scale
    vars.angle = 0.523599;  // 30 degrees in radians
    vars.z_scale = 5;       // Starting height scale
    
    vars.cos_angle = cos(vars.angle);
    vars.sin_angle = sin(vars.angle);
    // Initialize map
    if (!read_map(&vars.map, argv[1])) {
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
    update_points(&vars);
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