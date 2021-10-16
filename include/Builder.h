#pragma once

#include "Circle.h"
#include "Ellipse.h"
#include "Hexagon.h"
#include "Rectangle.h"
#include "Star.h"
#include "Triangle.h"

#include <iostream>

class Builder {
public:
  Figure *build_object();

private:
  std::string get_data();
  std::string input_to_valid_string(std::string);
  bool wrong_string(char *);
};
