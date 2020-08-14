#include "JsonParser.h"

class ParserManager {
 private:
  Parser* parser;

 public:
  ParserManager();
  ~ParserManager();
  void parse(const std::string& file, City & city);


 private:
  bool endsWith(const std::string& s, const std::string& suffix);
};