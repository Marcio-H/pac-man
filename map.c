#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include <string.h>

void readmap(MAP* m){
    FILE* f;
    f = fopen("map.txt", "r");

    if (f == False){
        printf("Erro na leitura do mapa");
        exit(True);
    }

    fscanf(f, "%d %d", &m->lines, &m->coluns);

    allocatemap(m);

    for (int i = 0; i < m->lines; i++){
        fscanf(f, "%s", m->matriz[i]);
    }

    fclose(f);
}

void allocatemap(MAP* m){
    m->matriz = malloc(sizeof(char*) * m->lines);
    
    for(int i = 0; i < m->lines; i++){
        m->matriz[i] = malloc(sizeof(char) * m->coluns + 1);
    }
}

void copymap(MAP* destiny, MAP* origin){
    destiny->lines = origin->lines;
    destiny->coluns = origin->coluns;

    allocatemap(destiny);

    for (int i = 0; i < origin->lines; i++){
        strcpy(destiny->matriz[i], origin->matriz[i]);
    }
    
}

void freemap(MAP* m){
    for(int i = 0; i < m->lines; i++){
        free(m->matriz[i]);
    }

    free(m->matriz);
}

int findinmap(MAP* m, POSITION* p, char c){
    for (int i = 0; i < m->lines; i++){
        for (int j = 0; j < m->coluns; j++){
            if (m->matriz[i][j] == c){
                p->x = i;
                p->y = j;

                return True;

            }
            
        }
        
    }

    return False;
    
}

int canwalk(MAP* m, char character, int* xy){
    return
        itsvalid(m, xy) &&
        !itswall(m, xy) &&
        !itscharacter(m, character, xy) &&
        !itsghostinpil(m, character, xy[0], xy[1]);
}

int itsghostinpil(MAP* m, char character, int x, int y){
    return character == GHOST && m->matriz[x][y] == PIL;
}

int itsvalid(MAP* m, int* xy){
    return xy[0] < m->lines && xy[1] < m->coluns;
}

int itscharacter(MAP* m, char character, int* xy){
    return
        m->matriz[xy[0]][xy[1]] == character;
}

int itswall(MAP* m, int* xy){
    return 
        m->matriz[xy[0]][xy[1]] == VERTICAL_WALL ||
        m->matriz[xy[0]][xy[1]] == HORIZONTAL_WALL;
}

void walkinmap(MAP* m, int xorigin, int yorigin, int xdestiny, int ydestiny){
    char character = m->matriz[xorigin][yorigin];

    m->matriz[xdestiny][ydestiny] = character;
    m->matriz[xorigin][yorigin] = EMPTY;
}