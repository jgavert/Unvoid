#include "objloader.h"

Objloader::Objloader()
{
  vertices = std::vector<std::string>();
  indexes = std::vector<std::string>();
}

VBO Objloader::readObj(std::string FileName)
{
  std::string objString = "";
  std::ifstream objFile;
  objFile.open(FileName);
  while(!objFile.eof())
  {
    std::string tempholder;
    getline(objFile, tempholder);
    objString += tempholder + "\n";
  }
  objFile.close();
  preProcess(objString);
  VBO object;
  object.vertices = std::vector<float>();
  for (std::string asd : vertices)
  {
    bool added = false;
    std::string sfloat = "";
    //float got[3] = {0.0f, 0.0f, 0.0f};
    //int i = 0;
    for (char chr : asd){
      if (chr != ' ' && chr != '\n') {
        sfloat += chr;
        added = true;
      } else {
        if (added) {
          //got[i++] = std::stof(sfloat);
          object.vertices.push_back(std::stof(sfloat));
          sfloat = "";
        }
        added = false;
      }
    }
    //got[i] = std::stod(sfloat);
    object.vertices.push_back(std::stof(sfloat));
    object.vertices.push_back(1.0f);

    //for (float asd : got) {
    //  std::cout << asd << " ";
    //}
    //std::cout << std::endl;
  }

  object.indices = std::vector<GLuint>();
  for (auto asd : indexes)
  {
    bool added = false;
    std::string sfloat = "";
    //int got[3] = {-1, -1, -1};
    //int i = 0;
    for (char chr : asd){
      if (chr != ' ' && chr != '\n') {
        sfloat += chr;
        added = true;
      } else {
        if (added) {
          //got[i++] = std::stoi(sfloat)-1;
          object.indices.push_back(std::stoi(sfloat)-1);
          sfloat = "";
        }
        added = false;
      }
    }
    //got[i] = std::stod(sfloat);
    object.indices.push_back(std::stoi(sfloat)-1);

    //for (float asd : got) {
    //  std::cout << asd << " ";
    //}
    //std::cout << std::endl;
  }
  object.colors = std::vector<float>();
  for (int i=0;i<object.vertices.size();i++)
  {
    object.colors.push_back(1.0f);
  }

  return object;
}

void Objloader::preProcess(std::string process)
{
  bool rewind = false;
  char currentToken = '0';
  std::string current = "";
  for (auto chr : process) {
    if (rewind) {
      if (chr == '\n')  {
        rewind = false;
        if (currentToken == 'v') {
          vertices.push_back(std::string(current));
        } else if ( currentToken == 'f') {
          indexes.push_back(std::string(current));
        }
        currentToken = '0';
        current = "";
      }
      current += chr;
      continue;
    }
    if (chr == 'v') {
      rewind = true;
      currentToken = 'v';
    }
    else if (chr == 'f') {
      currentToken = 'f';
      rewind = true;
    }
    else { rewind = true;}

  }
}
