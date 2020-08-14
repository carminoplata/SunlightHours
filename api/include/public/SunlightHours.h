#ifndef SUNLIGHTHOURS_H
#define SUNLIGHTHOURS_H

#include <string>
#include <ParserManager.h>


class SunlightHours
{
private:
  ParserManager manager;
  City city;
public:
  SunlightHours() = default;
  ~SunlightHours();
  SunlightHours(const SunlightHours & hours) = delete;
  SunlightHours & operator=(const SunlightHours& hours) = delete;
  SunlightHours(const SunlightHours&& hours);
  SunlightHours & operator=(const SunlightHours&& hours);
  void init(const std::string & filename);
  std::string getSunlightHours(const std::string & neighbourhood, const std::string & building, int apt);

private:
  bool isValidFile(const std::string & filename);
  double calculateSunlightEast(int building, int apt, const Neighborhood & district);
  double calculateSunlightWest(int building, int apt, double start, const Neighborhood & district);
  double calculateSunHeight(double hourAngle);
  double getShadow(double aptHeight, double sunHeight);
};

#endif
