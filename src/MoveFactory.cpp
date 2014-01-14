// 
// File: MoveFactory.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MoveFactory.h"
#include "Move.h"

Move* MoveFactory::createMove(int moveId)
{
    switch(moveId)
    {
        case 0:
            return new Ember();
            break;
        case 1:
            return new WaterGun();
            break;
        case 2:
            return new SelfInflictedConfusionMove();
            break;
        default:
            return NULL;
            break;
    }
}

