#ifndef SETTINGS_PARSER_H
#define SETTINGS_PARSER_H

#include <QColor>
#include <QString>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

namespace s21 {
enum Projection { kCentral, kParallel };
enum EdgType { kSolid, kDashed };
enum VerType { kInvisible, kCircle, kSquare };
class SettingsParser {
  SettingsParser();
  SettingsParser(const SettingsParser &) = delete;
  SettingsParser(SettingsParser &&) = delete;
  SettingsParser &operator=(const SettingsParser &) = delete;
  SettingsParser &operator=(SettingsParser &&) = delete;
  void settingsProjection();
  void settingsVertType();
  void settingsColorEdg();
  void settingsEdgThick();
  void settingsEdgMethod();
  void settingsColorVert();
  void settingsSizeVert();
  void settingsColorBack();

  static constexpr char kProj[] = "Projection:";
  static constexpr char kProjCentral[] = "central";
  static constexpr char kProjParallel[] = "parallel";
  static constexpr char kVerType[] = "VerticesType:";
  static constexpr char kVerTypeCircle[] = "circle";
  static constexpr char kVerTypeSquare[] = "square";
  static constexpr char kVerSize[] = "VerticesSize:";
  static constexpr char kVerCol[] = "VerticesColor:";
  static constexpr char kDefVerCol[] = "#000000";
  static constexpr char kEdgType[] = "EdgesType:";
  static constexpr char kEdgTypeSolid[] = "solid";
  static constexpr char kEdgTypeDashed[] = "dashed";
  static constexpr char kEdgSize[] = "EdgesSize:";
  static constexpr char kEdgCol[] = "EdgesColor:";
  static constexpr char kDefEdgCol[] = "#000000";
  static constexpr char kBackCol[] = "BackgroundColor:";
  static constexpr char kDefBackCol[] = "#ffffff";
  inline static SettingsParser *instance_ = nullptr;
  static std::string settings_file_;
  std::fstream file_;

 public:
  ~SettingsParser();
  struct Settings {
    bool projection;  // 0-central, 1-parallel
    bool edges_type;  // 0-solid 1-dashed
    char edges_size;
    char vert_type;  // 0-nan 1-circle 2-square
    char vert_size;
    QColor edges_col;
    QColor vert_col;
    QColor back_col;
    Settings()
        : projection(kCentral),
          edges_type(kSolid),
          edges_size(1),
          vert_type(kCircle),
          vert_size(1),
          edges_col(Qt::black),
          vert_col(Qt::black),
          back_col(Qt::white) {}
  } settings_;
  static SettingsParser *GetInstance();
  void parsFileSavedSettings();
  Settings &GetSettings();
  void SaveSettings(std::fstream &setFile);
};

}  // namespace s21
#endif  // SETTINGS_PARSER_H
