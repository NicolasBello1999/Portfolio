#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include "header.h"

static char **grid; // 2D array to store the game board to later print
static int size_x, size_y;
static piece *p;

static void initGrid() {
    int i, j;

    printf("Initializing grid...\n");

    p = malloc(sizeof(*p));

    srand(time(NULL));
    size_x = (rand() % 20) + 8;
    size_y = (rand() % 20) + 8;

    p = malloc(sizeof(*p)); // initialize piece
    grid = malloc(sizeof(char) * (size_x + 1)); // initialize 2D grid
    for (i = 0; i < size_x; i++) {
        grid[i] = malloc(sizeof(char) * (size_y + 1));
        
        for (j = 0; j < size_y; j++) {
            grid[i][j] = 'o'; // fill with 'o's
        }
    }

    // create the border of the grid
    for (i = 0; i < size_x; i++) {
        grid[i][0] = '#';
        grid[i][size_y - 1] = '#';
    }

    for (i = 0; i < size_y; i++) {
        grid[0][i] = '#';
        grid[size_x - 1][i] = '#';
    }

    // initialize first piece to a random position and random direction
    p->x_coordinate = 2;
    p->y_coordinate = 2;
    p->facing_piece = '>';
    p->facing = EAST;
}

static void printGrid() {
    int i, j;

    system("cls");
    printf("\n");
    for (i = 0; i < size_x; i++) {
        for (j = 0; j < size_y; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }

    sleep(1);
}

void move() {
    if (p == NULL && grid == NULL)
        initGrid();

    grid[p->x_coordinate][p->y_coordinate] = 'o'; // clear old position of piece

    if (p->facing == NORTH) {
        p->x_coordinate--; // update row
    } else if (p->facing == SOUTH) {
        p->x_coordinate++; // update row
    } else if (p->facing == EAST) {
        p->y_coordinate++; // update column
    } else {
        p->y_coordinate--; // update column
    }

    grid[p->x_coordinate][p->y_coordinate] = p->facing_piece;
    printGrid();
}

void turnRight() {
    if (p->facing == NORTH) {
        p->facing = EAST;
        p->facing_piece = '>';
    } else if (p->facing == SOUTH) {
        p->facing = WEST;
        p->facing_piece = '<';
    } else if (p->facing == EAST) {
        p->facing = SOUTH;
        p->facing_piece = 'v';
    } else {
        p->facing = NORTH;
        p->facing_piece = '^';
    }

    grid[p->x_coordinate][p->y_coordinate] = p->facing_piece;
    printGrid();
}

void turnLeft() {
    if (p->facing == NORTH) {
        p->facing = WEST;
        p->facing_piece = '<';
    } else if (p->facing == SOUTH) {
        p->facing = EAST;
        p->facing_piece = '>';
    } else if (p->facing == EAST) {
        p->facing = NORTH;
        p->facing_piece = '^';
    } else {
        p->facing = SOUTH;
        p->facing_piece = 'v';
    }

    grid[p->x_coordinate][p->y_coordinate] = p->facing_piece;
    printGrid();
}

int checkWall() {
    if (p->facing == NORTH) {
        if (grid[p->x_coordinate - 1][p->y_coordinate] == '#')
            return 1;
    } else if (p->facing == SOUTH) {
        if (grid[p->x_coordinate + 1][p->y_coordinate] == '#')
            return 1;
    } else if (p->facing == EAST) {
        if (grid[p->x_coordinate][p->y_coordinate + 1] == '#')
            return 1;
    } else {
        if (grid[p->x_coordinate][p->y_coordinate - 1] == '#')
            return 1;
    }

    return 0;
}

