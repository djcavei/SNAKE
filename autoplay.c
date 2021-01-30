//
// Created by marti on 30/01/2021.
//
#include "snake.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
int *src_void(const *field, int *food_coor, int *cross) {
    */
/*src a dx e sx*//*

    int i, count = 0;
    for (i = 1; food_coordinate + i < COLUMN; i++) {
        */
/*src dx*//*

        if (field[food_coordinate + i] == 0) {
            count++;
            cross = realloc(cross, count * sizeof(int));
            cross[count - 1] = food_coordinate + i;
        } else break;
    }
    for (i = 1; i < ROW; i++) {
        */
/*src sx*//*

        if (field[food_coordinate - i] == 0) {
        cross = realloc(cross, i * sizeof(int));
        cross[count] = food_coordinate + i;
        } else break;
    }
}

int *food_cross(int *field) {
    int *cross;
    int i;
    cross = (int*)malloc(sizeof(int));
    for (i = 0; i < ROW; i++) {
        cross = src_void(field, &food_coordinate, cross);
    }
    return cross;
}
*/

int src_right(const *field, body_t *snake, int *occ) {
    int i;
    for (i = 1; i <= COLUMN; i++) {
        if (field[HEAD.r * COLUMN + ((HEAD.c + i) % COLUMN)] == 10) {
            return 1;
        } else if (field[HEAD.r * COLUMN + ((HEAD.c + i) % COLUMN)] == 0) {
            continue;
        }
        else {
            break;
        }
    }
    return 0;
}

int src_down(const *field, body_t *snake, int *occ) {
    int i;
    for (i = 1; i <= ROW; i++) {
        if (field[((HEAD.r + i) % ROW) * COLUMN + HEAD.c] == 10) {
            return 1;
        } else if (field[((HEAD.r + i) % ROW) * COLUMN + HEAD.c] == 0) {
            continue;
        }
        else {
            break;
        }
    }
    return 0;
}

int src_left(const *field, body_t *snake, int *occ) {
    int i;
    for (i = 1; i <= COLUMN; i++) {
        if (field[HEAD.r * COLUMN + ((HEAD.c - i) % COLUMN)] == 10) {
            return 1;
        } else if (field[HEAD.r * COLUMN + ((HEAD.c - i) % COLUMN)] == 0) {
            continue;
        }
        else {
            break;
        }
    }
    return 0;
}

int src_up(const *field, body_t *snake, int *occ) {
    int i;
    for (i = 1; i <= ROW; i++) {
        if (field[((HEAD.r - i) % ROW) * COLUMN + HEAD.c] == 10) {
            return 1;
        } else if (field[((HEAD.r - i) % ROW) * COLUMN + HEAD.c] == 0) {
            continue;
        }
        else {
        break;
        }
    }
    return 0;
}


/*int keep_on(int *field, body_t *snake) {
    switch (DIRECTION) {
        case RIGHT: {
            if(src_right(field, snake)) {
                return RIGHT;
            }
            break;
        }
        case DOWN: {
            if(src_down(field, snake)) {
                return DOWN;
            }
            break;
        }
        case LEFT: {
            if(src_left(field, snake)) {
                return LEFT;
            }
            break;
        }
        case UP: {
            if(src_up(field, snake)) {
                return UP;
            }
            break;
        }
    }
    return 0;
}*/

int look_aside(int *field, body_t *snake) {
    switch (DIRECTION) {
        case RIGHT: {
            if ((src_down(field, snake, 0) || src_up(field, snake, 0))) {
                if (src_down(field, snake, 0) >= src_up(field, snake, 0)) {
                    return DOWN;
                } else {
                    return UP;
                }
            } return 0;
        }
        case LEFT: {
            if ((src_down(field, snake, 0) || src_up(field, snake, 0))) {
                if (src_down(field, snake, 0) >= src_up(field, snake, 0)) {
                    return DOWN;
                } else {
                    return UP;
                }
            } return 0;
        }
        case DOWN: {
            if ((src_left(field, snake, 0) || src_right(field, snake, 0))) {
                if (src_left(field, snake, 0) >= src_right(field, snake, 0)) {
                    return LEFT;
                } else {
                    return RIGHT;
                }
            } return 0;
        }
        case UP: {
            if ((src_left(field, snake, 0) || src_right(field, snake, 0))) {
                if (src_left(field, snake, 0) >= src_right(field, snake, 0)) {
                    return LEFT;
                } else {
                    return RIGHT;
                }
            }
        }
    }
    return 0;
}

/*int go_ahead(int *field, body_t *snake) {
    int right, down, left, up;
    right = src_right(field, snake, &right);
    down = src_right(field, snake, &down);
    left = src_right(field, snake, &left);
    up = src_right(field, snake, &up);
    switch (max) {

    }
}*/



int cross_scan(const *field, body_t *snake) {
    int i, j;
    if (field[food_coordinate.r * COLUMN + HEAD.c] == 0) {
        for (i = 1; i <= COLUMN; i++) {
            if (field[food_coordinate.r * COLUMN + ((food_coordinate.c + i) % COLUMN)] == 0) {
                if (field[food_coordinate.r * COLUMN + ((food_coordinate.c + i) % COLUMN)] == food_coordinate.r * COLUMN + HEAD.c) {
                    for (j = 1; j <= ROW; j++) {

                    }
                }
            }
        }
    }
}

void autoplay(int *field, body_t *snake) {
    cross_scan(field, snake);

    /*if (!look_aside(field, snake)) {
        DIRECTION = go_ahead(field, snake);
    }
    else if (look_aside(field, snake)) {
        DIRECTION = look_aside(field, snake);
    }*/
}
