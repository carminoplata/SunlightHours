#include "Neighborhood.h"
#include "InvalidValuesException.h"

Neighborhood::Neighborhood(std::string name, float aptHeight)
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

int Neighborhood::size() const
{
  return buildings.size();
}

float Neighborhood::getBuildingHeight(int building) const{
  return buildings[building].getHeight();
}

/*std::vector<Building>::iterator Neighborhood::findBuilding(const std::string & building){
  auto palace = std::find_if(buildings.begin(), buildings.end(), [&building](const Building & b){
    return b.equals(building);
  });
 return palace ;
}*/

int Neighborhood::findApt(const std::string & building, int apt){
  auto palace = std::find_if(buildings.begin(), buildings.end(), [&building](const Building & b){
    return b.equals(building);
  });

  if(palace == buildings.end()){
    throw InvalidBuilding(building);
  }else if(!palace->hasGotApt(apt)){
    throw InvalidApt(std::to_string(apt));
  }

  return palace - buildings.begin() ;
}

std::vector<Building>::const_iterator Neighborhood::begin() const {
  return buildings.begin();
}


std::vector<Building>::const_iterator Neighborhood::end() const{
  return buildings.end();
}

bool Neighborhood::isValidApt(int index, int apt){
  return buildings[index].hasGotApt(apt);
}

/*void Neighborhood::calculateLimit(const std::string & building, int apt, double_t & east, double_t& west){
  int buildingPos = findBuilding(building);
  //if(target == buildings.end()){
  if(buildingPos == buildings.size()-1){
    throw InvalidBuilding(building);
  }

  //if(!target->hasGotApt(apt)){
  if(!buildings[buildingPos].hasGotApt(apt)){
    throw InvalidApt(std::to_string(apt));
  }

  float eastDistance = 0;
  float westDistance = buildings[buildingPos].getDistance();
  int eastIndex = findMaxEast(buildingPos, apt*aptHeight, eastDistance);
  int westIndex = findMaxWest(buildingPos+1, apt*aptHeight, westDistance);

  east = calculateSunlightEast(eastIndex, buildingPos, apt*aptHeight, 25, eastDistance);
  west = calculateSunlightWest(westIndex, buildingPos, apt*aptHeight, 25, westDistance);
  if(eastIndex < 0)
  {
    east = 0;
    //west = calculateAngle(target, westBuilding, apt, westDistance, true);
    west = calculateAngle(buildings[westIndex], apt * aptHeight, westDistance);
  }else if(westIndex < 0){
    //east = calculateAngle(target, eastBuilding, apt, eastDistance, false);
    //east = calculateAngle(buildings[eastIndex], apt * aptHeight, eastDistance);
    east = calculateSunlightEast(eastIndex, buildingPos, apt*aptHeight, 25, eastDistance);
    west = 0;
  }else{
    //east = calculateAngle(target, eastBuilding, apt, eastDistance, false);
    //west = calculateAngle(target, westBuilding, apt, westDistance, true);
    east = calculateAngle(buildings[eastIndex], apt * aptHeight, eastDistance);
    west = calculateAngle(buildings[westIndex], apt * aptHeight, westDistance);
  }
}*/


double Neighborhood::getDistanceFrom(int building) const{
  return buildings[building].getDistance();
}

double Neighborhood::calculateSunlightEast(int eastIndex, int buildingIndex,
  int aptHeight, double sunHeight, double distance){
    float heightSun = 0; 
    bool isHitbySun = false;
    double height = 0;
    if(eastIndex < 0){
      return height;
    }
    for(int i=0; i <=sunHeight && !isHitbySun; i=5){
      double shadow = getShadow(eastIndex, aptHeight, sunHeight);
      if(shadow <= distance){
        isHitbySun = true;
        height = calculateAngle(buildings[eastIndex], aptHeight, shadow);
      }
    }
    
    return height;
}

double Neighborhood::calculateSunlightWest(int westIndex, int buildingIndex,
  int aptHeight, double sunHeight, double distance){
    float heightSun = 0; 
    bool isHitbySun = false;
    double height = 0;
    if(westIndex < 0){
      return height;
    }
    for(int i=sunHeight; i >= 0 && !isHitbySun; i=i-5){
      double shadow = getShadow(westIndex, aptHeight, sunHeight);
      if(shadow <= distance){
        isHitbySun = true;
        height = calculateAngle(buildings[westIndex], aptHeight, distance);
      }
    }
    return height;
}

double Neighborhood::getShadow(int index, int aptHeight, double sunHeight){
  return buildings[index].getHeight() / tan(sunHeight);
}

/*void Neighborhood::calculateLimit(int index, int apt, double_t & east, double_t& west){
  float height;
  if(index == 0){
    east = 0;
    west = calculateAngle(index, index+1, apt, true);
  }else if(index == buildings.size()-1){
    west = 0;
    east = calculateAngle(index-1, index, apt, false);
  }else{
    east = calculateAngle(index-1, index, apt, false);
    west = calculateAngle(index, index+1, apt, true);
  }
}*/

/*double Neighborhood::calculateAngle(double distance, double height){
  return (atan(distance/height) * 180) / M_PI ;
}*/



/*double Neighborhood::calculateAngle(std::vector<Building>::iterator target,
  std::vector<Building>::iterator max, int apt, float distance, bool isWest){
  float height = max->getHeight() - apt * aptHeight;;
  if(height == 0){
    height = aptHeight;
  }
  return (atan(distance/height) * 180) / M_PI ;
}*/


/*const Building & Neighborhood::findMaxEast(std::vector<Building>::iterator start,
  int aptHeight, float & distance)*/
int Neighborhood::findMaxEast(int start, int aptHeight, float & distance) 
{
  bool found = false;
  int i = start - 1;
  int posMax = -1;  
  if(start==0)
  {
    return -1;
  }
  while(i >= 0 && !found){
    distance += buildings[i].getDistance();
    if(buildings[i].isTaller(aptHeight)){
      found = true;
    }else{
      if(posMax < 0 || buildings[i].isTaller(buildings[posMax].getHeight())){
        posMax = i;
      }
      i--;
    }
  }
  if(!found){
    return posMax;
  }else{
    return i;
  }
}

/*const Building & Neighborhood::findMaxWest(std::vector<Building>::iterator start,
  int aptHeight, float & distance)*/
int Neighborhood::findMaxWest(int start, int aptHeight, float & distance){
  bool found = false;
  int i = start;
  int posMax = -1;
  float maxDistance = distance;  
  if(start==buildings.size()-1)
  {
    return -1;
  }
  while(i < buildings.size() && !found){
    if(buildings[i].isTaller(aptHeight)){
      found = true;
    }else{
      distance += buildings[i].getDistance();
      if(posMax < 0 || buildings[i].isTaller(buildings[posMax].getHeight())){
        posMax = i;
        maxDistance = distance - buildings[i].getDistance();
      }
      i++;
    }
  }
  if(!found){
    distance = maxDistance;
    return posMax;
  }else{
    return i;
  }
}

double Neighborhood::calculateAngle(const Building & max, int aptHeight, float maxDistance){
  float height;
  if(max.isTaller(aptHeight)){
    height = max.getHeight() - aptHeight;
  }else {
    height = max.getHeight() - this->aptHeight;
  }
  return  (atan(maxDistance/height) * 180) / M_PI;
}

/*std::vector<Building>::iterator Neighborhood::findMax(std::vector<Building>::iterator start,
  int aptHeight, float & distance, bool towardsEast){
  bool found = false;

  if(start == buildings.begin()){
    distance += start->getDistance();
    return start;
  }else if(start == buildings.end()){
    return buildings.end();
  }else{
    if(towardsEast){
      auto it = start - 1;
      
    }
  }


  if(towardsEast){
    auto end = buildings.ren;
    auto it = --start;
    while(it != end && !found){
      distance += it->getDistance();
      if(it->isTaller(aptHeight)){
        found = true;
      }else{
        --it;
      }
    }
    if(!found && it == end){
      distance += start->getDistance();
    }
    return it;
  }else{
    return std::find_if(start, buildings.end(), [&aptHeight, &distance](const Building & b){
    if(!b.isTaller(aptHeight)){
      distance += b.getDistance();
      return false;
    }else{
      return true;
    }
    //return b.isTaller(aptHeight);
  });
  }
}*/

  /*if(towardsEast && result!=buildings.end()){
    distance += result->getDistance();
  }

  return result;*/
