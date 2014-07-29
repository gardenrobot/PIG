// 
// File: Environment.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Environment.h"
#include "Player.h"
#include "Round.h"

#include <iostream>
#include <string>

using namespace std;


const string Environment::DATA_DIR = "data/";

Environment::Environment(Player* playerOne, Player* playerTwo)
:playerOne(playerOne)
,playerTwo(playerTwo)
,roundCount(0)
{
}


Environment::~Environment()
{
    delete playerOne;
    delete playerTwo;
}


Player* Environment::doGame()
{
    bool playerHasWon = false;

    while(not playerHasWon and (roundCount < MAX_ROUNDS or MAX_ROUNDS == -1))
    {
        Round::doRound(*this, *playerOne, *playerTwo);
        ++roundCount;

        playerHasWon = playerOne->hasLost() or playerTwo->hasLost();
    }

    Player* winner;
    if(not playerHasWon)
    {
        winner = NULL;
    }
    else if(playerTwo->hasLost())
    {
        winner = playerOne;
    }
    else // if(playerOne->hasLost())
    {
        winner = playerTwo;
    }

    return winner;
}

