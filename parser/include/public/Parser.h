#include <CommandList.h>
#include <Room.h>
#include <string>
#include <vector>

namespace parser
{
  class Parser
  {
  protected:
    Room map;
    CommandList commands;
    int battery;
    int startPoint_x;
    int startPoint_y;
    Direction direction;

  public:
    Parser() = default;
    ~Parser(){}

    int getBattery() { return battery; }
    int getPointX() { return  startPoint_x; }
    int getPointY() { return startPoint_y; }
    Direction getDirection() { return direction; }
    Room getRoom() { return std::move(map); }
    CommandList getCommands() {return std::move(commands);}
    virtual void parse(const std::string &file) = 0;
    virtual void write(const std::string & filename, const std::set<Position> & visited,
      const std::set<Position> & cleaned, const Position & position, const char & direction, int battery) = 0;
  };

}

