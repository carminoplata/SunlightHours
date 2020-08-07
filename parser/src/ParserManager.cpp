#include "ParserManager.h"

namespace parser
{
  ParserManager::ParserManager()
  {
    parser = nullptr;
  }

  ParserManager::~ParserManager()
  {
    //delete parser;
  }
  
  void ParserManager::parse(const std::string & file)
  {
    if(endsWith(file, "json") && parser == nullptr){
      parser = new JsonParser();
    }

    parser->parse(file);
  }

  void ParserManager::write(const std::string & filename, const std::set<Position> & visited,
    const std::set<Position> & cleaned, const Position & finalPos, const char & direction, int battery)
  {
    if(endsWith(filename, "json") && parser == nullptr ){
      parser = new JsonParser();
    }

    parser->write(filename, visited, cleaned, finalPos, direction, battery);
  }

  bool ParserManager::endsWith(const std::string & s, const std::string & suffix)
  {
    if(s.size() < suffix.size()){
      return false;
    }
    return std::equal(suffix.rbegin(), suffix.rend(),s.rbegin());
  }

  int ParserManager::getBattery()
  {
    return parser->getBattery();
  }
  
  int ParserManager::getPositionX()
  {
    return parser->getPointX();
  }
  
  int ParserManager::getPositionY()
  {
    return parser->getPointY();
  }

  Direction ParserManager::getDirection()
  {
    return parser->getDirection();
  }

  Room ParserManager::getRoom()
  {
    return parser->getRoom();
  }

  CommandList ParserManager::getCommands()
  {
    return std::move(parser->getCommands());
  }
}