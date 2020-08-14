#include <exception>
#include <iostream>
#include <sstream>
#include <string>

  class InvalidJsonFile : public std::exception
  {
  private:
    std::string filename;
    std::string message;

  public:
    InvalidJsonFile(){}
    InvalidJsonFile(const std::string & filename, const std::string & message)
      : filename{filename}
      , message{message}
    {
    }

    ~InvalidJsonFile(){}
    std::string getError()
    {
      std::stringstream ss;
      ss << "Error parsing file " << filename << ": " << message;
      return ss.str();
    }
  };

  class InvalidData : public std::exception
  {
  private:
    std::string filename;
    std::string message;
    std::string field;

  public:
    InvalidData(){}
    InvalidData(const std::string & filename, const std::string & message, const std::string & field)
      : filename{filename}
      , message{message}
      , field{field}
    {
    }

    ~InvalidData(){}
    std::string getError()
    {
      std::stringstream ss;
      ss << message << field;
      return ss.str();
    }
  };


