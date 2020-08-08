#include <exception>
#include <iostream>
#include <string>

class InvalidFile : public std::exception {
 private:
  std::string filename;
  std::string message;

 public:
  InvalidFile() {}
  InvalidFile(const std::string& filename, const std::string message)
      : filename{filename}, message{message} {}

  ~InvalidFile() {}
  void printError() {
    std::cout << "Error parsing file " << filename << ": " << message
              << std::endl;
  }
};
