// 
// File: MinorAffliction.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MinorAffliction.h"


MinorAffliction::MinorAffliction(Pokemon& afflictedPokemon)
:afflictedPokemon(afflictedPokemon)
{
}


void MinorAffliction::onRoundEnd()
{
}


bool MinorAffliction::whenAttacks()
{
    return false;
}

