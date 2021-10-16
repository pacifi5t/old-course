#include "Figure.h"

sf::RenderStates states = sf::RenderStates();

void Figure::initialize_vertices() { vertices = nullptr; }

Figure::Figure() {
  height = 0;
  width = 0;
  color = sf::Color::White;
  vertex_count = 0;
  default_color = sf::Color::White;
  reversed_color = sf::Color::Black;
}

Figure::Figure(int h, int w, sf::Color clr, sf::Vector2f pos) {
  height = h;
  width = w;
  color = clr;
  position = pos;
  vertex_count = 0;
  default_color = clr;
  reversed_color = sf::Color::White - default_color;
  reversed_color.a = 255;
}

Figure::~Figure() { delete[] vertices; }

bool Figure::crossed_border() {
  sf::Vector2u window_size = Viewport::get_window()->getSize();

  if (position.x - width / 2 < 0 || position.x + width / 2 > window_size.x ||
      position.y - height / 2 < 0 || position.y + height / 2 > window_size.y)
    return true;
  else
    return false;
}

bool Figure::hover(sf::Vector2i m_pos) {
  if (m_pos.x < position.x + width / 2 && m_pos.x > position.x - width / 2 &&
      m_pos.y < position.y + height / 2 && m_pos.y > position.y - height / 2)
    return true;
  else
    return false;
}

bool Figure::intersects(Figure *other) {
  if (other->to_string()[0] == '0')
    return other->intersects(this);

  sf::Vector2f delta = sf::Vector2f(
      position.x - other->position.x,
      position.y - other->position.y);
  sf::Vector2f distance = sf::Vector2f(
      fabs(delta.x) - (other->width / 2 + width / 2),
      fabs(delta.y) - (other->height / 2 + height / 2));

  if (distance.x < 0 && distance.y < 0)
    return true;
  else
    return false;
}

void Figure::change_visibility() {
  color.a = fabs(color.a - 255);
  for (int i = 0; i < vertex_count; i++)
    vertices[i].color.a = color.a;
}

void Figure::move_round(int deg, sf::Vector2f ofs) {
  sf::Vector2f offset(
      ofs.x * cos(deg * 3.14 / 180),
      ofs.y * sin(deg * 3.14 / 180));
  move(offset);
  if (crossed_border())
    move(-offset);
}

sf::Color Figure::get_color() { return color; }

sf::Vector2f Figure::get_position() { return position; }

int Figure::get_height() { return height; }

int Figure::get_width() { return width; }

int Figure::get_vertex_count() { return vertex_count; }

void Figure::get_memento(Memento &mem) { from_string(mem.state); }

void Figure::set_default_color() {
  color.r = default_color.r;
  color.g = default_color.g;
  color.b = default_color.b;
  for (int i = 0; i < vertex_count; i++) {
    vertices[i].color = color;
  }
}

void Figure::set_reversed_color() {
  color.r = reversed_color.r;
  color.g = reversed_color.g;
  color.b = reversed_color.b;

  for (int i = 0; i < vertex_count; i++) {
    vertices[i].color = color;
  }
}

void Figure::set_selection() { is_selected = true; }
void Figure::set_memento(Memento &mem) { mem.state = to_string(); }

bool Figure::selected() { return is_selected; }

void Figure::move(sf::Vector2f offset) {
  if (is_selected) {
    position += offset;
    for (int i = 0; i < vertex_count; i++) {
      vertices[i].position += offset;
    }
  }
}

void Figure::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(vertices, vertex_count, sf::TriangleFan, states);
}