#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include "Building.h"

#include <cmath>
#include <string>
#include <vector>


class Neighborhood{
private:
  std::vector<Building> buildings;
  std::string name;
  float aptHeight;

public:
  Neighborhood() = default;
  Neighborhood(std::string name, float aptHeight);
  ~Neighborhood();
  Neighborhood(const Neighborhood&) = delete;
  Neighborhood& operator=(const Neighborhood&) = delete;
  Neighborhood(const Neighborhood&& old);
  Neighborhood& operator=(const Neighborhood&& old);

  void add(const Building & building);
  int size() const;
  bool isEmpty() const;
  //std::vector<Building>::iterator findBuilding(const std::string & building);
  int findApt(const std::string & building, int apt);
  std::string getName() const {return name;}
  float getAptHeight() const {return aptHeight;}
  float getBuildingHeight(int building) const;
  float getBuildingAptHeight(int building, int apt) const;
  std::vector<Building>::const_iterator begin() const;
  std::vector<Building>::const_iterator end() const;
  bool isValidApt(int index, int apt);
  void calculateLimit(const std::string & building, int apt, double_t & east, double_t & west);
  double calculateSunlightAngle(double start, double end, int building);
  double getDistanceFrom(int building)const;
private:
  //double calculateAngle(double distance, double height);
  
  int findMaxEast(int start, int aptHeight, float & distance);
  int findMaxWest(int start, int aptHeight, float & distance);
  double calculateSunlightEast(int eastIndex, int buildingIndex, int aptHeight,
    double sunHeight, double distance);
  double calculateSunlightWest(int westIndex, int buildingIndex,
    int aptHeight, double sunHeight, double distance);
  
  double getShadow(int index, int aptHeight, double sunHeight);
  //const Building & findMaxEast(std::vector<Building>::iterator start, int aptHeight, float & distance);
  //const Building & findMaxWest(std::vector<Building>::iterator start, int aptHeight, float & distance);
  std::vector<Building>::iterator findMax(std::vector<Building>::iterator start, int aptHeight, float & distance, bool towardsEast = false);
  /*double calculateAngle(std::vector<Building>::iterator target, 
    std::vector<Building>::iterator max, int apt, float distance, bool west);*/
  double calculateAngle(const Building & max, int aptHeight, float maxDistance);
};

#endif