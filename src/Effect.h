// 
// File: Effect.h 
// 
// Author: Lucas Clotfelter
// 
// Move objects that have hooks for non-damage effects pass the work off
// to Effect objects.
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef EFFECT_H_
#define EFFECT_H_

class Pokemon;
class Move;


class Effect
{
    
  public:

    /// Called at the end of every turn that this move's owner is the current
    /// pokemon
    virtual void onRoundEnd(const Move& move) {}

    /// Performs the effect in place of an attack, if special category
    virtual void doEffect(const Move& move, Pokemon& owner, Pokemon& defending)
        {}

    /// Called after the move is done.
    virtual void onMoveEnd(const Move& move, Pokemon& owner,
        Pokemon& defending, bool moveHit) {}
    
};


/// These are the derived classes of Effect

class AfflictBurn : public Effect
{

  public:

    void onMoveEnd(const Move& move, Pokemon& owner, Pokemon& defending,
        bool moveHit);
    
};

class IncreaseSpeed2 : public Effect
{

  public:

    void doEffect(const Move& move, Pokemon& owner, Pokemon& defending);
    
};

#endif // EFFECT_H_

