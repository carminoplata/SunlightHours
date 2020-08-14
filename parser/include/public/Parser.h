
#include <City.h>

#include <string>
#include <vector>

class Parser {
 public:
  Parser() = default;
  ~Parser() {}
  virtual void parse(const std::string &file, City & city) = 0;
};
