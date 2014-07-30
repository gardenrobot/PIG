// 
// File: Stat.h 
// 
// Author: Lucas Clotfelter
// 
// Stats hold values that effect how a pokemon deals damage, takes damage, etc.
// Each stat has a constant base value which is multiplied by modifiers, which
// are effected by events in the game.
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef STAT_H_
#define STAT_H_


class Stat
{

  public:

    Stat(int base);

    Stat(const Stat& original);

    /// Change the stage
    Stat& operator+=(int change);
    Stat& operator-=(int change);

    /// Returns the original value of the stat
    float getBaseValue() const;

    /// Returns the value of the stat after being modified
    float getModValue() const;

  private:

    /// The base value
    const int base;

    /// Between 0 and 12. Lowering or raising this will change the modded value
    /// but not the base.
    int currentStage;

    /// Get the multiplier at the current stage
    float getModAt(int stage) const;

};


#endif // STAT_H_

