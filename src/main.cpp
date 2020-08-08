#include "Exception.h"

#include <SunlightHours.h>
#include <SunlightHoursException.h>

#include <iostream>

void validateInput(int argc ,char* argv[], std::string & source)
{
  if(argc != 2)
  {
    throw InvalidArgument("Run: sunlightHours <path_to_source.json> ");
    exit(-1);
  }
  source = std::move(argv[1]);
}

int main(int argc , char* argv[])
{
  std::cout << "Hello, SunlightHours!\n";

  try {
    std::string source;
    validateInput(argc, argv, source);
    std::cout << "Load data from " << source << std::endl;
    SunlightHours processHours;

    processHours.init(source);
    std::cout << "Loading completed!" << std::endl;
  }catch(InvalidFile & e)
  {
    e.printError();
  }
}