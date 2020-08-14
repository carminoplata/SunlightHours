#ifndef BUILDING_H
#define BUILDING_H

#include <string>

class Building
{
public:
  std::string name;
  int floors;
  float distance;
  float height;
public:
  Building();
  Building(const std::string & name, int floors, float distance, float aptHeight);
  ~Building();
  Building(const Building & old);
  Building & operator=(const Building & old);
  Building(const Building && old);
  Building & operator=(const Building && old);
  std::string to_string() const;
  std::string getName() const {return name;}
  int getNumOfApt() const {return floors;}
  float getDistance() const {return distance;}
  float getHeight() const {return height;}
  bool hasGotApt(int number) const ;
  bool equals(const std::string & name) const;
  bool isTaller(int height) const;
};
#endif