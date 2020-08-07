#include "Exception.h"
#include <ParserManager.h>
#include <ParserException.h>
#include <Robot.h>
#include <RobotException.h>
#include <iostream>

void validateInput(int argc ,char* argv[], std::string & source, std::string & result)
{
  if(argc != 3)
  {
    throw InvalidArgument("Run: cleaning_robot <path_to_source.json> <path_to_result.json>");
    exit(-1);
  }
  source = std::move(argv[1]);
  result = std::move(argv[2]);
  if(source.substr(source.size()-4) != "json"){
    throw InvalidArgument("Error: invalid source file. Required json file");
  }

  if(result.substr(result.size()-4) != "json"){
    throw InvalidArgument("Error: invalid source file. Required json file");
  }
}

int main(int argc , char* argv[])
{
  std::cout << "Hello, CleaningRobot!\n";

  try {
    std::string source, result;
    validateInput(argc, argv, source, result);
    std::cout << "Load data from " << source << std::endl;
    parser::ParserManager manager;
    manager.parse(source);
    std::cout << "Loading completed!" << std::endl;
    std::cout << "Initializing Cleaning Robot..." << std::endl;
    cleaning_robot::Robot robot( manager.getBattery(), manager.getPositionX(),
      manager.getPositionY(), manager.getDirection());
    robot.printInfo();
    robot.setBackOffStrategy(backoffStrategy);
    std::cout << "Back Off Strategy loaded!" << std::endl; 
    Room room  = manager.getRoom();
    CommandList commands = manager.getCommands();
    std::cout << "Cleaning the room..." << std::endl;
    robot.run(room, commands);
    std::cout << "Completed with success" << std::endl;
    cleaning_robot::State finalState = robot.getState();
    char direction = (char)finalState.direction;
    manager.write(result, robot.getVisited(), robot.getCleaned(), finalState.position, direction,
      robot.getBattery());

  }catch(InvalidArgument & e)
  {
    std::cout << "Error: " << e.what() << std::endl;
    exit(-1);
  }catch(parser::InvalidJsonFile & e)
  {
    e.printError();
    exit(-1);
  }catch(RobotIsOutOfPower & e)
  {
    std::cout << e.getError() << std::endl;
  }catch(RobotStuck & e)
  {
    std::cout << e.getError() << std::endl;
  }catch(InvalidInput& e)
  {
    std::cout << e.getError() << std::endl;
  }catch(parser::InvalidData & e)
  {
    e.printError();
  }
}