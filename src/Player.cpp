// 
// File: Player.cpp 
// 
// Author: Sam Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Player.h"
#include "Pokemon.h"
#include "Choice.h"
#include "MajorAffliction.h"
#include "MinorAffliction.h"
#include "Environment.h"
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
    // delete pokemon
    for(vector<Pokemon*>::iterator it = ownedPokemon.begin();
        it != ownedPokemon.end(); ++it)
    {
        delete *it;
    }
}


void Player::addPokemon(Pokemon* addedPokemon)
{
    // add to list of pokemon if there is avaiable space
    if(ownedPokemon.size() < Environment::MAX_POKEMON)
    {
        ownedPokemon.push_back(addedPokemon);
    }
}


void Player::swapPokemon(int index)
{
    // test that args are valid
    assert_debug(canSwap(index));

    // swap pokemon
    Pokemon* tmp = ownedPokemon[0];
    ownedPokemon[0] = ownedPokemon[index];
    ownedPokemon[index] = tmp;
}


void Player::onRoundEnd(Player& enemyPlayer)
{
    // pass off to current pokemon
    getPokemon(0)->onRoundEnd(*enemyPlayer.getPokemon(0));
}


void Player::surrender()
{
    surrenders = true;
}


bool Player::hasLost() const
{
    // did they surrender?
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
    // bounds checking
    if(index < 1 or index >= getNumPokemon())
    {
        return false;
    }

    // check if the entering pokemon is fainted
    Pokemon* enteringPokemon = getPokemon(index);
    if(enteringPokemon->isFainted())
    {
        return false;
    }

    // check if any of the lead pokemon's minor afflictions prevent them from
    // leaving
    Pokemon* leadPokemon = getPokemon(0);
    assert_debug(leadPokemon != NULL);

    for(int i = 0; i < leadPokemon->getNumMinorAfflictions(); ++i)
    {
        if(leadPokemon->getMinorAffliction(i)->isTrapped())
        {
            return false;
        }
    }

    return true;
}


Pokemon* Player::getPokemon(int index)
{
    // return pokemon from list or null if out of bounds
    if(index >= 0 and index < Environment::MAX_POKEMON)
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

