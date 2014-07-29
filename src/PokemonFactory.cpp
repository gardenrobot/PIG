// 
// File: PokemonFactory.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Pokemon.h"
#include "PokemonFactory.h"
#include "PokemonSpecies.h"
#include "PokemonId.h"
#include "MoveFactory.h"
#include "MoveId.h"
#include "Debug.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <stdlib.h>
#include <fstream>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

class Move;

using namespace std;
using namespace Json;
using namespace boost::filesystem;


map<PokemonId, PokemonSpecies*> PokemonFactory::allSpecies;

void PokemonFactory::initialize()
{
    // parse file
    Reader reader;
    path filename =  current_path() / path("data/") / path("Pokemon.json");
    ifstream stream;
    stream.open(filename.string().c_str(), ifstream::in);
    Value root;
    reader.parse(stream, root, true);

    // iterate over and parse each pokemon 
    for(ValueIterator it = root.begin(); it != root.end(); it++)
    {
        addSpecies(*it);
    }

    stream.close();
}

void PokemonFactory::addSpecies(Value& value)
{
    // parse all single values from json
    PokemonId id = (PokemonId) value.get("id", Value::null).asInt();
    string name = value.get("name", Value::null).asString();
    int hp = value.get("hp", Value::null).asInt();
    int attack = value.get("attack", Value::null).asInt();
    int defense = value.get("defense", Value::null).asInt();
    int specialAttack = value.get("specialAttack", Value::null).asInt();
    int specialDefense = value.get("specialDefense", Value::null).asInt();
    int speed = value.get("speed", Value::null).asInt();
    float genderDist = (float) value.get("gender", Value::null).asDouble();


    // parse types
    string type1 = value.get("type1", Value::null).asString();
    string type2 = Type::NO_TYPE;
    const Value& type2Value = value.get("type2", Value::null);
    if(type2Value.isString())
    {
        type2 = type2Value.asString();
    }

    // check that types are valid
    assert(Type::isType(type1));
    assert(Type::isType(type2));
    assert(type1 != Type::NO_TYPE);
    assert(type1 != type2);


    // initialize container for the pokemon species' moves
    MoveId moveIds[Pokemon::MAX_MOVES];
    for(int i = 0; i < Pokemon::MAX_MOVES; i++)
    {
        moveIds[i] = NO_MOVE;
    }
    // parse move id values into move species
    Value moveIdsRaw = value.get("moves", Value::null);
    for(int i = 0; i < moveIdsRaw.size(); i++)
    {
        Value moveId = moveIdsRaw[i];
        moveIds[i] = (MoveId) moveId.asInt();
    }

    // create species with parsed values
    PokemonSpecies* species = new PokemonSpecies(name, type1, type2, hp, attack,
        defense, specialAttack, specialDefense, speed, moveIds[0], moveIds[1],
        moveIds[2], moveIds[3], genderDist);

    // add to container
    println_debug("Registering Pokemon " << id);
    allSpecies.insert(std::pair<PokemonId, PokemonSpecies*>(id, species));
}

void PokemonFactory::destroy()
{
    for(map<PokemonId, PokemonSpecies*>::iterator it = allSpecies.begin();
        it != allSpecies.end(); it++)
    {
        delete it->second;
    }
}

Pokemon* PokemonFactory::createPokemon(PokemonId speciesId, string nickname="")
{
    // get the species from map
    PokemonSpecies* species;
    try
    {
        species = allSpecies.at(speciesId);
    }
    catch(const out_of_range& e)
    {
        println_debug("Pokemon ID " << speciesId << " not found.");
        return NULL;
    }

    // get values from species
    string speciesName = species->speciesName;
    string typeOne = species->typeOne;
    string typeTwo = species->typeTwo;
    int maxHp = species->maxHp;
    int baseAttack = species->baseAttack;
    int baseDefense = species->baseDefense;
    int baseSpecialAttack = species->baseSpecialAttack;
    int baseSpecialDefense = species->baseSpecialDefense;
    int baseSpeed = species->baseSpeed;
    MoveId moveId1 = species->moveId1;
    MoveId moveId2 = species->moveId2;
    MoveId moveId3 = species->moveId3;
    MoveId moveId4 = species->moveId4;

    // Determine the gender
    float genderDist = species->genderDist;
    Gender gender;
    if(genderDist == NO_GENDER_DIST)
    {
        gender = NO_GENDER;
    }
    else if(((rand() % 100) * 0.01) < genderDist)
    {
        gender = FEMALE;
    }
    else
    {
        gender = MALE;
    }

    // if there is no nickname, use the species name
    if(nickname == "")
    {
        nickname = speciesName;
    }

    // create the pokemon's moves
    Move* move1 = MoveFactory::createMove(moveId1);
    Move* move2 = MoveFactory::createMove(moveId2);
    Move* move3 = MoveFactory::createMove(moveId3);
    Move* move4 = MoveFactory::createMove(moveId4);

    // create move from values
    Pokemon* pokemon = new Pokemon(nickname, speciesName, typeOne, typeTwo,
        maxHp, baseAttack, baseDefense, baseSpecialAttack, baseSpecialDefense,
        baseSpeed, move1, move2, move3, move4, gender);
    return pokemon;
}

const map<PokemonId, const PokemonSpecies*> PokemonFactory::getAllSpecies()
{
    map<PokemonId, const PokemonSpecies*> allSpeciesList;

    for(map<PokemonId, PokemonSpecies*>::iterator it = allSpecies.begin();
        it != allSpecies.end(); it++)
    {
        PokemonId id = it->first;
        PokemonSpecies* species = it->second;
        allSpeciesList.insert(pair<PokemonId, const PokemonSpecies*>(id, species));
    }

    return allSpeciesList;
}

