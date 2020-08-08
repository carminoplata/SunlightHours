#ifndef BUILDING_H
#define BUILDING_H

#include <string>

class Building
{
public:
  std::string name;
  int floors;
  float distance;
public:
  Building();
  Building(const std::string & name, int floors, float distance);
  ~Building();
  Building(const Building & old);
  Building & operator=(const Building & old);
  Building(const Building && old);
  Building & operator=(const Building && old);
  std::string to_string() const;
};
#endif