#include "Star.h"

Star::Star() : Figure() { radius = 0; }

Star::Star(int rad, sf::Color clr, sf::Vector2f pos)
    : Figure(rad * 2, rad * 2, clr, pos) {
  radius = rad;
  vertex_count = 10;
  initialize_vertices();
}

Figure *Star::clone() { return new Star(*this); }

void Star::deform() {
  int vertex_id;

  vertex_id = rand() % vertex_count;
  vertices[vertex_id].position.y += 10;
  vertex_id = rand() % vertex_count;
  vertices[vertex_id].position.x -= 20;
  vertex_id = rand() % vertex_count;
  vertices[vertex_id].position.y -= 20;
  vertex_id = rand() % vertex_count;
  vertices[vertex_id].position.x += 10;
}

std::string Star::to_string() {
  return "5-" + std::to_string(radius) + "-" + std::to_string(default_color.r) +
         "," + std::to_string(default_color.g) + "," +
         std::to_string(default_color.b) + "-" +
         std::to_string((int)position.x) + "," +
         std::to_string((int)position.y);
}

void Star::from_string(std::string str) {
  char *cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());
  if (atoi(strtok(cstr, "-")) != 5)
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
  vertex_count = 10;

  initialize_vertices();
}

void Star::initialize_vertices() {
  vertices = new sf::Vertex[vertex_count];

  auto deg = 90;
  for (int i = 0; i < vertex_count; i += 2) {
    auto offset = sf::Vector2f(radius, radius);
    offset.x *= cos(deg * 3.14 / 180);
    offset.y *= sin(deg * 3.14 / 180);
    vertices[i] =
        sf::Vertex(position + sf::Vector2f(offset.x / 2, offset.y / 2), color);
    deg -= 72;
  }
  deg = 54;
  for (int i = 1; i < vertex_count; i += 2) {
    auto offset = sf::Vector2f(radius, radius);
    offset.x *= cos(deg * 3.14 / 180);
    offset.y *= sin(deg * 3.14 / 180);
    vertices[i] = sf::Vertex(position + offset, color);
    deg -= 72;
  }
}
