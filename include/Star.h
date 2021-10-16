#pragma once

#include "Figure.h"

class Star : public Figure {
  int radius;

public:
  Star();
  Star(int, sf::Color, sf::Vector2f);
  virtual Figure *clone() override;
  virtual void deform() override;
  virtual std::string to_string() override;
  virtual void from_string(std::string) override;
  virtual void initialize_vertices() override;
};
