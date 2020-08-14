#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <ctime>
#include <cmath>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace bg =  boost::gregorian;
namespace bp = boost::posix_time;


static bg::date targetDate(2020, 12, 22);

static bp::ptime sunriseTime(targetDate, bp::hours(8) +  bp::minutes(14));
static bp::ptime sunsetTime(targetDate, bp::hours(17) + bp::minutes(25));

static const double_t sun_path = 180;

static const double barcellona_latitude = 41.38879;
static const double barcellona_longitude = 2.15899;
static const double declination = -23.45;
static const int sun_movement = 15;


inline float convertToRadians(double degrees){
  return M_PI * degrees/180;
}

inline float convertToDegrees(double radians){
  return 180 * radians /M_PI;
}

/*inline double calculateHeight(double hourAngle){
  return asin(sin(declination) * sin(barcellona_latitude) + 
    cos(declination) * cos(barcellona_latitude) * cos(hourAngle));
}*/

inline double convertTimeToHourAngle(bp::ptime time){
  auto currentTime = time.time_of_day();
  int hours = currentTime.hours();
  float minutes = static_cast<float>(currentTime.minutes()) / 60;
  float seconds = static_cast<float>(currentTime.seconds()) / 3600;
  double result = sun_movement * (currentTime.hours() + minutes + seconds - 12);

  
  return result;
}

inline std::string convertHourAngleToTime(double angle){
  double time = 12 + angle / sun_movement;
  int hours =  static_cast<int>(time);
  int minutes = (time - hours) * 60;
  int seconds = 0;
  bp::time_duration td{hours, minutes, seconds};
  return bp::to_simple_string(td);
}



#endif