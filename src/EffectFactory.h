// 
// File: EffectFactory.h 
// 
// Author: Sam Clotfelter
// 
// Creates effects. Unlike other factories, the generated objects here are
// hard-coded.
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef EFFECT_FACTORY_H_
#define EFFECT_FACTORY_H_

#include "EffectId.h"

class Effect;

class EffectFactory
{

  public:

    /// Create pokemon of the species id. Calling function must de-allocate.
    static Effect* createEffect(EffectId speciesId);

};

#endif // EFFECT_FACTORY_H_

