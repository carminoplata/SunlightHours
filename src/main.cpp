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
  try {
    std::string source;
    validateInput(argc, argv, source);
    std::cout << "Loadind data from " << source <<  "..." << std::endl;
    SunlightHours processHours;
    processHours.init(source);
    std::cout << "Loading completed!" << std::endl;
    std::cout << "Sunlight Hours for building Aticco apt 5: "; 
    std::cout << processHours.getSunlightHours("Poblenou", "Aticco", 5) << std::endl;
    std::cout << "Sunlight Hours for building 01 apt 1: ";
    std::cout << processHours.getSunlightHours("Poblenou", "01", 1) << std::endl;
    std::cout << "Sunlight Hours for building Aticco apt 7: ";
    std::cout << processHours.getSunlightHours("Poblenou", "Aticco", 7) << std::endl;
    std::cout << "Sunlight Hours for building 30 apt 0: ";
    std::cout << processHours.getSunlightHours("Poblenou", "30", 0) << std::endl;
    std::cout << "Sunlight Hours for building CEM apt 5: ";
    std::cout << processHours.getSunlightHours("Poblenou", "CEM", 5) << std::endl;
    
  }catch(InvalidFile & e){
    e.printError();
  }catch(InvalidInput & e){
    e.printError();
  }
}