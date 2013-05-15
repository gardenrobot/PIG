// 
// File: MajorAffliction.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MajorAffliction.h"

#include <iostream>

using namespace std;


MajorAffliction::MajorAffliction(Pokemon& afflictedPokemon, string name,
    string shortName)
:afflictedPokemon(afflictedPokemon)
,name(name)
,shortName(shortName)
{
}


void MajorAffliction::onRoundEnd()
{
}


bool MajorAffliction::whenAttacks()
{
    return false;
}

