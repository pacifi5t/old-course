#include "Circle.h"

Circle::Circle() : Figure() { radius = 0; }

Circle::Circle(int rad, sf::Color clr, sf::Vector2f pos)
    : Figure(rad * 2, rad * 2, clr, pos) {
  radius = rad;
  vertex_count = 36;
  initialize_vertices();
}

Figure *Circle::clone() { return new Circle(*this); }

void Circle::deform() {
  int vertex_id;
  for (int i = 0; i < 2; i++) {
    vertex_id = rand() % vertex_count;
    vertices[vertex_id].position.y += 10;
    vertex_id = rand() % vertex_count;
    vertices[vertex_id].position.x -= 20;
    vertex_id = rand() % vertex_count;
    vertices[vertex_id].position.y -= 20;
    vertex_id = rand() % vertex_count;
    vertices[vertex_id].position.x += 10;
  }
}

std::string Circle::to_string() {
  return "1-" + std::to_string(radius) + "-" + std::to_string(default_color.r) +
         "," + std::to_string(default_color.g) + "," +
         std::to_string(default_color.b) + "-" +
         std::to_string((int)position.x) + "," +
         std::to_string((int)position.y);
}

void Circle::from_string(std::string str) {
  char *cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());
  if (atoi(strtok(cstr, "-")) != 1)
    return;
  radius = atoi(strtok(nullptr, "-"));
  color.r = atoi(strtok(nullptr, ","));
  color.g = atoi(strtok(nullptr, ","));
  color.b = atoi(strtok(nullptr, "-"));
  position.x = atoi(strtok(nullptr, ","));
  position.y = atoi(strtok(nullptr, "-"));
  delete[] cstr;

  width = radius * 2;
  height = radius * 2;
  default_color = color;
  reversed_color = sf::Color::White - color;
  reversed_color.a = 255;
  vertex_count = 36;

  initialize_vertices();
}

void Circle::initialize_vertices() {
  vertices = new sf::Vertex[vertex_count];

  auto deg = 0;
  for (int i = 0; i < vertex_count; i++) {
    auto offset = sf::Vector2f(radius, radius);
    offset.x *= cos(deg * 3.14 / 180);
    offset.y *= sin(deg * 3.14 / 180);
    vertices[i] = sf::Vertex(position + offset, color);
    deg += 360 / vertex_count;
  }
}
