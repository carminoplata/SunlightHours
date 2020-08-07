#include "JsonParser.h"

namespace parser
{
  class ParserManager
  {
  private:
    Parser * parser;
  public:
    ParserManager();
    ~ParserManager();
    void parse(const std::string & file);
    void write(const std::string & filename, const std::set<Position> & visited,
      const std::set<Position> & cleaned, const Position & finalPos, const char & direction, int battery);
    int getBattery();
    int getPositionX();
    int getPositionY();
    Direction getDirection();
    Room getRoom();
    CommandList getCommands();
  private:
    bool endsWith(const std::string & s, const std::string & suffix);
  };
}