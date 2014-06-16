// 
// File: Effect.cpp 
// 
// Author: Lucas Clotfelter
// 
// Implementations of Effect's derived classes
// 
// //////////////////////////////////////////////////////////////////// 

#include "Effect.h"
#include "Pokemon.h"
#include "Move.h"
#include "MajorAffliction.h"

#include <string>
#include <iostream>

using namespace std;


void AfflictBurn::onMoveEnd(const Move& move, Pokemon& owner, Pokemon& defending, bool moveHit)
{
    defending.setMajorAffliction(new Burn(defending));
}

