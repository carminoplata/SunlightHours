#include <exception>
#include <string>

class InvalidCommand: public std::exception
{
private:
  std::string value;
public:
  InvalidCommand(const std::string & value) : value{value}
  {
  }
  ~InvalidCommand(){}

  std::string getError(){return "Invalid command : " + value;};
};

class InvalidCell: public std::exception
{
private:
  std::string value;
public:
  InvalidCell(const std::string & value) : value{value}
  {
  }
  ~InvalidCell(){}

  std::string getError(){return "Invalid cell : " + value;};
};

class PositionOutOfRange: public std::exception
{
private:
  int x;
  int y;
public:
  PositionOutOfRange(int x, int y) 
  : x{x}
  , y{y}
  {
  }
  ~PositionOutOfRange(){}

  std::string getError()
  {
    return "Position out of the map's range : (" + std::to_string(x) + "," + std::to_string(y) + ")";
  };
};
