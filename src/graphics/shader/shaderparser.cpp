#include "shaderparser.hpp"

std::string ShaderParser::process(std::string filename)
{
  std::string ShaderString = "";
  std::ifstream shaderFile;
  shaderFile.open(filename);
  while(!shaderFile.eof())
  {
    std::string tempholder;
    getline(shaderFile, tempholder);
    ShaderString += tempholder + "\n";
  }
  shaderFile.close();
  auto parsed = parseShaderForComments(ShaderString);
  return parsed;
}

std::string ShaderParser::parseShaderForComments(std::string unparsed)
{
  bool start = false;
  std::string parsed;
  for (unsigned i = 0; i<unparsed.length(); i++){
    if (unparsed[i] == '/')
      if (unparsed[i+1] == '*') {
        start = true;
        i+=1;
        continue;
      }
    if (unparsed[i] == '*')
      if (unparsed[i+1] == '/'){
        start = false;
        i+=1;
        continue;
      }
    if (start)
      continue;
    parsed += unparsed[i];
  }
  return parsed;
}
