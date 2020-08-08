#include "SunlightHours.h"
#include "SunlightHoursException.h"

#include <ParserException.h>
#include <fstream>

SunlightHours::~SunlightHours()
{
}

SunlightHours::SunlightHours(const SunlightHours && hours)
{
  manager = std::move(hours.manager);
}

SunlightHours & SunlightHours::operator=(const SunlightHours && hours)
{
  manager = std::move(hours.manager);

  return *this;
}

void SunlightHours::init(const std::string & filename)
{
  if(!isValidFile(filename)){
    throw InvalidFile(filename, "Unknown format or file not found. Required JSON file");
  }
  try{
    manager.parse(filename);
  }catch(InvalidData & e){
    throw InvalidFile(filename, e.what());
  }
}

std::string SunlightHours::getSunlightHours(const std::string & neighbourhood, 
  const std::string & building, int apt)
{
  return "";
}

bool SunlightHours::isValidFile(const std::string & filename)
{
  std::ifstream stream;

  stream.open(filename);

  if(filename.substr(filename.size()-4) != "json" || stream.fail()){
    return false;
  }else{
    return true;
  }
  
}