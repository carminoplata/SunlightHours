#include "Building.h"

#include <tuple>
#include <sstream>

Building::Building()
: floors{0}
, distance{0.0}
{
}

Building::Building(const std::string & name, int floors, float distance)
: name{std::move(name)}
, floors{floors}
, distance{distance}
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
}

Building & Building::operator=(const Building & old)
{
  name = old.name;
  floors = old.floors;
  distance = old.distance;
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


