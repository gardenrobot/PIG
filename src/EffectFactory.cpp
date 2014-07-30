// 
// File: EffectFactory.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "EffectFactory.h"
#include "Effect.h"
#include "EffectId.h"
#include "Debug.h"

#include <iostream>

using namespace std;


Effect* EffectFactory::createEffect(EffectId speciesId)
{
    // this is the hard-coded map
    switch(speciesId)
    {
        case NO_EFFECT:
            return NULL;
            break;
        case AFFLICT_BURN:
            return new AfflictBurn();
            break;
        case INCREASE_SPEED_2:
            return new IncreaseSpeed2();
            break;
        case CONFUSE:
            return new Confuse();
            break;
        default:
            println_debug("Effect ID " << speciesId << " not found.");
            return NULL;
            break;
    }
}

