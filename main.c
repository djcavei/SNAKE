#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define SNAKELEN snake->length
#define HEAD snake->position[0]
#define X1 (food_coordinate.r * COLUMN + HEAD.c)
#define X1_RIGHT (food_coordinate.r * COLUMN + ((HEAD.c + i) % COLUMN))
#define X1_DOWN (((food_coordinate.r + i) % ROW) * COLUMN + HEAD.c)
#define X2 (HEAD.r * COLUMN + food_coordinate.c)
#define X2_RIGHT (HEAD.r * COLUMN + ((food_coordinate.c + i) % COLUMN))
#define X2_DOWN (((HEAD.r + i) % ROW) * COLUMN + food_coordinate.c)
#define HEAD_RIGHT (HEAD.r * COLUMN + ((HEAD.c + i) % COLUMN))
#define HEAD_DOWN (((HEAD.r + i) % ROW) * COLUMN + HEAD.c)
#define FOOD (food_coordinate.r * COLUMN + food_coordinate.c)
#define FOOD_RIGHT (food_coordinate.r * COLUMN + ((food_coordinate.c + i) % COLUMN))
#define FOOD_DOWN (((food_coordinate.r + i) % ROW) * COLUMN + food_coordinate.c)

#define FOOD_ROW food_coordinate.r
#define FOOD_COLUMN food_coordinate.c
#define HEAD_ROW HEAD.r
#define HEAD_COLUMN HEAD.c
#define X1_ROW food_coordinate.r
#define X1_COLUMN HEAD.c
#define X2_ROW HEAD.r
#define X2_COLUMN food_coordinate.c

typedef struct position { /*memorizza 3 interi: coordinate dei pezzi dello snake e la direzione in cui sta andando*/
    int r;
    int c;
    int direction;
} position_t;

typedef struct body { /*il corpo dello snake, tiene informazioni sulla sua lunghezza e ogni pezzo punta a position_t per le coordinate e direzione*/
    position_t *position;
    int length;
} body_t;

int DIRECTION; /*cambia a seconda della pressione di wasd memorizzando un intero (1 2 3 4 a seconda della direzione)*/
int ROW; /*All'avvio del gioco chiede quante righe e colonne lo vuoi grande*/
int COLUMN;
const RIGHT = 1;
const DOWN = 2;
const LEFT = 3;
const UP = 4;
int speed; /*questo valore va nella funzione sleep e diminuisce ogni mangiata*/
position_t food_coordinate; /*un intero che indica la casella del cibo, inizalmente a 20 e poi random con % area*/
int score; /*punteggio*/
int esc = 0; /*condizione stupida, bastava mettere while 1*/
int max_score = 0; /*max score, memorizzato sul txt*/

void snake_init(body_t *snake) { /*inizializza lo snake con 3 pezzi (1 head e 2 tail) di lunghezza 3 e direzione right*/
    SNAKELEN = 3;
    snake->position = (position_t*)malloc(SNAKELEN * sizeof(position_t));
    DIRECTION = LEFT;
    /*getchar();*/
    HEAD.r = (rand() % ROW);
    HEAD.c = (rand() % COLUMN);
    HEAD.direction = DIRECTION+4;
    snake->position[1].r = HEAD.r;
    snake->position[1].c = (HEAD.c + 1) % COLUMN;
    snake->position[1].direction = DIRECTION;
    snake->position[2].r = HEAD.r;
    snake->position[2].c = (HEAD.c + 2) % COLUMN;
    snake->position[2].direction = DIRECTION;
}

void field_p(const *field, int r, int c) { /*una funzione semplicissima, vede l'intero che popola il punto nella matrice bidimensionale e printa il simbolo corrispondente*/
if (field[r * COLUMN + c] == 1 || field[r * COLUMN + c] == 3) {
printf("*");
} else if (field[r * COLUMN + c] == 2 || field[r * COLUMN + c] == 4) {
printf("+");
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

void snake_to_field(int *field, body_t *snake) { /*inizializza a zero tutta la matrice bidimensionale e poi setta a 10 la cella del food, a DIRECTION+4 per la head e con un ciclo for lungo come il corpo restante setta la cella di field del valore della direzione che ha ogni pezzo*/
    int i, r, c;
    for (r = 0; r < ROW; r++) {
        for (c = 0; c < COLUMN; c++) {
            field[r * COLUMN + c] = 0; /*tutta la matrice a 0*/
        }
    }
    field[food_coordinate.r * COLUMN + food_coordinate.c] = 10; /*il cibo che è random settato a 10*/
    field[HEAD.r * COLUMN + HEAD.c] = DIRECTION + 4;
    for (i = 1; i < SNAKELEN; i++) {
        field[snake->position[i].r * COLUMN + snake->position[i].c] = snake->position[i].direction; /*ogni pezzo del corpo setta la matrice del valore corrispondente alla direzione che verrà ogni mossa ereditato*/
    }
}

void move(int *field, body_t *snake) {
    int r, c, i;
    snake_to_field(field, snake); /*assegna valori alla matrice sulla base della direzione del pezzo del corpo*/
    printf("SCORE: %d     MAX_SCORE: %d\n ", score, max_score);
    for (i = 0; i < COLUMN; i++) {
        printf("_");
    }
    for (r = 0; r < ROW; r++) {
        printf("\n");
        printf("|");
        for (c = 0; c < COLUMN; c++) {
            field_p(field, r, c); /*printata effettiva*/
        }
        printf("|");
    }
    printf("\n ");
    for (i = 0; i < COLUMN; i++) {
        printf("-");
    }
}

void update_head(body_t *snake, int dir) { /*dopo aver scalato i valori del corpo[1] assegna il nuovo valore alla testa*/
    if (dir == RIGHT) {
        HEAD.c += 1; /*se la direzione è right ovviamente la testa in questa mossa andrà nella colonna +1 e cosi via*/
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

void food_new(const *field) { /*nel main si controlla se coordinate testa e food sono uguali e si calcola random il nuovo cibo verificando che non ci sia un serpente*/
food_coordinate.r = rand() % ROW;
food_coordinate.c = rand() % COLUMN;
while(field[food_coordinate.r * COLUMN + food_coordinate.c] != 0) {
food_coordinate.r = rand() % ROW;
food_coordinate.c = rand() % COLUMN;
}
}

int food_check(body_t *snake, int *field) { /*verifica che testa e cibo siano nella stessa coordinata e chiama una funzione per randomizzare la posizione del nuovo cibo*/
    if (HEAD.r * COLUMN + HEAD.c == food_coordinate.r * COLUMN + food_coordinate.c) {
        food_new(field);
        return 1;
    }
    else return 0;
}

void increase_snake(body_t *snake) { /*se mangi realloca la memoria grande len+1*/
    SNAKELEN += 1;
    snake->position = realloc(snake->position, SNAKELEN*sizeof(position_t)); /*assegna al nuovo culo il valore del vecchio culo*/
    snake->position[SNAKELEN - 1].r = snake->position[SNAKELEN - 2].r;
    snake->position[SNAKELEN - 1].c = snake->position[SNAKELEN - 2].c;
    snake->position[SNAKELEN - 1].direction = snake->position[SNAKELEN - 2].direction;
}

void updating(body_t *snake) { /*dopo ogni move updata la composizione scalando direzioni e coordinate dalla coda alla posizione 1 poi in una funzione a parte corpo[0] viene updatato e la direzione corpo[1] eredita la testa-4*/
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

int lost(position_t head, position_t *tail, int len) { /*vede se la testa ha le stesse coordinate del corpo ricorsivamente*/
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



/* INIZIO AUTOPLAY*/





int src_down(const *field, int r, int c, int X) {
    int i, occ = 0;
    for (i = 1; i < ROW; i++) {
        if (field[(((r + i) % ROW) * COLUMN + c)] == 0) {
            occ++;
            if ((((r + i) % ROW) * COLUMN + c) == X) {
                return occ;
            }
        } else if (field[(((r + i) % ROW) * COLUMN + c)] >= 5) {
            occ++;
            return occ;
        } else return 0;
    }
    return 0;
}

int src_right(const *field, int r, int c, int X) {
    int i, occ = 0;
    for (i = 1; i < COLUMN; i++) {
        if (field[r * COLUMN + ((c + i) % COLUMN)] == 0) {
            occ++;
            if (r * COLUMN + ((c + i) % COLUMN) == X) {
                return occ;
            }
        } else if (field[r * COLUMN + ((c + i) % COLUMN)] >= 5) {
            occ++;
            return occ;
        } else return 0;
    }
    return 0;
}

int *steps_init(int *steppess) {
    int *a = malloc(4 * sizeof(int));
    int i;
    for (i = 0; i < 4; i++) {
        a[i] = 0;
    }
    return a;
}

int *src_minimum(int one, int two, int three, int four, int *steps, int flag) {
    int i, i_min, min = 10000;
    int combo[4];
    steps[0] = one; steps[1] = two; steps[2] = three; steps[3] = four;
    for (i = 0; i < 4; i++) {
        if (steps[i] == 0) {
            steps[i] = 10000;
        }
    }
    combo[0] = steps[0] + steps[2]; combo[1] = steps[0] + steps[3];
    combo[2] = steps[1] + steps[2]; combo[3] = steps[1] + steps[2];
    for (i = 0; i < 4; i++) {
        if (combo[i] < min) {
            min = combo[i];
            i_min = i;
        } else combo[i] = 0;
    }
    switch (i_min) {
        case 0: {
            if (flag == 1) {
                steps[0] = UP; steps[1] = one; steps[2] = LEFT; steps[3] = three;
            } else {
                steps[0] = LEFT; steps[1] = one; steps[2] = UP; steps[3] = three;
            }
            break;
        }
        case 1: {
            if (flag == 1) {
                steps[0] = UP; steps[1] = one; steps[2] = RIGHT; steps[3] = four;
            } else {
                steps[0] = LEFT; steps[1] = one; steps[2] = DOWN; steps[3] = four;
            }
            break;
        }
        case 2: {
            if (flag == 1) {
                steps[0] = DOWN; steps[1] = two; steps[2] = LEFT; steps[3] = three;
            } else {
                steps[0] = RIGHT; steps[1] = two; steps[2] = UP; steps[3] = three;
            }
            break;
        }
        case 3: {
            if (flag == 1) {
                steps[0] = DOWN; steps[1] = two; steps[2] = RIGHT; steps[3] = four;
            } else {
                steps[0] = RIGHT; steps[1] = two; steps[2] = DOWN; steps[3] = four;
            }
            break;
        }
    }
    return steps;
}

/*TODO OCCHIO OCCHIO OCCHIO, SE TROVA LA TESTA CHE FAI???*/
int *cross_src(const *field, body_t *snake) { /*formato dell'array [direction, passi, direction, passi]*/
    int *steppess_x1 = NULL, *steppess_x2 = NULL;
    int F_R, F_D, H_R, H_D, X1_D, X1_R, X2_D, X2_R;
    if (field[X1] == 0) {
        steppess_x1 = steps_init(steppess_x1);
        F_R = src_right(field, FOOD_ROW, FOOD_COLUMN, X1);
        X1_R = src_right(field, X1_ROW, X1_COLUMN, X1);
        H_D = src_down(field, HEAD_ROW, HEAD_COLUMN, X1);
        X1_D = src_down(field, X1_ROW, X1_COLUMN, X1);
        if ((X1_D || H_D) && (X1_R || F_R)) {
            steppess_x1 = src_minimum(X1_D, H_D, F_R, X1_R, steppess_x1, 1);
        } else free(steppess_x1);
    }
    if (field[X2] == 0) {
        steppess_x2 = steps_init(steppess_x2);
        H_R = src_right(field, HEAD_ROW, HEAD_COLUMN, X2);
        F_D = src_down(field, FOOD_ROW, FOOD_COLUMN, X2);
        X2_D = src_down(field, X2_ROW, X2_COLUMN, X2);
        X2_R = src_right(field, X2_ROW, X2_COLUMN, X2);
        if ((X2_R || H_R) && (X2_D || F_D)) {
            steppess_x2 = src_minimum(X2_R, H_R, F_D, X2_D, steppess_x2, 2);
        }
        else free(steppess_x2);
    }
    else {
        return NULL;
    }
    if (steppess_x1 && steppess_x2) {
        if (steppess_x1[1] + steppess_x1[3] < steppess_x2[1] + steppess_x2[3]) {
            return steppess_x1;
        } else return steppess_x2;
    }
    if (!steppess_x1) {
        return steppess_x2;
    } else return steppess_x1;
}

int *autoplay(int *field, body_t *snake) {
    int *buba;
    buba = cross_src(field, snake);
    return buba;
}

int main() {
    FILE *punteggio;
    setbuf(stdout, 0);
    printf("Digita grandezza campo, formato: 'righe spazio colonne'. (Max suggerito 30x60 poi vedi tu se vuoi avere una crisi epilettica): ");
    scanf("%d %d", &ROW, &COLUMN); /*scegli la grandezza del campo*/
    while (!esc) {
        body_t *snake = malloc(sizeof(body_t));
        char quit = 'x';
        int field[ROW][COLUMN];
        float multiplier = 1.0;
        char control = 'x';
        int game_mode;
        game_mode = 0;
        snake_init(snake);
        food_coordinate.r = (rand() % ROW);
        food_coordinate.c = (rand() % COLUMN);
        score = 0;
        speed = 250;
        printf("Game mode: 1 autoplay, 2 humanplay");
        scanf("%d", &game_mode);
        punteggio = fopen("max_score.txt", "r+"); /*se c'è apre il file con max score*/ /*TODO RISOLVI PROBLEMI REPLAY SE SCHIACCI TANTI TASTI solito scanf di merda*/
        if (punteggio) {
            fscanf(punteggio, "%d", &max_score);
        }
        fclose(punteggio);
        while (game_mode == 2 && lost(HEAD, &snake->position[1], SNAKELEN - 1)) {
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
            if (food_check(snake, *field)) {
                if (speed > 15) {
                    speed -= 15;
                } else if (speed==10) speed -= 3; /*TODO CALCOLO CHE APPROSSIMI A 0 MA MAI CI ARRIVI*/
                increase_snake(snake);
                score += 10 * multiplier;
                multiplier += 0.15;
            }
        }
        while (game_mode == 1 /*(autoplay)*/) { /*AUTOPLAY*/
            int *moves;
            int i;
            system("cls");
            move(*field, snake);
            moves = autoplay(*field, snake);
            if (moves) {
                DIRECTION = moves[0];
                for (i = 0; i < moves[1]; i++) {
                    system("cls");
                    updating(snake);
                    move(*field, snake);
                }
                DIRECTION = moves[2];
                for (i = 0; i < moves[3]; i++) {
                    system("cls");
                    updating(snake);
                    move(*field, snake);
                }
                free(moves);
                food_check(snake, *field);
                increase_snake(snake);
                continue;
            }
            updating(snake);
            if (food_check(snake, *field)) {
                increase_snake(snake);
            }
        }
        system("cls");
        printf("YOU LOSEEEEEE!\nYOUR SCORE IS: %d\n", score);
        if (score > max_score) {
            max_score = score;
            punteggio = fopen("max_score.txt", "w+");
            fprintf(punteggio, "%d", max_score);
            fclose(punteggio);
        }
        printf("Press q to quit or any key to continue\n"); /*TODO GRAFICA E AUTOGIOCO*/
        free(snake->position);                                      /*TODO INIZIALIZZA A ZERO SOLO ALL'INIZIO POI UPGRADA E BASTA*/
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