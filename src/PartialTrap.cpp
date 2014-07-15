// 
// File: PartialTrap.cpp 
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


PartialTrap::PartialTrap(Pokemon& afflictedPokemon)
:MinorAffliction(afflictedPokemon)
{
    turnsLeft = (rand() % 4) + 2;
}


bool PartialTrap::isFinished()
{
    return turnsLeft == 0;
}

void PartialTrap::onRoundEnd()
{
    // do damage
    int damage = (int)ceil(afflictedPokemon.getHp() / 16.0);
    afflictedPokemon.changeHp(-damage);

    // decrement counter
    turnsLeft--;
}

