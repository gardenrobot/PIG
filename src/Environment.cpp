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


// Define public variables
const string Environment::DATA_DIR = "data/";
const int Environment::MAX_ROUNDS = 2;
const int Environment::MAX_POKEMON = 6;
const int Environment::MAX_MOVES = 4;
const std::string Environment::POKEMON_DATA_FILE = "Pokemon.json";
const std::string Environment::MOVE_DATA_FILE = "Move.json";
const std::string Environment::TYPE_DATA_FILE = "Type.json";

Environment::Environment(Player* playerOne, Player* playerTwo)
:playerOne(playerOne)
,playerTwo(playerTwo)
,roundCount(1)
{
}


Environment::~Environment()
{
    delete playerOne;
    delete playerTwo;
}


Player* Environment::doGame()
{
    // This is the game loop; run until finished
    bool playerHasWon = false;
    while(not playerHasWon and (roundCount <= MAX_ROUNDS or MAX_ROUNDS == -1))
    {
        cout << "Round " << roundCount << endl;

        Round::doRound(*this, *playerOne, *playerTwo);

        playerHasWon = playerOne->hasLost() or playerTwo->hasLost();
        ++roundCount;
    }

    // determine the winner and return
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

