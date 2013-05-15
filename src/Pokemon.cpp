// 
// File: Pokemon.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Pokemon.h"
#include "MajorAffliction.h"
#include "MinorAffliction.h"
#include "Move.h"
#include "Type.h"
#include "Stat.h"
#include "Debug.h"

#include <string>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;


Pokemon::Pokemon(string nickname, string speciesName, Type typeOne,
    Type typeTwo, int maxHp, int baseAttack, int baseDefense,
    int baseSpecialAttack, int baseSpecialDefense, int baseSpeed, Move* move1,
    Move* move2, Move* move3, Move* move4)
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
{
    // place all non-null moves into the pokemon's move container
    Move** tmpMoves = new Move*[MAX_MOVES];
    tmpMoves[0] = move1;
    tmpMoves[1] = move2;
    tmpMoves[2] = move3;
    tmpMoves[3] = move4;
    for(int i(0); i < MAX_MOVES; ++i)
    {
        if(tmpMoves[i] != NULL)
        {
            moves.push_back(tmpMoves[i]);
        }
    }
    delete tmpMoves;

    assert(moves.size() > 0);
    assert(moves.size() <= MAX_MOVES);
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
    for(vector< MinorAffliction* >::iterator it(minorAfflictions.begin());
        it != minorAfflictions.end(); ++it)
    {
        delete *it;
    }
    for(vector< Move* >::iterator it(moves.begin()); it != moves.end();
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


Move* Pokemon::getMove(int index)
{
    assert(index >= 0 and index < moves.size());

    return moves[index];
}


int Pokemon::getNumMoves() const
{
    return moves.size();
}


const vector< Move* > Pokemon::getMovesContainer() const
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


Type Pokemon::getTypeOne() const
{
    return typeOne;
}


Type Pokemon::getTypeTwo() const
{
    return typeTwo;
}


const Stat& Pokemon::getAttack() const
{
    return *attack;
}

const Stat& Pokemon::getDefense() const
{
    return *defense;
}

const Stat& Pokemon::getSpecialAttack() const
{
    return *specialAttack;
}

const Stat& Pokemon::getSpecialDefense() const
{
    return *specialDefense;
}

const Stat& Pokemon::getSpeed() const
{
    return *speed;
}

const Stat& Pokemon::getAccuracy() const
{
    return *accuracy;
}

const Stat& Pokemon::getEvasiveness() const
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


void Pokemon::onRoundEnd()
{
    // call minor and major afflcition
    for(vector< MinorAffliction* >::iterator it(minorAfflictions.begin());
        it != minorAfflictions.end(); ++it)
    {
        (*it)->onRoundEnd();
    }

    if(majorAffliction != NULL)
    {
        majorAffliction->onRoundEnd();
    }

    // call moves
    for(vector< Move* >::iterator it(moves.begin()); it != moves.end();
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


void Pokemon::setMajorAffliction(MajorAffliction* affliction)
{
    assert(this->majorAffliction == NULL);

    this->majorAffliction = affliction;
}

void Pokemon::addMinorAffliction(MinorAffliction* affliction)
{
    minorAfflictions.push_back(affliction);
}


/// All implementations for derived classes of Pokemon go below here.


Charmander::Charmander(const string nickname)
:Pokemon(nickname, "Charmander", FIRE, NONE, 39, 52, 143, 60, 150, 65, new Ember(), NULL,
    NULL, NULL)
{
}

Squirtle::Squirtle(const string nickname)
:Pokemon(nickname, "Squirtle", WATER, NONE, 29, 30, 180, 23, 121, 29, new WaterGun(), NULL,
    NULL, NULL)
{
}

