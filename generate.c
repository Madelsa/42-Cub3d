#include <mlx.h>
#include <math.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define PLAYER_SIZE 20 // Size of the square player
#define LINE_LENGTH 40  // Length of the line

typedef struct s_data {
    void *mlx;
    void *win;
    int player_x, player_y; // Position of the player
    double angle; // Rotation angle in radians
} t_data;

void draw_player(t_data *data) {
    int half_size = PLAYER_SIZE / 2;
    // Draw the square player
    for (int i = data->player_x - half_size; i <= data->player_x + half_size; i++) {
        for (int j = data->player_y - half_size; j <= data->player_y + half_size; j++) {
            mlx_pixel_put(data->mlx, data->win, i, j, 0xFFFFFF); // Draw a pixel at (i, j)
        }
    }
}

void draw_line(t_data *data) {
    int x1 = data->player_x; // Starting point of the line is the player's position
    int y1 = data->player_y;
    int x2 = x1 + LINE_LENGTH * cos(data->angle); // Calculate end point using line length and angle
    int y2 = y1 + LINE_LENGTH * sin(data->angle);
    
    // Draw the line segment using Bresenham's line algorithm
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) {
        mlx_pixel_put(data->mlx, data->win, x1, y1, 0xFFFFFF); // Draw a pixel at (x1, y1)
        if (x1 == x2 && y1 == y2) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x1 += sx; }
        if (e2 < dy) { err += dx; y1 += sy; }
    }
}

void move_player(t_data *data, int direction) {
    int moveSpeed = 5; // Speed of player movement

    // Calculate movement direction based on the angle of the line
    int dx = cos(data->angle) * moveSpeed;
    int dy = sin(data->angle) * moveSpeed;

    if (direction == 0) { // Forward movement
        data->player_x += dx;
        data->player_y += dy;
    } else if (direction == 1) { // Backward movement
        data->player_x -= dx;
        data->player_y -= dy;
    }
}

void rotate_line(t_data *data, double angle) {
    data->angle += angle; // Increment the rotation angle
}

int key_hook(int keycode, t_data *data) {
    double rotationSpeed = 0.1; // Angle increment for rotation

    if (keycode == 123) // Left arrow key
        rotate_line(data, -rotationSpeed); // Rotate counterclockwise
    else if (keycode == 124) // Right arrow key
        rotate_line(data, rotationSpeed); // Rotate clockwise
    else if (keycode == 126) // Up arrow key
        move_player(data, 0); // Move player forward
    else if (keycode == 125) // Down arrow key
        move_player(data, 1); // Move player backward

    mlx_clear_window(data->mlx, data->win); // Clear the window
    draw_player(data); // Draw the player
    draw_line(data); // Draw the line

    return 0;
}

int main() {
    t_data data;

    // Initialize MiniLibX
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Line Projection");

    // Initialize player position and rotation angle
    data.player_x = WIN_WIDTH / 2; // Place player in the middle of the window horizontally
    data.player_y = WIN_HEIGHT / 2; // Place player in the middle of the window vertically
    data.angle = 0.0; // Initial rotation angle

    // Draw the initial player and line
    draw_player(&data);
    draw_line(&data);

    // Set up keyboard event handling
    mlx_hook(data.win, 2, 1L << 0, key_hook, &data);

    // Start the MiniLibX event loop
    mlx_loop(data.mlx);

    return 0;
}
