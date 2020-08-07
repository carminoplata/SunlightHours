#include <exception>
#include <iostream>
#include <string>

namespace parser
{
  class InvalidJsonFile : public std::exception
  {
  private:
    std::string filename;
    std::string message;

  public:
    InvalidJsonFile(){}
    InvalidJsonFile(const std::string & filename, const std::string message)
      : filename{filename}
      , message{message}
    {
    }

    ~InvalidJsonFile(){}
    void printError()
    {
      std::cout << "Error parsing file " << filename << ": " << message << std::endl;
    }
  };

  class InvalidData : public std::exception
  {
  private:
    std::string filename;
    std::string message;

  public:
    InvalidData(){}
    InvalidData(const std::string & filename, const std::string message)
      : filename{filename}
      , message{message}
    {
    }

    ~InvalidData(){}
    void printError()
    {
      std::cout << "Impossible generate " << filename << ": " << message << std::endl;
    }
  };
}

