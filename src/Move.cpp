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
    Category category)
:name(name)
,type(type)
,damage(damage)
,accuracy(accuracy)
,category(category)
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
    effect->onRoundEnd(*this);
}


void Move::doEffect(Pokemon& owner, Pokemon& defending)
{
    effect->doEffect(*this, owner, defending);
}

