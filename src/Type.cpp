// 
// File: Type.cpp 
// 
// Author: Lucas Clotfelter
// 
// //////////////////////////////////////////////////////////////////// 

#include "Type.h"
#include "Environment.h"
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


// define static variables
vector<string> Type::allTypes;
map<TypePair, float> Type::typeMultipliers;
string Type::NO_TYPE = "";

void Type::initialize()
{
    // parse file
    Reader reader;
    path filename =  current_path() / Environment::DATA_DIR /
        Environment::TYPE_DATA_FILE;
    ifstream stream;
    stream.open(filename.string().c_str(), ifstream::in);
    Value root;
    reader.parse(stream, root, true);

    const Value& typesRoot = root.get("types", Value::null);
    const Value& typeModRoot = root.get("typeModifiers", Value::null);

    // Register NO_TYPE
    allTypes.push_back(NO_TYPE);

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
        int attackingIndex = 0;
        int defendingIndex = 1;
        int modValueIndex = 2;
        string attacking = typeMod[attackingIndex].asString();
        string defending = typeMod[defendingIndex].asString();
        float modValue = (float) typeMod[modValueIndex].asDouble();

        // check if the type are valid
        assert(isType(attacking));
        assert(isType(defending));
        assert(attacking != NO_TYPE);
        assert(defending != NO_TYPE);

        // add values to map
        println_debug("Registering Type Modifier " << attacking << " on " <<
            defending);
        typeMultipliers.insert(pair<TypePair, float>(TypePair(attacking,
            defending), modValue));
    }

    // close file stream
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
    // multiply multiplier for move against both defending types
    float mult1 = getMultiplier(move, defending1);
    float mult2 = getMultiplier(move, defending2);
    float multTotal = mult1 * mult2;
    return multTotal;
}


TypePair::TypePair(std::string move, std::string defending)
:move(move)
,defending(defending)
{}

bool TypePair::operator<(const TypePair& other) const
{
    // sort by move, then defending
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
    // sort by move, then defending
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

