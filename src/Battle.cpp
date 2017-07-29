// 
// File: Battle.cpp 
// 
// Author: Sam Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Battle.h"
#include "Pokemon.h"
#include "Move.h"
#include "Category.h"
#include "Type.h"
#include "Stat.h"
#include "Debug.h"

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;


void Battle::doBattle(Pokemon& attacking, Pokemon& defending, Move& move)
{
    // print the pokemon and move involved in this battle
    println_debug("Running Battle");
    cout << attacking.getNickname() << " used " << move.getName() << "."
        << endl;

    // determine if move will hit
    bool moveHit = willMoveHit(attacking, defending, move);

    if(moveHit)
    {
        // do the actual move
        if(move.getCategory() == STATUS)
        {
            // status moves just use a hook
            move.doEffect(attacking, defending);
        }
        else
        {
            // physical and special moves do damage
            int damage = getDamage(attacking, defending, move);
            defending.changeHp(-damage);
        }

        // hook for post-move effect
        move.onMoveEnd(attacking, defending, moveHit);
    }
    else
    {
        // print miss  statement
        cout << attacking.getNickname() << "'s attack missed." << endl;
    }
}

int Battle::roundDamage(float damage)
{
    // round down, but must be at least 1
    int rounded = (int) floor(damage);
    if(rounded < 0)
    {
        return 1;
    }
    return rounded;
}

bool Battle::willMoveHit(Pokemon& attacking, Pokemon& defending, Move& move)
{
    // get the moves acc
    float accuracy = move.getAccuracy();

    // if acc is set to always hit, no calculation is needed; it will hit
    if(accuracy == ALWAYS_HIT)
    {
        return true;
    }
    else if(accuracy == HIT_UNLESS_SEMI_INVUL)
    {
        return true;
    }

    // if is a normal value, calculate it
    else
    {
        // calculate the probability of the move hitting
        float hitProb = calcHitProb(attacking, defending, move);

        // roll percentile to hit; roll must be below probability to hit
        float percentile = (rand() % 100) * 0.01;
        bool moveHit = hitProb > percentile;

        // debug message
        println_debug("Random percentile: " << percentile);
        println_debug("Move hit: " << (moveHit ? "True" : "False"));
        println_debug("");

        return moveHit;
    }
}

float Battle::calcHitProb(Pokemon& attacking, Pokemon& defending, Move& move)
{
    // calculate using move accuracy, pokemon accuracy, and pokemon evasiveness
    float moveAcc = move.getAccuracy();
    float pokemonAcc = attacking.getAccuracy().getModValue();
    float pokemonEva = defending.getEvasiveness().getModValue();
    float hitProb = moveAcc * pokemonAcc / pokemonEva;

    // debug messages
    println_debug("Probability of " << attacking.getNickname() << " hitting "
        << defending.getNickname() << " with " << move.getName());
    println_debug("Move Accuracy: " << moveAcc);
    println_debug("Attacking Pokemon Accuracy: " << pokemonAcc);
    println_debug("Defending Pokemon Evasiveness: " << pokemonEva);
    println_debug("Chance of hit: " << hitProb);

    return hitProb;
}

int Battle::getDamage(Pokemon& attacking, Pokemon& defending, Move& move)
{
    // get the pokemon's level
    int level = attacking.getLevel();

    // get the relavent values for attack and defense
    int attackStat;
    int defenseStat;
    if(move.getCategory() == PHYSICAL)
    {
        attackStat = attacking.getAttack().getModValue();
        defenseStat = defending.getDefense().getModValue();
    }
    else
    {
        attackStat = attacking.getSpecialAttack().getModValue();
        defenseStat = defending.getSpecialDefense().getModValue();
    }

    // get the moves power
    double attackPower = move.getPower();

    // get the stab
    double STAB = 1.0;
    if(attacking.getTypeOne() == move.getType() or attacking.getTypeTwo() ==
        move.getType())
    {
        STAB = 1.5;
    }

    // get the type multiplier
    double typeMult = Type::getMultiplier(move.getType(), defending.getTypeOne(),
        defending.getTypeTwo());

    // get the random number 85-100
    double randomNumber = (rand() % 16) + 85;

    // do the calculation
    double damage = ((((2.0 * level / 5.0 + 2.0) * attackStat * attackPower /
        defenseStat) / 50.0) + 2.0) * STAB * typeMult *
        randomNumber / 100.0;

    // print debug messages
    println_debug("Damage for " << attacking.getNickname() << " attacking " <<
        defending.getNickname() << " with " << move.getName());
    println_debug("Level = " << level);
    println_debug("attackStat = " << attackStat);
    println_debug("attackPower = " << attackPower);
    println_debug("defenseStat = " << defenseStat);
    println_debug("STAB = " << STAB);
    println_debug("type = " << typeMult);
    println_debug("random = " << randomNumber);
    println_debug("Damage calculated = " << damage);
    println_debug("");

    // round damage 
    return roundDamage(damage);
}

