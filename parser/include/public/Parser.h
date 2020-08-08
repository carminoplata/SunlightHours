
#include <City.h>

#include <string>
#include <vector>

class Parser {
 protected:
  City city;

 public:
  Parser() = default;
  ~Parser() {}
  City getCity() { return std::move(city); }
  virtual void parse(const std::string &file) = 0;
};
