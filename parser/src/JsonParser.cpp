#include "JsonParser.h"

#include <boost/property_tree/json_parser/error.hpp>
#include <exception>
#include <iostream>

#include "ParserException.h"

JsonParser::~JsonParser() {}

void JsonParser::parse(const std::string& file, City & city) {
  try {
    pt::json_parser::read_json(file, jsonTree);
    parseAndValidateData(file, city);
  } catch (pt::json_parser::json_parser_error& e) {
    throw InvalidJsonFile(file, e.message());
  } catch (pt::ptree_bad_data& e) {
    throw InvalidJsonFile(file, e.what());
  } catch (pt::ptree_bad_path& e) {
    throw InvalidJsonFile(file, e.what());
  } catch (pt::ptree_error& e) {
    throw InvalidJsonFile(file, e.what());
  }
}

void JsonParser::parseAndValidateData(const std::string& file, City & city) {
  auto cityTree = jsonTree.get_child("city");

    for (auto it = cityTree.begin(); it != cityTree.end(); it++) {
      std::string district;
      float aptHeight;
      for (auto nit = it->second.begin(); nit != it->second.end(); nit++) {
        if (nit->first == "neighborhood") {
          district = nit->second.data();
        } else if (nit->first == "apartments_height") {
          try{
            aptHeight = std::stof(nit->second.data());
            if(aptHeight <= 0)
            {
              throw InvalidData(file, "bad value ", nit->first);
            }
          }catch(std::exception & e){
            throw InvalidData(file, "bad value ", nit->first);
          }
        } else if (nit->first == "buildings") {
          Neighborhood neighborhood(district, aptHeight);
          auto buildings = nit->second.begin();
          for (; buildings != nit->second.end(); buildings++) {
            auto buildIt = buildings->second.begin();
            std::string name;
            int numApt;
            float distance;
            for (; buildIt != buildings->second.end(); buildIt++) {
              if (buildIt->first == "name") {
                name = buildIt->second.data();
              } else if (buildIt->first == "apartments_count") {
                try{
                  numApt = std::stoi(buildIt->second.data());
                }catch(std::exception & e){
                  throw InvalidData(file, "bad value ", buildIt->first);
                }
              } else if (buildIt->first == "distance") {
                try{
                  distance = std::stof(buildIt->second.data());
                  neighborhood.add({name, numApt, distance, aptHeight});
                }catch(std::exception & e){
                  throw InvalidData(file, "bad value ", buildIt->first);
                }
              } else {
                throw InvalidData(file,
                                  "Unknown building field ", buildIt->first);
              }
            }
          }
          city.add(std::move(neighborhood));
        } else {
          throw InvalidData(file, "Unknown neighborhood field ", nit->first);
        }
      }
    }
}
