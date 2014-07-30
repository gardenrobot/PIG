// 
// File: Confusion.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MinorAffliction.h"
#include "Pokemon.h"
#include "Move.h"
#include "MoveFactory.h"
#include "Battle.h"

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;


Confusion::Confusion(Pokemon& afflictedPokemon)
:MinorAffliction("Confusion", afflictedPokemon)
,turnsLeft(rand() % 4 + 1)
{
}


bool Confusion::whenAttacks(Pokemon& defending)
{
    cout << afflictedPokemon.getNickname() << " is confused." << endl;

    // determine if confusion will activate this turn
    if(rand() % 100 < 50)
    {
        cout << afflictedPokemon.getNickname() << " hurt itself in its confusion." << endl;

        // create tmp move and do a battle on afflicted pokemon
        Move* confusedMove = MoveFactory::createMove(3);
        Battle::doBattle(afflictedPokemon, afflictedPokemon, *confusedMove);
        delete confusedMove;
        return true;
    }
    else
    {
        // nothing happens
        return false;
    }
}


bool Confusion::isFinished()
{
    return false;
}

