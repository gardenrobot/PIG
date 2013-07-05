// 
// File: Bind.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MinorAffliction.h"
#include "Move.h"
#include "Battle.h"

using namespace std;


Bind::Bind(Pokemon& afflictedPokemon)
:MinorAffliction(afflictedPokemon)
,turnsLeft(10000)
{
}


bool Bind::isFinished()
{
    return false;
}

bool Bind::isTrapped()
{
    return true;
}

