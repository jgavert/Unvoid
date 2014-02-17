#pragma once
#include <string>
#include <fstream>

class ShaderParser
{
public:
  static std::string process(std::string input);
private:
  static std::string parseShaderForComments(std::string unparsed);
};

