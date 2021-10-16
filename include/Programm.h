#pragma once

#include "Builder.h"
#include "Composite.h"
#include "Figure.h"
#include "Viewport.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Programm {
public:
  static const int VELOCITY;
  static bool trail_enabled;
  static int degrees;

  static void build_new_figure(std::vector<Figure *> &);
  static void change_visibility(std::vector<Figure *> &);
  static void deform(std::vector<Figure *> &);
  static void add_to_composite(std::vector<Figure *> &);
  static void display_start_msg();
  static void check_collisions(std::vector<Figure *> &);
  static void handle_input(Viewport *, std::vector<Figure *> &, sf::Vector2f &);
  static void move_shapes(std::vector<Figure *> &, sf::Vector2f);
  static void select_shape(std::vector<Figure *> &, sf::Vector2i);
  static void deselect_shape(std::vector<Figure *> &, sf::Vector2i);
  static void save_start(std::vector<Figure *> &);
  static void save_checkpoint(std::vector<Figure *> &);
  static void load_start(std::vector<Figure *> &);
  static void load_checkpoint(std::vector<Figure *> &);
};