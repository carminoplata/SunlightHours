#include "Constants.h"
#include "SunlightHours.h"
#include "SunlightHoursException.h"

#include <InvalidValuesException.h>
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
    manager.parse(filename, city);
  }catch(InvalidJsonFile & e){
    throw InvalidFile(filename, e.getError());
  }catch(InvalidData & e){
    throw InvalidFile(filename, e.getError());
  }
}

std::string SunlightHours::getSunlightHours(const std::string & neighbourhood, 
  const std::string & building, int apt)
{
  std::stringstream ss;
  double east = 0, west=0;
  std::string start, end;
  if(neighbourhood.empty() || building.empty() || apt < 0){
    throw InvalidInput("Invalid inputs");
  }

  auto district = city.findNeighborhood(neighbourhood);

  if(district == nullptr)
  {
    ss << "Neighbourhood "<< neighbourhood << " doesn't exist!"; 
    throw InvalidInput(ss.str());
  }
  try{
    int target = district->findApt(building, apt);

    east = calculateSunlightEast(target, apt, *district);
    west = calculateSunlightWest(target, apt, east, *district);
    start = convertHourAngleToTime(east);
    end = convertHourAngleToTime(west);

    ss << start << " - " << end;
    return ss.str();
  }catch(InvalidBuilding & e){
    throw InvalidInput(e.getError());
  }catch(InvalidApt & e){
    throw InvalidInput(e.getError());
  }
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

double SunlightHours::calculateSunlightEast(int building, int apt, const Neighborhood & district){
  bool isHitbySun = false;
  double sunrise = convertTimeToHourAngle(sunriseTime);
  double w=sunrise, eastAngle;
  float currHeight = (apt + 1) * district.getAptHeight();
  float distance = 0, height = 0; 
  int i = 1, prev = 0;
  
  if(building == 0){ 
    return sunrise;
  }

  while(w<0 && !isHitbySun){
    float sunHeight = calculateSunHeight(w);
    if(prev!= i){
      height = district.getBuildingHeight(building-i);
      distance += district.getDistanceFrom(building-i);
    }
    if(height >= currHeight){
      double shadow = getShadow(height, sunHeight);
      float diff = shadow - distance;
      if(diff <= 0 || diff < currHeight){
        // shadow shorter than distance between two buildings or shadow doesn't reach the apt's height
        // apt recieves the light from sun
        eastAngle = w;
        isHitbySun = true; 
      }else{
        w += sun_movement; //hour angle + 15° (due to Earth's movement).
        if(prev!=i){
          prev = i;
        }
      }
    }else{
      // building next to ours under observation is shorter than ours
      // change building for getting a new shadow.
      prev = i;
      i++;
      if(building-i > 0)
      {
        // no sun from east side for this building ==> recieve sun starting from midday.
        eastAngle = 0;
        isHitbySun = true;
      }
     
    }
  }

  if(!isHitbySun && w>=0){
    // set angle at midday
    eastAngle = 0;
  }

  return eastAngle;
}


double SunlightHours::calculateSunlightWest(int building, int apt, double start,
  const Neighborhood & district){

  bool isHitbySun = true;
  double sunset = convertTimeToHourAngle(sunsetTime);
  double w=start, westAngle;
  float currHeight = (apt + 1) * district.getAptHeight();
  float distance = 0, height = 0; 
  int i = 1, next = 0;

  if(building == district.size()-1){
    westAngle = sunset;
  }

  while(w<sunset && isHitbySun){
    float sunHeight = calculateSunHeight(w);
    if(next!= i){
      height = district.getBuildingHeight(building+i);
      distance += district.getDistanceFrom(building+next);
    }
    if(height >= currHeight){
      double shadow = getShadow(height, sunHeight);
      float diff = shadow - distance;
      if(diff > 0 || diff > currHeight){
        // shadow longer than distance between two buildings or shadow reaches the apt's height
        // apt doesn't recieve the light from sun (opposite east case)
        westAngle = w;
        isHitbySun = false; 
      }else{
        w += sun_movement; //hour angle + 15° (due to Earth's movement).
        if(next!=i){
          next = i;
        }
      }
    }else{
      // building next to ours under observation is shorter than ours
      // change building for getting a new shadow.
      next = i;
      i++;
      if(building+i >= district.size())
      {
        // building recieve sun until the sunset.
        westAngle = sunset;
        isHitbySun = false;
      }
    }
  }

  if(w>=sunset){
    // set angle at midday
    westAngle = sunset;
  }

  return westAngle;
}

double SunlightHours::calculateSunHeight(double hourAngle){
  double w = convertToRadians(hourAngle);
  double d = convertToRadians(declination);
  double latitude = convertToRadians(barcellona_latitude);
  double sunHeightRadians = asin(sin(d) * sin(latitude) + cos(d) * cos(latitude) * cos(w));
  return sunHeightRadians;
}


double SunlightHours::getShadow(double aptHeight, double sunHeight){
  // add error for sun height = 0 and height = 180
  return aptHeight * (cos(sunHeight)/sin(sunHeight));
}