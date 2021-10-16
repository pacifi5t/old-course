#pragma once

#include "Figure.h"

class Circle : public Figure {
  int radius;

public:
  Circle();
  Circle(int, sf::Color, sf::Vector2f);
  virtual Figure *clone() override;
  virtual void deform() override;
  virtual std::string to_string() override;
  virtual void from_string(std::string) override;
  virtual void initialize_vertices() override;
};
