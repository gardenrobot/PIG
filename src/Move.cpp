// 
// File: Move.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Move.h"
#include "Type.h"
#include "Effect.h"

#include <string>
#include <iostream>

using namespace std;


Move::Move(string name, Type type, int damage, float accuracy,
    Category category, Effect* effect)
:name(name)
,type(type)
,damage(damage)
,accuracy(accuracy)
,category(category)
,effect(effect)
{
}


Move::~Move()
{
}


string Move::getName() const
{
    return name;
}


Type Move::getType() const
{
    return type;
}


int Move::getPower() const
{
    return damage;
}


float Move::getAccuracy() const
{
    return accuracy;
}


Category Move::getCategory() const
{
    return category;
}


void Move::onRoundEnd() const
{
    if(effect != NULL)
    {
        effect->onRoundEnd(*this);
    }
}


void Move::doEffect(Pokemon& owner, Pokemon& defending)
{
    if(effect != NULL)
    {
        effect->doEffect(*this, owner, defending);
    }
}

void Move::onMoveEnd(Pokemon& owner, Pokemon& defending, bool moveHit)
{
    if(effect != NULL)
    {
        effect->onMoveEnd(*this, owner, defending, moveHit);
    }
}

