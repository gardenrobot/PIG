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
const int Environment::MAX_ROUNDS = 15;
const int Environment::MAX_POKEMON = 6;
const int Environment::MAX_MOVES = 4;
const std::string Environment::POKEMON_DATA_FILE = "Pokemon.json";
const std::string Environment::MOVE_DATA_FILE = "Move.json";
const std::string Environment::TYPE_DATA_FILE = "Type.json";

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

