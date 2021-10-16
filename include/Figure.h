#pragma once

#include "Memento.h"
#include "Viewport.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstring>

using sf::RenderTarget, sf::RenderStates;

class Figure : public sf::Drawable {
  friend class Composite;

  virtual void initialize_vertices();

protected:
  bool is_selected = 0;
  int height;
  int width;
  sf::Color color;
  sf::Color default_color;
  sf::Color reversed_color;
  sf::Vector2f position;
  int vertex_count;
  sf::Vertex *vertices = nullptr;
  static sf::RenderStates states;

public:
  Figure();
  Figure(int, int, sf::Color, sf::Vector2f);
  virtual ~Figure();
  sf::Color get_color();
  sf::Vector2f get_position();
  int get_height();
  int get_width();
  int get_vertex_count();
  void get_memento(Memento &);
  void set_memento(Memento &);
  virtual bool selected();
  virtual bool crossed_border();
  virtual void change_visibility();
  virtual bool hover(sf::Vector2i);
  virtual bool intersects(Figure *);
  virtual void move(sf::Vector2f);
  virtual void move_round(int, sf::Vector2f);
  virtual void set_default_color();
  virtual void set_reversed_color();
  virtual void set_selection();
  virtual Figure *clone() = 0;
  virtual void deform() = 0;
  virtual std::string to_string() = 0;
  virtual void from_string(std::string) = 0;
  virtual void draw(RenderTarget &target, RenderStates states) const;
};