// 
// File: Confusion.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MinorAffliction.h"

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;


Confusion::Confusion(Pokemon& afflictedPokemon)
:MinorAffliction(afflictedPokemon)
,turnsLeft(rand() % 4 + 1)
{
}


bool Confusion::whenAttacks()
{
    cout << afflictedPokemon.getNickname() << " is confused." << endl;

    if(rand() % 100 < 50)
    {
        cout << afflictedPokemon.getNickname() << " hurt itself in its confusion." << endl;
        afflictedPokemon.setHp(-afflictedPokemon.getHp() / 2);
        return true;
    }
    else
    {
        return false;
    }
}


bool Confusion::isFinished()
{
    return false;
}

