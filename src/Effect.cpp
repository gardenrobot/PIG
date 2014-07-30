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
#include "MinorAffliction.h"
#include "Stat.h"
#include "Debug.h"


#include <string>
#include <iostream>

using namespace std;


void AfflictBurn::onMoveEnd(const Move& move, Pokemon& owner, Pokemon& defending, bool moveHit)
{
    defending.setMajorAffliction(new Burn(defending));
}

void IncreaseSpeed2::doEffect(const Move& move, Pokemon& owner, Pokemon& defending)
{
    Stat& speed = owner.getSpeed();
    println_debug("Current speed: " << speed.getModValue());
    speed -= 2;
    cout << owner.getNickname() << "'s speed rose." << endl;
    println_debug("Current speed: " << speed.getModValue());
}

void Confuse::doEffect(const Move& move, Pokemon& owner, Pokemon& defending)
{
    defending.addMinorAffliction(new Confusion(defending));
}

