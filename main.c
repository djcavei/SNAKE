#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

/*#define COLUMN 20
#define ROW 10*/
#define SNAKELEN snake->length
#define HEAD snake->position[0]

int DIRECTION;
int ROW;
int COLUMN;
const RIGHT = 1;
const DOWN = 2;
const LEFT = 3;
const UP = 4;
int speed;
int food_coordinate;
int score;
int esc = 0;

typedef struct position {
    int r;
    int c;
    int direction;
} position_t;

typedef struct body {
    position_t *position;
    int length;
} body_t;

void snake_init(body_t *snake) {
    SNAKELEN = 3;
    snake->position = (position_t*)malloc(SNAKELEN * sizeof(position_t));
    DIRECTION = RIGHT;
    HEAD.r = 5;
    HEAD.c = 5;
    HEAD.direction = DIRECTION+4;
    snake->position[1].r = 5;
    snake->position[1].c = 4;
    snake->position[1].direction = DIRECTION;
    snake->position[2].r = 5;
    snake->position[2].c = 3;
    snake->position[2].direction = DIRECTION;
}

void field_p(const *field, int r, int c) {
    if (field[r * COLUMN + c] == 1 || field[r * COLUMN + c] == 3) {
        printf("-");
    } else if (field[r * COLUMN + c] == 2 || field[r * COLUMN + c] == 4) {
        printf("|");
    } else if (field[r * COLUMN + c] == 5) {
        printf(">");
    } else if (field[r * COLUMN + c] == 6) {
        printf("v");
    } else if (field[r * COLUMN + c] == 7) {
        printf("<");
    } else if (field[r * COLUMN +c] == 8) {
        printf("^");
    } else if (field[r * COLUMN + c] == 10) {
        printf("O");
    } else printf(" ");
}

void snake_to_field(int *field, body_t *snake) {
    int i, r, c;
    for (r = 0; r < ROW; r++) {
        for (c = 0; c < COLUMN; c++) {
            field[r * COLUMN + c] = 0;
        }
    }
    field[food_coordinate] = 10;
    field[HEAD.r * COLUMN + HEAD.c] = DIRECTION + 4;
    for (i = 1; i < SNAKELEN; i++) {
        field[snake->position[i].r * COLUMN + snake->position[i].c] = snake->position[i].direction;
    }
}

void move(int *field, body_t *snake) {
    int r, c, i;
    snake_to_field(field, snake);
    printf("SCORE: %d\n ", score);
    for (i = 0; i < COLUMN; i++) {
        printf("_");
    }
    for (r = 0; r < ROW; r++) {
        printf("\n");
        printf("|");
        for (c = 0; c < COLUMN; c++) {
            field_p(field, r, c);
        }
        printf("|");
    }
    printf("\n ");
    for (i = 0; i < COLUMN; i++) {
        printf("-");
    }
}

void update_head(body_t *snake, int dir) {
    if (dir == RIGHT) {
        HEAD.c += 1;
        if (HEAD.c == COLUMN) { /*TODO FARE UN CALCOLO PIU SENSATO*/
            HEAD.c = 0;
        }
    }
    else if (dir == LEFT) {
        HEAD.c -= 1;
        if (HEAD.c < 0) {
            HEAD.c = COLUMN - 1;
        }
    }
    else if (dir == DOWN) {
        HEAD.r += 1;
        if (HEAD.r == ROW) {
            HEAD.r = 0;
        }
    }
    else if (dir == UP) {
        HEAD.r -= 1;
        if (HEAD.r < 0) {
            HEAD.r = ROW - 1;
        }
    }
    HEAD.direction = DIRECTION + 4;
}

void food_new(int *food_coor, const *field) {
    int random = rand() % (ROW*COLUMN)-1;
    while(field[random] != 0) {
        random = rand() % (ROW*COLUMN)-1;
    }
    *food_coor = random;
}

int food_check(int *food_coor, body_t *snake, int *field) {
    if (HEAD.r * COLUMN + HEAD.c == food_coordinate) {
        food_new(food_coor, field);
        return 1;
    }
    else return 0;
}

void increase_snake(body_t *snake) {
    SNAKELEN += 1;
    snake->position = realloc(snake->position, SNAKELEN*sizeof(position_t));
    snake->position[SNAKELEN - 1].r = snake->position[SNAKELEN - 2].r;
    snake->position[SNAKELEN - 1].c = snake->position[SNAKELEN - 2].c;
    snake->position[SNAKELEN - 1].direction = snake->position[SNAKELEN - 2].direction;
}

void updating(body_t *snake) {
    int i;
    for (i = SNAKELEN - 1; i > 1; i--) {
        snake->position[i].r = snake->position[i - 1].r;
        snake->position[i].c = snake->position[i - 1].c;
        snake->position[i].direction = snake->position[i - 1].direction;
    }
    snake->position[i].r = snake->position[i - 1].r;
    snake->position[i].c = snake->position[i - 1].c;
    update_head(snake, DIRECTION);
    snake->position[i].direction = snake->position[i - 1].direction - 4;
}

int lost(position_t head, position_t *tail, int len) {
    if (len == 0) {
        return 1;
    }
    else if (head.r == tail->r) {
        if (head.c == tail->c) {
            return 0;
        }
    }
    return lost(head, tail + 1, len - 1);
}

int main() {
    printf("Digita grandezza campo, formato: 'righe spazio colonne'. (Max suggerito 30x60 poi vedi tu se vuoi avere una crisi epilettica): ");
    scanf("%d %d", &ROW, &COLUMN);
    while (!esc) {
        body_t *snake = malloc(sizeof(body_t));
        char quit = 'x';
        int field[ROW][COLUMN];
        float multiplier = 1.0;
        char control = 'x';
        snake_init(snake);
        food_coordinate = 20;
        score = 0;
        speed = 250;
        while (lost(HEAD, &snake->position[1], SNAKELEN - 1)) {
            Sleep(speed); /*incluso in windows.h*/
            if (kbhit()) {
                control = getch();
                switch (control) {
                    case 'w':
                        if (DIRECTION != UP && DIRECTION != DOWN) {
                            DIRECTION = UP;
                            break;
                        }
                    case 'd':
                        if (DIRECTION != LEFT && DIRECTION != RIGHT) {
                            DIRECTION = RIGHT;
                            break;
                        }
                    case 'a':
                        if (DIRECTION != LEFT && DIRECTION != RIGHT) {
                            DIRECTION = LEFT;
                            break;
                        }
                    case 's':
                        if (DIRECTION != UP && DIRECTION != DOWN) {
                            DIRECTION = DOWN;
                            /*TODO SPOSTAMENTO IMMEDIATO SE PREMI*/
                            break;
                        }
                    default: {
                        break;
                    }
                }
            }
            system("cls");
            move(*field, snake);
            updating(snake);
            /*end_game(snake);*/
            if (food_check(&food_coordinate, snake, *field)) {
                if (speed > 15) {
                    speed -= 15;
                } else if (speed==10) speed -= 3; /*TODO CALCOLO CHE APPROSSIMI A 0 MA MAI CI ARRIVI*/
                increase_snake(snake);
                score += 10 * multiplier;
                multiplier += 0.15;
            }
        }
        system("cls");
        printf("YOU LOSEEEEEE!\nYOUR SCORE IS: %d\n", score);
        printf("Press q to quit or any key to continue\n");
        free(snake->position);
        free(snake);
        while (!kbhit()) {
            quit = getch();
            if (quit == 'q' || quit == 'Q') {
                system("cls");
                return 0;
            }
            else break;
        }
    }
}
