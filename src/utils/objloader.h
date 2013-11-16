#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "../graphics/vbo.h"

class Objloader
{
public:
  Objloader();
  VBO readObj(std::string);

private:
  void preProcess(std::string);
  std::vector<std::string> vertices;
  std::vector<std::string> indexes;
};


#endif  /* OBJLOADER_H */
