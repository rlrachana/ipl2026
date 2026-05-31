#include <stdio.h>
#include <math.h>

const int WIDTH = 60;
const int HEIGHT = 30;

void init_buffer(char buffer[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            buffer[y][x] = ' ';
        }
    }
}

void draw_circle(char buffer[HEIGHT][WIDTH], int radius) {
    int cx = WIDTH / 2;
    int cy = HEIGHT / 2;
    float aspect_ratio = 2.5f; 

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            float dx = (x - cx) / aspect_ratio;
            float dy = y - cy;
            float distance_squared = (dx * dx) + (dy * dy);
            float radius_squared = radius * radius;

            if (fabsf(distance_squared - radius_squared) < radius * 0.8f) {
                buffer[y][x] = '*';
            }
        }
    }
}

void display_buffer(char buffer[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", buffer[y][x]);
        }
        printf("\n");
    }
}

int main() {
    char buffer[HEIGHT][WIDTH];
    int radius;

    printf("Enter circle radius (suggested 5 to 12): ");
    if (scanf("%d", &radius) != 1) {
        return 1;
    }

    if (radius >= HEIGHT / 2 || radius >= WIDTH / 4) {
        printf("Radius too large for the buffer size!\n");
        return 1;
    }

    init_buffer(buffer);
    draw_circle(buffer, radius);
    display_buffer(buffer);

    return 0;
}