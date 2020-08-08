#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include "Building.h"

#include <string>
#include <vector>


class Neighborhood{
private:
  std::vector<Building> buildings;
  std::string name;
  int aptHeight;

public:
  Neighborhood() = default;
  Neighborhood(std::string name, int aptHeight);
  ~Neighborhood();
  Neighborhood(const Neighborhood&) = delete;
  Neighborhood& operator=(const Neighborhood&) = delete;
  Neighborhood(const Neighborhood&& old);
  Neighborhood& operator=(const Neighborhood&& old);

  void add(const Building & building);
  int size() const;
  bool isEmpty() const;
  //std::vector<Building>::const_iterator begin() const;
  //std::vector<Building>::const_iterator end() const;
};

#endif