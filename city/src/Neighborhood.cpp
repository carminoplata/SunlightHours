#include "Neighborhood.h"
#include "InvalidValuesException.h"

Neighborhood::Neighborhood(std::string name, int aptHeight)
: name{name}
, aptHeight{aptHeight}
, buildings{}
{
} 


Neighborhood::~Neighborhood()
{
}

Neighborhood::Neighborhood(const Neighborhood&& old)
{
  if(!old.isEmpty())
  {
    buildings = std::move(old.buildings);
    name = std::move(old.name);
    aptHeight = old.aptHeight;
  }
}

Neighborhood & Neighborhood::operator=(const Neighborhood && old)
{
  if(!old.isEmpty())
  {
    buildings = std::move(old.buildings);
    name = std::move(old.name);
    aptHeight = old.aptHeight;
  }
  
  return *this;
}

void Neighborhood::add(const Building & building){
  buildings.push_back(building);
}

bool Neighborhood::isEmpty()const
{
  return buildings.empty();
}

/*std::vector<Building>::const_iterator Neighborhood::begin() const
{
  return buildings.begin();
}

std::vector<Building>::const_iterator Neighborhood::end() const
{
  return buildings.end();
}*/

int Neighborhood::size() const
{
  return buildings.size();
}
