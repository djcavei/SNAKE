#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define SNAKELEN snake->length
#define HEAD snake->position[0]

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
    DIRECTION = (rand() % 4);
    getchar();
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




int head_to_down(const *field, body_t *snake) {
    int j;
    for (j = 1; j < ROW; j++) {
        if (field[(((HEAD.r + 1) % ROW) * COLUMN + HEAD.c)] == 0) {
            if (field[(((HEAD.r + 1) % ROW) * COLUMN + HEAD.c)] == food_coordinate.r * COLUMN + HEAD.c) {
                return DOWN;
            }
        }
    }
}

int food_to_down(const *field, body_t *snake) {
    int j;
    for (j = 1; j < ROW; j++) {
        if (field[((food_coordinate.r + j) % ROW) * COLUMN + HEAD.c] == 0) {
        }
        else if (field[((food_coordinate.r + j) % ROW) * COLUMN + HEAD.c] >= 5) {
            return UP;
        }
        else return head_to_down(field, snake);
    }
}

int food_to_right(const *field, body_t *snake) {
    int i;
    for (i = 1; i < COLUMN; i++) {
        if (field[food_coordinate.r * COLUMN + (food_coordinate.c + i) % COLUMN] == 0) {
            if (field[food_coordinate.r * COLUMN + (food_coordinate.c + i) % COLUMN] == food_coordinate.r * COLUMN + HEAD.c) {
                return food_to_down(field, snake);
            }
        }
        else if (field[food_coordinate.r * COLUMN + (food_coordinate.c + i) % COLUMN] >= 5) {
            return LEFT;
        }
        else return 0;
    }
}

int cross_src(int *field, body_t *snake) {
    if (food_coordinate.r * COLUMN + HEAD.c == 0) {
        food_to_right(field, snake);
    }
}

int autoplay(int *field, body_t *snake) {
    cross_src(field, snake);
}











int main() {
    FILE *punteggio;
    printf("Digita grandezza campo, formato: 'righe spazio colonne'. (Max suggerito 30x60 poi vedi tu se vuoi avere una crisi epilettica): ");
    scanf("%d %d", &ROW, &COLUMN); /*scegli la grandezza del campo*/
    while (!esc) {
        body_t *snake = malloc(sizeof(body_t));
        char quit = 'x';
        int field[ROW][COLUMN];
        float multiplier = 1.0;
        char control = 'x';
        int game_mode;
        snake_init(snake);
        food_coordinate.r = (rand() % ROW);
        food_coordinate.c = (rand() % COLUMN);
        score = 0;
        speed = 250;
        printf("Game mode: 1 autoplay, 2 humanplay");
        scanf("%d", &game_mode);
        getchar();
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
        while (game_mode == 1) {
            move(*field, snake);
            autoplay(*field, snake);
            updating(snake);
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