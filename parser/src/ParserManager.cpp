#include "ParserManager.h"


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

  City ParserManager::getCity()
  {
    return parser->getCity();
  }

  bool ParserManager::endsWith(const std::string & s, const std::string & suffix)
  {
    if(s.size() < suffix.size()){
      return false;
    }
    return std::equal(suffix.rbegin(), suffix.rend(),s.rbegin());
  }
