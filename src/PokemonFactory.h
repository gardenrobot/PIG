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
#include <jsoncpp/json/value.h>

class Pokemon;
class PokemonSpecies;


class PokemonFactory
{

  public:

    /// The json file to parse
    static const std::string POKEMON_JSON_FILE;

    /// Must be called once per process before use of this class.
    static void initialize();

    /// Should be called at the end of the process. Will prevent memory leaks.
    static void destroy();

    /// Create pokemon of the species id. Calling function must de-allocate.
    static Pokemon* createPokemon(int speciesId, std::string nickname);

    /// Get all pokemon species
    static const std::map<int, const PokemonSpecies*> getAllSpecies();

  private:
    
    /// Holds one of each pokemon species objects
    static std::map<int, PokemonSpecies*> allSpecies;

    /// Parses the Json value and adds it to the species container
    static void addSpecies(Json::Value& value);

};

#endif // POKEMON_FACTORY_H_

