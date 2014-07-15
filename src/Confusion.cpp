// 
// File: Confusion.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MinorAffliction.h"
#include "Move.h"
#include "MoveFactory.h"
#include "MoveId.h"
#include "Battle.h"

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;


Confusion::Confusion(Pokemon& afflictedPokemon)
:MinorAffliction(afflictedPokemon)
,turnsLeft(rand() % 4 + 1)
{
}


bool Confusion::whenAttacks(Pokemon& defending)
{
    cout << afflictedPokemon.getNickname() << " is confused." << endl;

    if(rand() % 100 < 50)
    {
        cout << afflictedPokemon.getNickname() << " hurt itself in its confusion." << endl;

        Move* confusedMove = MoveFactory::createMove(CONFUSED_MOVE);
        Battle::doBattle(afflictedPokemon, afflictedPokemon, *confusedMove);
        delete confusedMove;
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

