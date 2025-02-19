#include "fdf.h"

int is_visible(int x, int y)
{
    return (x >= 0 && x < 1920 && y >= 0 && y < 1080);
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

char **ft_split(char *str, char delimiter)
{
    int count = 1;
    for (int i = 0; str[i]; i++)
        if (str[i] == delimiter) count++;
    
    char **result = (char**)malloc(sizeof(char*) * (count + 1));
    if (!result)
      return NULL;
    
    char *start = str;
    char *end = str;
    int idx = 0;
    
    while (1) {
        if (*end == delimiter || *end == '\0') {
            int len = end - start;
            result[idx] = (char*)malloc(len + 1);
            if (!result[idx])
              return NULL;
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

int ft_atoi(const char *str)
{
    int result = 0;
    int sign = 1;
    
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    
    if (*str == '-' || *str == '+')
    {
        sign = (*str == '-') ? -1 : 1;
        str++;
    }
    
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    
    return sign * result;
}