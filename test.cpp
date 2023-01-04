#include <gtest/gtest.h>

#include "ModelReader.h"
#include "affine.h"

#define EPS 1e-5

TEST(test, full_test) {
  Model model, standard_model;
  s21::ModelReader pars;
  model = pars.Read("test_cube.obj");
  standard_model = pars.Read("transformed_cube.obj");
  ASSERT_EQ(model.vertices.size(), standard_model.vertices.size());
  ASSERT_EQ(model.polygons.size(), standard_model.polygons.size());
  s21::Strategy affine;
  affine.SetStrategy(new s21::Scale);
  affine.Work(model.vertices, 15, 15, 15);
  affine.SetStrategy(new s21::Rotate);
  affine.Work(model.vertices, M_PI_4, M_PI_4, M_PI_4);
  affine.SetStrategy(new s21::Move);
  affine.Work(model.vertices, 3, -5, 7);

  for (size_t i = 0; i < model.vertices.size(); i++) {
    ASSERT_FLOAT_EQ(model.vertices[i], standard_model.vertices[i]);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
