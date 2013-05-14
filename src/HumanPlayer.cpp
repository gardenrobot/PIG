// 
// File: HumanPlayer.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Player.h"
#include "HumanPlayer.h"
#include "StringHelper.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;


const string HumanPlayer::MOVE_COMMAND = "move";
const string HumanPlayer::SWITCH_POKEMON_COMMAND = "switch";
const string HumanPlayer::SURRENDER_COMMAND = "surrender";
const string HumanPlayer::HELP_COMMAND = "help";

const string HumanPlayer::PLAYER = "player";
const string HumanPlayer::ENEMY = "enemy";
const string HumanPlayer::POKEMON = "pokemon";

HumanPlayer::HumanPlayer(string name)
:Player(name)
{
}


Choice HumanPlayer::getInput()
{
    bool isValid = false;
    Choice* tmpChoice;
    while(not isValid)
    {
        tmpChoice = askForInput();
        isValid = tmpChoice != NULL;
        cout << endl;

    }

    Choice choice = *tmpChoice;
    delete tmpChoice;
    return choice;
}


Choice* HumanPlayer::askForInput()
{
    cout << getName() << ", enter choice..." << endl;

    string input;
    getline(cin, input);

    vector<string> splitInput(StringHelper::split(input));

    if(splitInput.size() < 1)
    {
        return NULL;
    }
    else if(splitInput[0] == MOVE_COMMAND)
    {
        if(splitInput.size() < 2)
        {
            return NULL;
        }

        int index;
        bool success = stringstream(splitInput[1]) >> index;

        if(not success)
        {
            return NULL;
        }

        return new Choice(MOVE, index);
    }
    else if(splitInput[0] == SWITCH_POKEMON_COMMAND)
    {
        if(splitInput.size() < 2)
        {
            return NULL;
        }

        int index;
        bool success = stringstream(splitInput[1]) >> index;

        if(not success)
        {
            return NULL;
        }

        return new Choice(SWITCH_POKEMON, index);
    }
    else if(splitInput[0] == SURRENDER_COMMAND)
    {
        return new Choice(SURRENDER, 0);
    }
    else if(splitInput[0] == HELP_COMMAND)
    {
        cout << "All commands: " << endl;
        cout << "move <move index>" << endl;
        cout << "  Use your pokemon's move" << endl;
        cout << "switch <pokemon index>" << endl;
        cout << "  Switch current pokemon for another in team" << endl;
        cout << "surrender" << endl;
        cout << "  Give up" << endl;
        return NULL;
    }
    else
    {
        return NULL;
    }
}

