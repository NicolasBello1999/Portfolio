#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(void) {
    move();
    move();
    turnRight();
    move();
    move();
    move();
    move();
    turnLeft();

    printGrid();

    return 0;
}