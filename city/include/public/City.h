#ifndef CITY_H
#define CITY_H

#include "Neighborhood.h"
//#include "Constants.h"
//#include "Position.h"

#include <vector>

class City
{
private:
  std::vector<Neighborhood> districts;

public:
  City() = default;
  ~City();
  City(const City &) = delete;
  City & operator=(const City &) = delete;
  City(City && old);
  City & operator=(const City && old);

  int size() const;
  bool isEmpty() const;
  void add(Neighborhood neighborhood);
  std::vector<Neighborhood> getNeighborhood();
  Neighborhood* findNeighborhood(const std::string& name);
private:
};

#endif

