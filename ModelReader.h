#ifndef MODELREADER_H
#define MODELREADER_H

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

struct Model {
  std::vector<unsigned int> polygons;
  std::vector<double> vertices;
};

namespace s21 {
class ModelReader {
public:
  ModelReader(){};
  ~ModelReader(){};
  Model Read(std::string file);

private:
  int CountV(std::ifstream &file);
  int CountF(std::ifstream &file);
  void Reset(std::ifstream &file);
};
} // namespace s21

#endif // MODELREADER_H_
