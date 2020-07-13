#ifndef _MAP_H_
#define _MAP_H_

#define True 1
#define False 0
#define HERO '@'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'
#define GHOST 'F'
#define PIL 'P'

struct map{
    char** matriz;
    int lines;
    int coluns;
};

typedef struct map MAP;

void allocatemap(MAP* m);
void readmap(MAP* m);
void freemap(MAP* m);

typedef int * poshero();

struct position{
    int x;
    int y;
    poshero *xy;
};

typedef struct position POSITION;

int findinmap(MAP* m, POSITION* p, char c);
int itsvalid(MAP* m, int* xy);
int itswall(MAP* m, int* xy);
int itscharacter(MAP* m, char character, int* xy);
int itsghostinpil(MAP* m, char character, int x, int y);

void walkinmap(MAP* m, int xorigin, int yorigin, int xdestiny, int ydestiny);

void copymap(MAP* destiny, MAP* origin);

int canwalk(MAP* m, char character, int* xy);

#endif