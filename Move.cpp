// 
// File: Move.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Move.h"
#include "Type.h"

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
    cout << "Move sees that the round is ending" << endl;
}


void Move::doEffect(Pokemon& owner, Pokemon& defending)
{
}


/// All implementations for derived moves go below here

Ember::Ember()
:Move(string("Ember"), FIRE, 40, 0.75F, SPECIAL)
{
}

WaterGun::WaterGun()
:Move(string("Water Gun"), WATER, 40, 0.75F, SPECIAL)
{
}

