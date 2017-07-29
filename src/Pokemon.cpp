// 
// File: Pokemon.cpp 
// 
// Author: Sam Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Pokemon.h"
#include "MajorAffliction.h"
#include "MinorAffliction.h"
#include "Move.h"
#include "Type.h"
#include "Stat.h"
#include "MoveFactory.h"
#include "Environment.h"
#include "Debug.h"

#include <string>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;


Pokemon::Pokemon(string nickname, string speciesName, string typeOne,
    string typeTwo, int maxHp, int baseAttack, int baseDefense,
    int baseSpecialAttack, int baseSpecialDefense, int baseSpeed,
    vector<Move*> moves, Gender gender)
:nickname(nickname)
,speciesName(speciesName)
,typeOne(typeOne)
,typeTwo(typeTwo)
,maxHp(maxHp)
,hp(maxHp)
,attack(new Stat(baseAttack))
,defense(new Stat(baseDefense))
,specialAttack(new Stat(baseSpecialAttack))
,specialDefense(new Stat(baseSpecialDefense))
,speed(new Stat(baseSpeed))
,accuracy(new Stat(1))
,evasiveness(new Stat(1))
,majorAffliction(NULL)
,level(50)
,moves(moves)
,gender(gender)
{
    assert(moves.size() > 0);
    assert(moves.size() <= Environment::MAX_MOVES);
}


Pokemon::~Pokemon()
{
    delete attack;
    delete defense;
    delete specialAttack;
    delete specialDefense;
    delete speed;
    delete accuracy;
    delete evasiveness;

    if(majorAffliction != NULL)
    {
        delete majorAffliction;
    }
    for(vector<MinorAffliction*>::iterator it(minorAfflictions.begin());
        it != minorAfflictions.end(); ++it)
    {
        delete *it;
    }
    for(vector<Move*>::iterator it(moves.begin()); it != moves.end();
        ++it)
    {
        delete *it;
    }
}


void Pokemon::setHp(int hp)
{
    println_debug(getNickname() << "'s hp set to " << hp);
    this->hp = hp;
}


void Pokemon::changeHp(int change)
{
    setHp(getHp() + change);
}


int Pokemon::getHp() const
{
    return hp;
}


int Pokemon::getMaxHp() const
{
    return maxHp;
}


string Pokemon::getSpeciesName() const
{
    return speciesName;
}


string Pokemon::getNickname() const
{
    return nickname;
}


Gender Pokemon::getGender() const
{
    return gender;
}


Move* Pokemon::getMove(int index)
{
    assert(index >= 0 and index < moves.size());

    return moves[index];
}


int Pokemon::getNumMoves() const
{
    return moves.size();
}


const vector<Move*> Pokemon::getMovesContainer() const
{
    return moves;
}


MajorAffliction* Pokemon::getMajorAffliction() 
{
    return majorAffliction;
}


int Pokemon::getNumMinorAfflictions() const
{
    return minorAfflictions.size();
}


MinorAffliction* Pokemon::getMinorAffliction(int index)
{
    assert(index >= 0 and index < minorAfflictions.size());

    return minorAfflictions[index];
}


string Pokemon::getTypeOne() const
{
    return typeOne;
}


string Pokemon::getTypeTwo() const
{
    return typeTwo;
}


Stat& Pokemon::getAttack() const
{
    return *attack;
}

Stat& Pokemon::getDefense() const
{
    return *defense;
}

Stat& Pokemon::getSpecialAttack() const
{
    return *specialAttack;
}

Stat& Pokemon::getSpecialDefense() const
{
    return *specialDefense;
}

Stat& Pokemon::getSpeed() const
{
    return *speed;
}

Stat& Pokemon::getAccuracy() const
{
    return *accuracy;
}

Stat& Pokemon::getEvasiveness() const
{
    return *evasiveness;
}


int Pokemon::getLevel() const
{
    return level;
}


bool Pokemon::isFainted() const
{
    return hp == 0;
}


void Pokemon::onRoundEnd(Pokemon& enemyPokemon)
{
    // call hooks for minor afflcition
    int i = 0;
    while(i < minorAfflictions.size())
    {
        MinorAffliction* aff = minorAfflictions.at(i);
        aff->onRoundEnd(enemyPokemon);
        if(aff->isFinished())
        {
            delete aff;
            minorAfflictions.erase(minorAfflictions.begin()+i);
        }
        else
        {
            i++;
        }
    }

    // call hooks for minor afflcition
    if(majorAffliction != NULL)
    {
        majorAffliction->onRoundEnd();
        if(majorAffliction->isFinished())
        {
            delete majorAffliction;
            majorAffliction = NULL;
        }
    }

    // call moves
    for(vector<Move*>::iterator it(moves.begin()); it != moves.end();
        ++it)
    {
        if(*it != NULL)
        {
            (*it)->onRoundEnd();
        }
    }
}


void Pokemon::healMajorAffliction()
{
    delete majorAffliction;
    majorAffliction = NULL;
}


void Pokemon::setMajorAffliction(MajorAffliction* affliction, bool force)
{
    if(this->majorAffliction == NULL or force)
    {
        this->majorAffliction = affliction;
    }
}

void Pokemon::addMinorAffliction(MinorAffliction* affliction)
{
    // check if the pokemon already has this kind of affliction
    for(vector<MinorAffliction*>::iterator it = minorAfflictions.begin();
        it != minorAfflictions.end(); it++)
    {
        if((*it)->name == affliction->name)
        {
            // this affliction already exists, do nothing
            println_debug("Affliction " << affliction->name <<
                " already exists.");
            return;
        }
    }

    // add the affliction
    println_debug("Affliction " << affliction->name << " added.");
    minorAfflictions.push_back(affliction);
}

