#ifndef _FOGE_FOGE_H_
#define _FOGE_FOGE_H_

enum key_directions {UP = 'w', DOWN = 's', RIGHT = 'd', LEFT = 'a'};

#define LOWER ' '

// Primeiras Alterações //

typedef int * direction(int pos[2]);

struct directions{
    direction *up;
    direction *down;
    direction *left;
    direction *right;
};

typedef struct directions DIR;

int * go_left(int pos[2]);
int * go_right(int pos[2]);
int * go_down(int pos[2]);
int * go_up(int pos[2]);
void set_directions();

// Fim Primeira Alterações //

int ended();
void move(int index);

void ghostsPlay();
int whereghostgo(int ghost_now[2], int** ghost_destiny);

// Seguda Alteração //

void pac_manPlay();
int take_direction(char comand);
int game_rule(int* VerifyPosition, char HG);
void pil_rule(int* VerifyPosition);

// Fim Segunda Alteração //

#endif