#include <stdio.h>
#include "map.h"

// User interface

char desenhofantasma[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char desenhoparede[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char desenhoheroi[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char desenhovazio[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

char desenhopilula[4][7] = {
    {"      "},
    {"  .-. "},
    {"  '-' "},
    {"      "}
};

void printpart(char draw[4][7], int part){
    printf("%s", draw[part]);
}

void printmap(MAP* m){
    for (int i = 0; i < m->lines; i++){
        for(int part = 0; part < 4; part++){
            for(int j = 0; j < m->coluns; j++){
                switch (m->matriz[i][j]){
                    case GHOST:
                        printpart(desenhofantasma, part);
                        break;
                    case HERO:
                        printpart(desenhoheroi, part);
                        break;
                    case PIL:
                        printpart(desenhopilula, part);
                        break;
                    case VERTICAL_WALL:
                    case HORIZONTAL_WALL:
                        printpart(desenhoparede, part);
                        break;
                    case EMPTY:
                        printpart(desenhovazio, part);
                        break;
                
                }

            }
            printf("\n");

        }
    }
}