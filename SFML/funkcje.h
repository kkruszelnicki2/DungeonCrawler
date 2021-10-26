#ifndef FUNKCJE_H_INCLUDED
#define FUNKCJE_H_INCLUDED
#include <stdlib.h>
#include <time.h>
#include <math.h>

void generuj(int iloscPokoi,bool czyPokoj[][5])
{
    srand(time(NULL));
    int ile=0;
    int x=2;
    int y=2;
    while(true)
    {
        switch(rand()%4+1)
        {
        case 1:
            if(y-1>=0)
            {
                if(!czyPokoj[x][y-1])
                {
                    czyPokoj[x][y-1]=true;
                    ile++;
                }
                y=y-1;
            }
            break;
        case 2:
            if(x+1<=4)
            {
                if(!czyPokoj[x+1][y])
                {
                    czyPokoj[x+1][y]=true;
                    ile++;
                }
                x=x+1;
            }
            break;
        case 3:
            if(x-1>=0)
            {
                if(!czyPokoj[x-1][y])
                {
                    czyPokoj[x-1][y]=true;
                    ile++;
                }
                x=x-1;
            }
            break;
        case 4:
            if(y+1<=4)
            {
                if(!czyPokoj[x][y+1])
                {
                    czyPokoj[x][y+1]=true;
                    ile++;
                }
                y=y+1;
            }
            break;
        }
        if(ile==iloscPokoi)
        {
            break;
        }
    }
}

#endif // FUNKCJE_H_INCLUDED
