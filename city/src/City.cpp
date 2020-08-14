
#include "City.h"

#include <iostream>

City::~City(){}

City::City(City && old){
  if(!old.isEmpty()){
    districts.reserve(old.districts.size());
    districts = std::move(old.districts);
  }
}

City & City::operator=(const City && old)
{
  if(!old.isEmpty()){
    districts.reserve(old.districts.size());
    std::move(old.districts.begin(), old.districts.end(), districts.begin());
  }
  return *this;
}

int City::size() const
{
  return districts.size();
}

void City::add(Neighborhood district){
  districts.push_back(std::move(district));
}

bool City::isEmpty() const
{
  return districts.empty();
}

Neighborhood* City::findNeighborhood(const std::string& name){
  if(districts.empty()){
    return nullptr;
  }

  auto it = std::find_if(districts.begin(), districts.end(), [&name](const Neighborhood & n){
    return n.getName() == name;
  });

  return it!=districts.end() ? it.base() : nullptr;
}