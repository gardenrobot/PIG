// 
// File: EffectFactory.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "EffectFactory.h"
#include "Effect.h"
#include "EffectId.h"

#include <iostream>

using namespace std;


Effect* EffectFactory::createEffect(EffectId speciesId)
{
    switch(speciesId)
    {
        case NO_EFFECT:
            return NULL;
            break;
        case AFFLICT_BURN:
            return new AfflictBurn();
            break;
        default:
            return NULL;
            break;
    }
}

