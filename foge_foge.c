#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "foge_foge.h"
#include "map.h"
#include "ui.h"

// VARIAVEIS GLOBAIS//
    // MAPA = {NUMERO DE LINHAS, NUMERO DE COLUNAS, MATRIZ COM O MAPA GUARDADO} || HEROI = {POSIÇÃO DO HEROI X. Y} || DIREÇÕES = {CIMA, BAIXO, DIREITA, ESQUERDA} //
MAP m;
POSITION hero;
DIR d;
    // ~~ //


    // TEMPILULA = {STATUS DO COME-COME} || TURNO = {DURAÇÃO DO EFEITO DA PILULA}
int haspil = False;
int turn = 0;
    // ~~ //

    // VÁ PRA CIMA = {FUNÇÃO QUE RETORNA VETOR COM A POSIÇÃO ACIMA} || VÁ PARA BAIXO = {FUNÇÃOO QUE RETORNA VETOR COM A POSIÇÃO ABAIXO} || VÁ PARA ESQUERDA = {FUNÇÃO QUE RETORNA VETOR COM A POSIÇÃO A ESQUERDA} || VÁ PARA DIREITA = {FUNÇÃO QUE RETORNA VETOR COM A POSIÇÃO A DIREITA} || FUNÇÃOO QUE SETA OS VALORES PARA A STRUCT DIREÇÕES //
int * go_up(int pos[2]){
    int* copyPos = malloc(sizeof(int) * 2);
    copyPos[0] = pos[0];
    copyPos[1] = pos[1];
    copyPos[0]--;
    return copyPos;
}

int * go_down(int pos[2]){
    int* copyPos = malloc(sizeof(int) * 2);
    copyPos[0] = pos[0];
    copyPos[1] = pos[1];
    copyPos[0]++;
    return copyPos;
}

int * go_left(int pos[2]){
    int* copyPos = malloc(sizeof(int) * 2);
    copyPos[0] = pos[0];
    copyPos[1] = pos[1];
    copyPos[1]--;
    return copyPos;
}

int * go_right(int pos[2]){
    int* copyPos = malloc(sizeof(int) * 2);
    copyPos[0] = pos[0];
    copyPos[1] = pos[1];
    copyPos[1]++;
    return copyPos;
}

void set_directions(){
    d.down = go_down;
    d.left = go_left;
    d.up = go_up;
    d.right = go_right;
}
    // ~~ //
// FIM VARIAVEIS GLOBAIS //

void main(){
    readmap(&m);
    findinmap(&m, &hero, HERO);
    set_directions();

    do
    {
        printf("Pílula: %s \n", (haspil ? "SIM" : "NÃO"));
        printmap(&m);

        pac_manPlay();
        ghostsPlay();

    } while (!ended());

    freemap(&m);
}

void pac_manPlay(){
    char comand;
    scanf(" %c", &comand);

    //A LINHA A SEGUIR USA DE CONCEITOS DE PROGRAMAÇÃO SEM RAMO PARA TRANSFORMAR LETRAS MAIUSCULAS EM MINUSCULAS //
    comand += (comand < 'a') * 32;

    int toDirection = take_direction(comand);
    move(toDirection);
}

int take_direction(char comand){
    char keys[4] = {LEFT, UP, DOWN, RIGHT};
    int theDirection = 0;

    for (int i = 0; i < 4; i++){
        theDirection += (keys[i] == comand) * i;
    }

    return theDirection;
}

void move(int theDirection){    
    int* nextPosition;
    int hero_xy[2] = {hero.x, hero.y};
    int* options[4] = {d.left(hero_xy), d.up(hero_xy), d.down(hero_xy), d.right(hero_xy)};

    nextPosition = options[theDirection];

    if(game_rule(nextPosition, HERO)){
        free(nextPosition);
        return;
    }

    pil_rule(nextPosition);    

    walkinmap(&m, hero.x, hero.y, nextPosition[0], nextPosition[1]);

    hero.x = nextPosition[0];
    hero.y = nextPosition[1];

    free(nextPosition);
    
}

int game_rule(int* VerifyPosition, char HG){
    return !canwalk(&m, HG, VerifyPosition) || 
            ((HG == HERO && itscharacter(&m, GHOST, VerifyPosition) && haspil == False) ||
            (HG == GHOST && itscharacter(&m, HERO, VerifyPosition) && haspil == True));

}

void pil_rule(int* VerifyPosition){
    turn -= (turn > 0) * 1;
    haspil = (turn != 0) * 1;

    if(itscharacter(&m, PIL, VerifyPosition)){
        haspil = True;
        turn = 20;
    }
}

void ghostsPlay(){
    MAP copy;

    copymap(&copy, &m);

    for (int i = 0; i < copy.lines; i++){
        for (int j = 0; j < copy.coluns; j++){
            if(copy.matriz[i][j] == GHOST){
                int ghost_now[2] = {i, j};
                int *ghost_destiny;
                int found = whereghostgo(ghost_now, &ghost_destiny);

                if(found){
                    walkinmap(&m, i, j, ghost_destiny[0], ghost_destiny[1]);
                }  

                free(ghost_destiny);

            }
            
            
        }
        
    }

    freemap(&copy);
    
}

int whereghostgo(int ghost_now[2], int** ghost_destiny){
    if(ghost_now[0] > hero.x){
        ghost_destiny[0] = d.up(ghost_now);
    }else if(ghost_now[0] < hero.x){
        ghost_destiny[0] = d.down(ghost_now);
    }else if(ghost_now[1] > hero.y){
        ghost_destiny[0] = d.left(ghost_now);
    }else if (ghost_now[1] < hero.y){
        ghost_destiny[0] = d.right(ghost_now);
    }    

    if(!game_rule(ghost_destiny[0], GHOST)){
        return True;
    }

    free(ghost_destiny[0]);

    int* options[4] = {d.right(ghost_now), d.left(ghost_now), d.up(ghost_now), d.down(ghost_now)};
    
    srand(time(0));
    for (int i = 0; i < 10; i++){
        int choose = rand() % 4;

        ghost_destiny[0] = options[choose];

        if(!game_rule(ghost_destiny[0], GHOST)){
            return True;
        }

        free(ghost_destiny[0]);

    }

    return False;
    
}

int ended(){
    POSITION pos;

    int lose = !findinmap(&m, &pos, HERO);
    int win = !findinmap(&m, &pos, GHOST);

    return win || lose;
}
