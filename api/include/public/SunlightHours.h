#include <string>
#include <ParserManager.h>

class SunlightHours
{
private:
  ParserManager manager;

public:
  SunlightHours() = default;
  ~SunlightHours();
  SunlightHours(const SunlightHours & hours) = delete;
  SunlightHours & operator=(const SunlightHours& hours) = delete;
  SunlightHours(const SunlightHours&& hours);
  SunlightHours & operator=(const SunlightHours&& hours);
  void init(const std::string & filename);
  std::string getSunlightHours(const std::string & neighbourhood, const std::string & building, int apt);

private:
  void loadFile(std::string filename);
  bool isValidFile(const std::string & filename);
};
