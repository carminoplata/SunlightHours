#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class InvalidArgument : std::exception
{
  private:
    std::string message;
  
  public:
    InvalidArgument(const char * message) : message(message) {}

    virtual const char* what() const throw()
    {
      return message.c_str();
    }
};



#endif