#include "modelstorage.hpp"


ModelStorage::ModelStorage()
{
}
ModelStorage::~ModelStorage()
{
}
void ModelStorage::addModel(std::string name, std::string filename)
{
  int id = models.size();
  auto p1 = parseFile(filename); //wtf happens if this fails. Out of project scope for now :D
  nametomodel.insert({name, id});
  models.push_back(std::move(p1));
}

// TODO: horribly broken atm, dont use
std::unique_ptr<ModelData> ModelStorage::parseFile(std::string filename)
{
  std::string buf; // Have a buffer string
  std::stringstream ss(filename); // Insert the string into a stream

  std::vector<std::string> tokens; // Create vector to hold our words

  while (ss >> buf) {
    tokens.push_back(buf);
  }

  //std::cout << objectString << std::endl;
  //std::cout << "" << std::endl;
  //std::cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
  //std::cout << "" << std::endl;
  std::vector<GLuint> indices;
  std::vector<float> vertices, colors;
  int itemCount = 3;
  int currentChoice = 0;
  bool end = false;

  for (auto &it: tokens){
    if (it == "ORDER") {
      currentChoice = 1;
      continue;
    }
    else if (it == "VERTICES") {
      currentChoice = 2;
      continue;
    }
    else if (it == "COLORS") {
      currentChoice = 3;
      continue;
    }
    else if (it == "END") {
      currentChoice = 0;
      itemCount--;
      if (itemCount <= 0)
        end = true;
      else
        continue;
    }
    if (end)
      break;

    switch(currentChoice) {
      case 1:
        indices.push_back(static_cast<GLuint>(std::atoi(it.c_str())));
        break;
      case 2:
        vertices.push_back(static_cast<float>(std::atof(it.c_str())));
        break;
      case 3:
        colors.push_back(static_cast<float>(std::atof(it.c_str())));
      default:
        break;
    }
  }
  auto p1 = std::unique_ptr<ModelData>(new ModelData(vertices, colors,indices));
  return std::move(p1);
}

int ModelStorage::getModel(std::string name)
{
  return nametomodel.at(name);
}

int ModelStorage::getVao(int id)
{
  return models.at(id)->getVaoID();
}

int ModelStorage::getModelSize(int id)
{
  return models.at(id)->getSize();
}

