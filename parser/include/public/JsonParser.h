#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>

#include "Parser.h"

namespace pt = boost::property_tree;

class JsonParser : public Parser {
 private:
  pt::ptree jsonTree;

 public:
  JsonParser() = default;
  ~JsonParser();

  void parse(const std::string& file) override;

 private:
  void parseAndValidateData(const std::string& file);
};
