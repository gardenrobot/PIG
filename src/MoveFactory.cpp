// 
// File: MoveFactory.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Move.h"
#include "MoveFactory.h"
#include "MoveSpecies.h"
#include "Effect.h"
#include "EffectFactory.h"
#include "EffectId.h"
#include "Environment.h"
#include "Debug.h"

#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <fstream>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

using namespace std;
using namespace Json;
using namespace boost::filesystem;


const std::string MoveFactory::MOVE_JSON_FILE = "Move.json";
map<int, MoveSpecies*> MoveFactory::allSpecies;

void MoveFactory::initialize()
{
    // parse file
    Reader reader;
    path filename =  current_path() / Environment::DATA_DIR / MOVE_JSON_FILE;
    ifstream stream;
    stream.open(filename.string().c_str(), ifstream::in);
    Value root;
    reader.parse(stream, root, true);

    // iterate over and parse each move 
    for(ValueIterator it = root.begin(); it != root.end(); it++)
    {
        addSpecies(*it);
    }

    stream.close();
}

void MoveFactory::addSpecies(Value& value)
{
    // parse all single values from json
    int id = (int) value.get("id", Value::null).asInt();
    string name = value.get("name", Value::null).asString();
    string type = value.get("type", Value::null).asString();
    int damage = value.get("damage", Value::null).asInt();
    float accuracy = (float) value.get("accuracy", Value::null).asDouble();
    Category category = (Category) value.get("category", Value::null).asInt();
    EffectId effectId = (EffectId) value.get("effectId", Value::null).asInt();

    // create species with parsed values
    MoveSpecies* species = new MoveSpecies(name, type, damage, accuracy,
        category, effectId);

    // add to container
    println_debug("Registering Move " << id);
    allSpecies.insert(std::pair<int, MoveSpecies*>(id, species));
}

void MoveFactory::destroy()
{
    for(map<int, MoveSpecies*>::iterator it = allSpecies.begin();
        it != allSpecies.end(); it++)
    {
        delete it->second;
    }
}

Move* MoveFactory::createMove(int speciesId)
{
    // get the species from map
    MoveSpecies* species;
    try
    {
        species = allSpecies.at(speciesId);
    }
    catch(const out_of_range& e)
    {
        println_debug("Move ID " << speciesId << " not found.");
        return NULL;
    }

    // get values from species
    string name = species->name;
    string type = species->type;
    int damage = species->damage;
    float accuracy = species->accuracy;
    Category category = species->category;
    EffectId effectId = species->effectId;

    // get effect from effect factory

    Effect* effect = EffectFactory::createEffect(effectId);

    // create move from values
    Move* move = new Move(name, type, damage, accuracy, category, effect);
    return move;
}

