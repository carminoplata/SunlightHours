#include "Parser.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <iostream>
//#include <nlohmann/json.hpp>

namespace pt = boost::property_tree;

namespace parser
{
  class JsonParser : public Parser 
  {
  
  private:
    pt::ptree jsonTree;
  public:
    JsonParser() = default;
    ~JsonParser();

    void parse(const std::string & file) override;
    void write(const std::string & filename, const std::set<Position> & visited,
      const std::set<Position> & cleaned, const Position & pos, const char & direction, int battery) override;

  private:
    void parseAndValidateData(const std::string & file);
    void readCommandList(const std::string & file);
    void readMap(const std::string & file);
    void writeSet(const std::set<Position> & set, const std::string & name,
      pt::ptree & tree, const std::string & file);
   /* template<typename Result>
    Result readValue(const std::string & key, const Result & result)
    {
      int value = jsonTree.count(key);
      pt::ptree children = jsonTree.get_child(key);
      if(jsonTree.count(key) > 0)
      {
        std::cout << "Object " << key << " has got " << jsonTree.count(key) << " children" << std::endl;
        std::vector<std::string> array(jsonTree.count(key));
        BOOST_FOREACH(pt::ptree::value_type &v, jsonTree.get_child(key)){
          std::string value = v.second.data();
          std::cout << "Value: "<< value << std::endl;
          array.push_back(v.second.data());
        }
      }else{
        return jsonTree.get(key, result);
      }
    }*/
  };

} 