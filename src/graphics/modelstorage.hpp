#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include "modeldata.hpp"

class ModelStorage
{
public:
  ModelStorage();
  ~ModelStorage();
  void addModel(std::string name, std::string filename);
  int getModel(std::string name);
  int getVao(int id);
  int getModelSize(int id);

private:
  std::unique_ptr<ModelData> parseFile(std::string filename);
  std::map<std::string, int> nametomodel;
  std::vector<std::unique_ptr<ModelData>> models;
};


