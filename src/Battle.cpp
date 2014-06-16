// 
// File: Battle.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Battle.h"
#include "Pokemon.h"
#include "Move.h"
#include "Category.h"
#include "Type.h"
#include "Stat.h"
#include "Debug.h"

#include <stdlib.h>
#include <math.h>


void Battle::doBattle(Pokemon& attacking, Pokemon& defending, Move& move)
{
    if(move.getCategory() == STATUS)
    {
        move.doEffect(attacking, defending);
    }
    else
    {
        bool moveHit = true; //TODO

        if(moveHit)
        {
            int damage = getDamage(attacking, defending, move);

            defending.changeHp(-damage);
        }

        // hook for post-move effect
        move.onMoveEnd(attacking, defending, moveHit);
    }
}


int Battle::getDamage(Pokemon& attacking, Pokemon& defending, Move& move)
{
    int level = attacking.getLevel();
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

    double attackPower = move.getPower();
    double STAB = 1.0;
    if(attacking.getTypeOne() == move.getType() or attacking.getTypeTwo() ==
        move.getType())
    {
        STAB = 1.5;
    }

    double typeMult = TypeMult::getMultiplier(move.getType(), defending.getTypeOne(),
        defending.getTypeTwo());

    double randomNumber = (rand() % 16) + 85;

    double damage = ((((2.0 * level / 5.0 + 2.0) * attackStat * attackPower /
        defenseStat) / 50.0) + 2.0) * STAB * typeMult *
        randomNumber / 100.0;

    println_debug("Damage for " << attacking.getNickname() << " attacking " <<
        defending.getNickname());
    println_debug("Level = " << level);
    println_debug("attackStat = " << attackStat);
    println_debug("attackPower = " << attackPower);
    println_debug("defenseStat = " << defenseStat);
    println_debug("STAB = " << STAB);
    println_debug("type = " << typeMult);
    println_debug("random = " << randomNumber);
    println_debug("Damage calculated = " << damage);
    println_debug("");

    return (int)ceil(damage);
}

