#include "SettingsParser.h"

namespace s21 {

SettingsParser::SettingsParser() {
  file_.open(settings_file_, std::fstream::in);
}

SettingsParser::~SettingsParser() {
  file_.close();
  file_.open(settings_file_, std::fstream::out);
  SaveSettings(file_);
  file_.close();
}

SettingsParser *SettingsParser::GetInstance() {
  if (!instance_)
    instance_ = new SettingsParser();
  return instance_;
}

SettingsParser::Settings &SettingsParser::GetSettings() { return settings_; }

void SettingsParser::settingsProjection() {
  char *token = strtok(nullptr, ":");
  if (!strncmp(kProjCentral, token, sizeof(kProjCentral))) {
    settings_.projection = kCentral;
  } else {
    settings_.projection = kParallel;
  }
}

void SettingsParser::settingsEdgMethod() {
  char *token = strtok(nullptr, ":");
  if (!strncmp(kEdgTypeSolid, token, sizeof(kEdgTypeSolid))) {
    settings_.edges_type = kSolid;
  } else {
    settings_.edges_type = kDashed;
  }
}

void SettingsParser::settingsColorEdg() {
  char *token = strtok(nullptr, ":");
  if (token[0] == '#') {
    settings_.edges_col.setNamedColor(token);
  } else {
    settings_.edges_col.setNamedColor(kDefEdgCol);
  }
}

void SettingsParser::settingsEdgThick() {
  char *token = strtok(nullptr, ":");
  if (!token || !atoi(token)) {
    settings_.edges_size = 1;
  } else {
    settings_.edges_size = atoi(token);
  }
}

void SettingsParser::settingsVertType() {
  char *token = strtok(nullptr, ":");
  if (!strncmp("none", token, 4)) {
    settings_.vert_type = kInvisible;
  } else if (!strncmp(kVerTypeCircle, token, sizeof(kVerTypeCircle))) {
    settings_.vert_type = kCircle;
  } else {
    settings_.vert_type = kSquare;
  }
}

void SettingsParser::settingsColorVert() {
  char *token = strtok(nullptr, ":");
  if (token[0] == '#') {
    settings_.vert_col.setNamedColor(token);
  } else {
    settings_.vert_col.setNamedColor(kDefVerCol);
  }
}

void SettingsParser::settingsSizeVert() {
  char *token = strtok(nullptr, ":");
  if (!token || !atoi(token)) {
    settings_.vert_size = 1;
  } else {
    settings_.vert_size = atoi(token);
  }
}

void SettingsParser::settingsColorBack() {
  char *token = strtok(nullptr, ":");
  if (token[0] == '#') {
    settings_.back_col.setNamedColor(token);
  } else {
    settings_.back_col.setNamedColor(kDefBackCol);
  }
}

void SettingsParser::parsFileSavedSettings() {
  if (file_.is_open()) {
    std::string line;
    for (std::getline(file_, line); !file_.eof(); std::getline(file_, line)) {
      char *token = std::strtok(&line[0], ":");
      if (!strncmp(kProj, token, sizeof(kProj) - 2)) {
        settingsProjection();
      } else if (!strncmp(kVerType, token, sizeof(kVerType) - 2)) {
        settingsVertType();
      } else if (!strncmp(kEdgCol, token, sizeof(kEdgCol) - 2)) {
        settingsColorEdg();
      } else if (!strncmp(kEdgSize, token, sizeof(kEdgSize) - 2)) {
        settingsEdgThick();
      } else if (!strncmp(kEdgType, token, sizeof(kEdgType) - 2)) {
        settingsEdgMethod();
      } else if (!strncmp(kVerCol, token, sizeof(kVerCol) - 2)) {
        settingsColorVert();
      } else if (!strncmp(kVerSize, token, sizeof(kVerSize) - 2)) {
        settingsSizeVert();
      } else if (!strncmp(kBackCol, token, sizeof(kBackCol) - 2)) {
        settingsColorBack();
      }
    }
  }
}

void SettingsParser::SaveSettings(std::fstream &file) {
  if (settings_.projection == kCentral) {
    file << kProj << kProjCentral << '\n';
  } else {
    file << kProj << kProjParallel << '\n';
  }

  if (settings_.edges_type == kSolid) {
    file << kEdgType << kEdgTypeSolid << '\n';
  } else {
    file << kEdgType << kEdgTypeDashed << '\n';
  }

  if (settings_.edges_size) {
    file << kEdgSize << static_cast<int>(settings_.edges_size) << '\n';
  } else {
    file << kEdgSize << 1 << '\n';
  }

  if (settings_.vert_size) {
    file << kVerSize << static_cast<int>(settings_.vert_size) << '\n';
  } else {
    file << kVerSize << 1 << '\n';
  }

  if (settings_.vert_type == kSquare) {
    file << kVerType << kVerTypeSquare << '\n';
  } else if (settings_.vert_type == kCircle) {
    file << kVerType << kVerTypeCircle << '\n';
  } else {
    file << kVerType << "none" << '\n';
  }

  file << kVerCol << settings_.vert_col.name(QColor::HexRgb).toStdString()
       << '\n';
  file << kEdgCol << settings_.edges_col.name(QColor::HexRgb).toStdString()
       << '\n';
  file << kBackCol << settings_.back_col.name(QColor::HexRgb).toStdString()
       << '\n';
}
} // namespace s21
