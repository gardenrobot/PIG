// 
// File: PokemonFactory.h 
// 
// Author: Lucas Clotfelter
// 
// Factory for pokemon
// 
// //////////////////////////////////////////////////////////////////// 

#ifndef POKEMON_FACTORY_H_
#define POKEMON_FACTORY_H_

#include <string>
#include <map>

class Pokemon;
class PokemonSpecies;


class PokemonFactory
{

  public:

    /// Must be called once per process before use of this class.
    static void initialize();

    /// Create pokemon of the species id. Calling function must de-allocate.
    static Pokemon* createPokemon(int speciesId, std::string nickname);

  private:
    
    /// Holds one of each pokemon species objects
    static std::map<int, PokemonSpecies*> allSpecies;

};

#endif // POKEMON_FACTORY_H_

