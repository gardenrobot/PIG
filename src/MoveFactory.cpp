// 
// File: MoveFactory.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "MoveFactory.h"
#include "Move.h"

#include <iostream>
#include <string>

using namespace std;


void MoveFactory::initialize()
{
}

Move* MoveFactory::createMove(int speciesId)
{
    switch(speciesId)
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
            cerr << "Move species " << speciesId << " not found." << endl;
            return NULL;
            break;
    }
}

