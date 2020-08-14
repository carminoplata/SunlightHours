#include <exception>
#include <string>

class InvalidBuilding: public std::exception
{
private:
  std::string message;
public:
  InvalidBuilding(const std::string & message) : message{message}
  {
  }
  ~InvalidBuilding(){}

  std::string getError(){return "Invalid building " + message;};
};

class InvalidApt: public std::exception
{
private:
  std::string message;
public:
  InvalidApt(const std::string & message) : message{message}
  {
  }
  ~InvalidApt(){}

  std::string getError(){return "Invalid apartment : " + message;};
};