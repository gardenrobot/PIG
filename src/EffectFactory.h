// 
// File: EffectFactory.h 
// 
// Author: Lucas Clotfelter
// 
// Creates effects. Unlike other factories, the generated objects here are
// hard-coded.
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef EFFECT_FACTORY_H_
#define EFFECT_FACTORY_H_

class Effect;

class EffectFactory
{

  public:

    /// Create pokemon of the species id. Calling function must de-allocate.
    static Effect* createEffect(int speciesId);

};

#endif // EFFECT_FACTORY_H_

