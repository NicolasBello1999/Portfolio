#include <stdio.h>

typedef enum cardinalDirection {
    NORTH = 1, SOUTH = 2,
    EAST = 3, WEST = 4
} direction;

typedef struct piece {
    direction facing;
    char facing_piece;
    int x_coordinate, y_coordinate;
} piece;