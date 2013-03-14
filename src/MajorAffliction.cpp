// 
// File: MajorAffliction.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MajorAffliction.h"


MajorAffliction::MajorAffliction(Pokemon& afflictedPokemon)
:afflictedPokemon(afflictedPokemon)
{
}


void MajorAffliction::onRoundEnd()
{
}


bool MajorAffliction::whenAttacks()
{
    return false;
}

