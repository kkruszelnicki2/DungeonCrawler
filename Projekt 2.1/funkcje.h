#ifndef FUNKCJE_H_INCLUDED
#define FUNKCJE_H_INCLUDED
#include <stdlib.h>
#include <time.h>
#include <math.h>

//generowanie pietra
void generuj(int iloscPokoi,bool czyPokoj[][5])
{
    srand(time(NULL));
    int ile=0; //ile juz pokoi stworzonych
    int x=2; //x srodkowego pokoju
    int y=2; //y srodkowego pokoju
    while(true)
    {
        switch(rand()%4+1) //losowanie kierunku
        {
        case 1:
            if(y-1>=0)
            {
                if(!czyPokoj[x][y-1]) //sprawdzanie, czy pokoj jest pusty
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
        if(ile==iloscPokoi) //sprawdzanie, czy wystarczajaca ilosc pokoi jest juz zajeta
        {
            break;
        }
    }
}

void RysujDrzwi(bool czyPokoj[][5],bool czyDrzwiRysuj[4],int x,int y)
{
    if(y-1>=0 && czyPokoj[x][y-1]==1) //drzwi gorne
    {
        czyDrzwiRysuj[0]=true;
    }
    else
    {
        czyDrzwiRysuj[0]=false;
    }
    if(x-1>=0 && czyPokoj[x-1][y]==1) //drzwi lewe
    {
        czyDrzwiRysuj[1]=true;
    }
    else
    {
        czyDrzwiRysuj[1]=false;
    }
    if(x+1<5 && czyPokoj[x+1][y]==1) //drzwi prawe
    {
        czyDrzwiRysuj[2]=true;
    }
    else
    {
        czyDrzwiRysuj[2]=false;
    }
    if(y+1<5 && czyPokoj[x][y+1]==1) //drzwi dolne
    {
        czyDrzwiRysuj[3]=true;
    }
    else
    {
        czyDrzwiRysuj[3]=false;
    }
}

#endif // FUNKCJE_H_INCLUDED
