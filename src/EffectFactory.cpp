// 
// File: EffectFactory.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "EffectFactory.h"
#include "Effect.h"

#include <iostream>

using namespace std;


Effect* EffectFactory::createEffect(int speciesId)
{
    switch(speciesId)
    {
        case 0:
            return NULL;
            break;
        case 1:
            return new AfflictBurn();
            break;
        default:
            return NULL;
            break;
    }
}

