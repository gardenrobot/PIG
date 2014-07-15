// 
// File: PartialTrap.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MinorAffliction.h"
#include "Move.h"
#include "Battle.h"

using namespace std;


PartialTrap::PartialTrap(Pokemon& afflictedPokemon)
:MinorAffliction(afflictedPokemon)
,turnsLeft(10000)
{
}


bool PartialTrap::isFinished()
{
    return false;
}

bool PartialTrap::isTrapped()
{
    return true;
}

