#include "ModelReader.h"

namespace s21 {
int ModelReader::CountF(std::ifstream &fileReader) {
  char *tok;
  int countTokenF = 0;
  std::string myline;
  Reset(fileReader);
  while (!fileReader.eof()) {
    std::getline(fileReader, myline);
    if (!strncmp("f ", myline.c_str(), (size_t)2)) {
      tok = strtok(myline.data(), "f \n");
      while (tok != NULL) {
        tok = strtok(NULL, " f\n");
        countTokenF++;
      }
    }
  }
  return countTokenF;
}

int ModelReader::CountV(std::ifstream &fileReader) {
  int countV = 0;
  std::string myline;
  Reset(fileReader);
  while (!fileReader.eof()) {
    std::getline(fileReader, myline);
    if (!strncmp("v ", myline.c_str(), (size_t)2)) {
      countV++;
    }
  }
  return countV;
}

void ModelReader::Reset(std::ifstream &fileReader) {
  fileReader.clear();
  fileReader.seekg(0);
}

Model ModelReader::Read(std::string nameFiles) {
  Model figure;
  std::ifstream fileReader(nameFiles, std::ifstream::in);
  std::string myline;

  if (fileReader.is_open()) {
    char *token;
    figure.polygons.reserve(CountF(fileReader) * 2);
    figure.vertices.reserve(CountV(fileReader) * 3);
    Reset(fileReader);
    while (!fileReader.eof()) {
      std::getline(fileReader, myline);
      if (!strncmp("f ", myline.c_str(), (size_t)2)) {
        token = std::strtok(myline.data(), "f \n");
        int first = std::stoul(token) - 1;
        int last = first;
        while ((token = strtok(NULL, " \nf"))) {
          int cur = std::stoul(token) - 1;
          figure.polygons.push_back(last);
          figure.polygons.push_back(cur);
          last = cur;
        }
        figure.polygons.push_back(last);
        figure.polygons.push_back(first);
      } else if (!strncmp("v ", myline.c_str(), (size_t)2)) {
        token = strtok(myline.data(), "v \n");
        while (token != NULL) {
          figure.vertices.push_back(atof(token));
          token = strtok(NULL, "v \n");
        }
      }
    }
  }
  return figure;
}
} // namespace s21
