// 
// File: Type.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Type.h"
#include "Debug.h"
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cassert>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

using namespace std;
using namespace Json;
using namespace boost::filesystem;


vector<string> Type::allTypes;
map<TypePair, float> Type::typeMultipliers;

void Type::initialize()
{
    // parse file
    Reader reader;
    path filename =  current_path() / path("data/") / path("Type.json");
    ifstream stream;
    stream.open(filename.string().c_str(), ifstream::in);
    Value root;
    reader.parse(stream, root, true);

    const Value& typesRoot = root.get("types", Value::null);
    const Value& typeModRoot = root.get("typeModifiers", Value::null);

    // Add each type to the list of valid types
    for(ValueIterator it = typesRoot.begin(); it != typesRoot.end(); it++)
    {
        string type = (*it).asString();
        assert_debug(not isType(type));
        println_debug("Registering Type " << type);
        allTypes.push_back(type);
    }

    // Add each modifier to the map
    for(ValueIterator it = typeModRoot.begin(); it != typeModRoot.end(); it++)
    {
        // get values
        const Value& typeMod = *it;
        string attacking = typeMod[0].asString();
        string defending = typeMod[1].asString();
        float modValue = typeMod[2].asFloat();

        // check if the type are valid
        assert(isType(attacking));
        assert(isType(defending));

        // add values to map
        println_debug("Registering Type Modifier " << attacking << " on " <<
            defending);
        typeMultipliers.insert(pair<TypePair, float>(TypePair(attacking,
            defending), modValue));
    }

    stream.close();
}

bool Type::isType(string s)
{
    // check if the string is in the list
    for(vector<string>::iterator it = allTypes.begin(); it != allTypes.end();
        it++)
    {
        if(*it == s)
        {
            return true;
        }
    }
    return false;
}

float Type::getMultiplier(string move, string defending)
{
    assert_debug(isType(move));
    assert_debug(isType(defending));

    // search map for value
    TypePair pair(move, defending);
    map<TypePair, float>::iterator it = typeMultipliers.find(pair);

    if(it == typeMultipliers.end())
    {
        return 1;
    }
    else
    {
        return it->second;
    }
}

float Type::getMultiplier(std::string move, string defending1,
    string defending2)
{
    float mult = getMultiplier(move, defending1) * getMultiplier(move, defending2);
    return mult;
}


TypePair::TypePair(std::string move, std::string defending)
:move(move)
,defending(defending)
{}

bool TypePair::operator<(const TypePair& other) const
{
    if(move == other.move)
    {
        return defending < other.defending;
    }
    else
    {
        return move < other.move;
    }
}

bool TypePair::operator>(const TypePair& other) const
{
    if(move == other.move)
    {
        return defending > other.defending;
    }
    else
    {
        return move > other.move;
    }
}

bool TypePair::operator==(const TypePair& other) const
{
    return move == other.move and defending == other.defending;
}

