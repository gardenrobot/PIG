// 
// File: Player.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Player.h"
#include "Pokemon.h"
#include "Choice.h"
#include "MajorAffliction.h"
#include "MinorAffliction.h"
#include "Debug.h"

#include <vector>
#include <cassert>
#include <string>
#include <iostream>

using namespace std;


Player::Player(string name)
:name(name)
,surrenders(false)
{
}


Player::~Player()
{
    vector<Pokemon*>::iterator it = ownedPokemon.begin();
    for( ; it != ownedPokemon.end(); ++it)
    {
        delete *it;
    }
}


void Player::addPokemon(Pokemon* addedPokemon)
{
    if(ownedPokemon.size() < MAX_POKEMON)
    {
        ownedPokemon.push_back(addedPokemon);
    }
}


void Player::swapPokemon(int index)
{
    assert_debug(index >= 1 and index < getNumPokemon());

    Pokemon* tmp = ownedPokemon[0];
    ownedPokemon[0] = ownedPokemon[index];
    ownedPokemon[index] = tmp;
}


void Player::onRoundEnd()
{
    getPokemon(0)->onRoundEnd();
}


void Player::surrender()
{
    surrenders = true;
}


bool Player::hasLost() const
{
    if(surrenders)
    {
        return true;
    }

    // If at least one pokemon is alive, the player hasnt lost
    vector<Pokemon*>::const_iterator it(ownedPokemon.begin());
    for( ; it != ownedPokemon.end(); ++it)
    {
        if((*it)->getHp() > 0)
        {
            return false;
        }
    }

    return true;
}


bool Player::canSwap(int index)
{
    // check if any of the lead pokemon's minor afflictions prevent them from
    // leaving
    Pokemon* pokemon = getPokemon(0);
    assert_debug(pokemon != NULL);

    for(int i = 0; i < pokemon->getNumMinorAfflictions(); ++i)
    {
        if(pokemon->getMinorAffliction(i)->isTrapped())
        {
            return false;
        }
    }

    return true;
}


Pokemon* Player::getPokemon(int index)
{
    if(index >= 0 and index < MAX_POKEMON)
    {
        return ownedPokemon.at(index);
    }
    else
    {
        return NULL;
    }
}


int Player::getNumPokemon() const
{
    return ownedPokemon.size();
}


string Player::getName() const
{
    return name;
}

