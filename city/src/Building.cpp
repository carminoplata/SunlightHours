#include "Building.h"

#include <tuple>
#include <sstream>

Building::Building()
: name{""}
, floors{0}
, distance{0.0}
, height{0}
{
}

Building::Building(const std::string & name, int floors, float distance, float aptHeight)
: name{std::move(name)}
, floors{floors}
, distance{distance}
, height{floors * aptHeight}
{
}

Building::~Building()
{
}

Building::Building(const Building & old)
{
  name = old.name;
  floors = old.floors;
  distance = old.distance;
  height = old.height;
}

Building & Building::operator=(const Building & old)
{
  name = old.name;
  floors = old.floors;
  distance = old.distance;
  height = old.height;
  return *this;
}

Building::Building(const Building && old)
{
  name = std::move(old.name);
  floors = old.floors;
  distance = old.distance;
}


Building & Building::operator=(const Building && old)
{
  name = std::move(old.name);
  floors = old.floors;
  distance = old.distance;
  return *this;
}

std::string Building::to_string() const
{
  std::stringstream ss;

  ss << "Building " << name << " floors " << floors << " distance " << distance;

  return ss.str();
}

bool Building::hasGotApt(int number) const {
  return number >= 0 && number < floors; 
}

bool Building::equals(const std::string & name) const {
  return this->name == name;
}

bool Building::isTaller(int height) const {
  return this->height > height;
}