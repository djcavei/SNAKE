//
// Created by marti on 30/01/2021.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H
#define SNAKELEN snake->length
#define HEAD snake->position[0]

#endif //SNAKE_SNAKE_H

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

void autoplay(int *field, body_t *snake);