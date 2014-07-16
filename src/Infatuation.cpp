// 
// File: Infatuation.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MinorAffliction.h"
#include "Move.h"
#include "Battle.h"

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;


Infatuation::Infatuation(Pokemon& afflictedPokemon, Pokemon& infatSrc)
:MinorAffliction(afflictedPokemon)
,infatSrc(infatSrc)
,infatSrcHasChanged(false)
{
}

bool Infatuation::whenAttacks(Pokemon& defending)
{
    // TODO Take gender into account
    if(&defending == &infatSrc)
    {
        if(rand() % 100 < 50)
        {
            cout << afflictedPokemon.getNickname() << " is infatuated." << endl;
            return true;
        }
        else
        {
            cout << afflictedPokemon.getNickname() << " resists infatuation." << endl;
        }
    }
    else
    {
        infatSrcHasChanged = true;
    }
}

bool Infatuation::isFinished()
{
    return infatSrcHasChanged;
}

