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
    if(&defending == &infatSrc)
    {
        if(rand() % 100 < 50 and oppositeGender(afflictedPokemon.getGender(),
            defending.getGender()))
        {
            cout << afflictedPokemon.getNickname() << " is infatuated." << endl;
            return true;
        }
        else
        {
            cout << afflictedPokemon.getNickname() << " resists infatuation." << endl;
            return false;
        }
    }
    else
    {
        infatSrcHasChanged = true;
        return false;
    }
}

bool Infatuation::isFinished()
{
    return infatSrcHasChanged;
}

bool Infatuation::oppositeGender(Gender g1, Gender g2)
{
    return (g1 == MALE and g2 == FEMALE) or (g1 == FEMALE and g2 == MALE);
}

