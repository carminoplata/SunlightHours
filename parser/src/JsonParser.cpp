#include "JsonParser.h"
#include "ParserException.h"
#include "Constants.h"

#include <InvalidValuesException.h>
#include <boost/property_tree/json_parser/error.hpp>
#include <boost/foreach.hpp>

#include <iostream>

namespace parser
{
  JsonParser::~JsonParser()
  {
  }

  void JsonParser::parse(const std::string & file)
  {
    try{
      pt::json_parser::read_json(file, jsonTree);
      parseAndValidateData(file);
    }catch(pt::json_parser::json_parser_error & e)
    {
      throw InvalidJsonFile(file, e.message());
    }catch(pt::ptree_bad_data & e)
    {
      throw InvalidJsonFile(file, e.what());
    }catch(pt::ptree_bad_path & e)
    {
      throw InvalidJsonFile(file, e.what());
    }catch(pt::ptree_error & e)
    {
      throw InvalidJsonFile(file, e.what());
    }
  }

  void JsonParser::write(const std::string & filename, const std::set<Position> & visited,
    const std::set<Position> & cleaned, const Position & pos, const char & direction, int battery)
  {
    pt::ptree tree; 
    pt::ptree subTreeVisited;
    pt::ptree subTreeCleaned;
    try{
      writeSet(visited, "visited", subTreeVisited, filename);
      writeSet(cleaned, "cleaned", subTreeCleaned, filename);
      tree.put_child("visited", subTreeVisited);
      tree.put_child("cleaned", subTreeCleaned);
      tree.put("final.X", pos.x);
      tree.put("final.y", pos.y);
      tree.put("final.facing", direction);
      tree.put("battery", battery);
      pt::json_parser::write_json(filename, tree);
    }catch(pt::json_parser_error & e)
    {
      throw InvalidData(filename, e.what());
    }

  }


  void JsonParser::parseAndValidateData(const std::string & file){
    battery = jsonTree.get<int>("battery", -1);
    startPoint_x = jsonTree.get<int>("start.X", -1);
    startPoint_y = jsonTree.get<int>("start.Y", -1);
    char facing = jsonTree.get<char>("start.facing", '0');
    
    if(battery <= -1){
      throw InvalidJsonFile(file, "bad value battery");
    }

    if(startPoint_x <= -1 || startPoint_y <=-1 || !isValidDirection(facing)){
      throw InvalidJsonFile(file, "bad value start position");
    }else{
      direction = (Direction)facing;
    }
    readCommandList(file);
    readMap(file);
  }

  void JsonParser::readCommandList(const std::string & file){
    BOOST_FOREACH(pt::ptree::value_type &v, jsonTree.get_child("commands")){
      try
      {
        commands.add(v.second.data());
      }catch(InvalidCommand &e)
      {
        throw InvalidJsonFile(file, e.getError());
      }
    }
  }

  void JsonParser::readMap(const std::string & file){
    int width = 0;
    
    BOOST_FOREACH(pt::ptree::value_type &v, jsonTree.get_child("map"))
    {
        std::vector<Cell> cells;

        for (pt::ptree::value_type &cell : v.second)
        {
          try{
            std::string s = (std::string)cell.second.get_value<std::string>();
            Cell c = map.isValidCell(s);
            cells.push_back(c);
          }catch(InvalidCell &e)
          {
            throw InvalidJsonFile(file, e.getError());
          }
        }
        if(!cells.empty())
        {
          map.addCells(cells);
          if(map.getLength() <=0)
          {
            map.setLength(cells.size());
          }
        }
    }
    map.setWidth(map.size());
  }

  void JsonParser::writeSet(const std::set<Position> & set, const std::string & name,
     pt::ptree & tree, const std::string & file)
  {
    std::for_each(set.begin(), set.end(), [&tree](const Position & pos){
        pt::ptree position, subTree;
        position.put("X", pos.x);
        position.put("Y", pos.y);
        //subTree.push_back(std::make_pair("", position));
        tree.push_back(std::make_pair("", position));
        //tree.put("", pos);
    });
  }
}