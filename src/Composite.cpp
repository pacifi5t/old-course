#include "Composite.h"

Composite::Composite() : Figure() { figures = new std::vector<Figure *>(); }

Composite::~Composite() {
  figures->clear();
  delete figures;
}

void Composite::add_shape(Figure *shape) { figures->push_back(shape); }

void Composite::remove_shape(Figure *shape) {
  int i = 0;
  for (auto elem : *figures) {
    if (elem == shape) {
      figures->erase(figures->begin() + i);
      break;
    }
    i++;
  }
}

bool Composite::selected() {
  for (auto elem : *figures) {
    if (elem->selected())
      return true;
  }
  return false;
}

bool Composite::crossed_border() {
  for (auto elem : *figures) {
    if (elem->crossed_border())
      return true;
  }
  return false;
}

void Composite::change_visibility() {
  for (auto elem : *figures) {
    elem->change_visibility();
  }
}

bool Composite::intersects(Figure *other) {
  for (auto elem : *figures) {
    if (elem->intersects(other))
      return true;
  }
  return false;
}

bool Composite::hover(sf::Vector2i mouse_pos) {
  for (auto elem : *figures) {
    if (elem->hover(mouse_pos))
      return true;
  }
  return false;
}

void Composite::move(sf::Vector2f offset) {
  for (auto elem : *figures) {
    elem->move(offset);
  }
}

void Composite::move_round(int deg, sf::Vector2f offset) {
  for (auto elem : *figures) {
    elem->move_round(deg, offset);
  }
}

void Composite::set_selection() {
  for (auto elem : *figures) {
    elem->set_selection();
  }
}

void Composite::set_default_color() {
  for (auto elem : *figures) {
    elem->set_default_color();
  }
}

void Composite::set_reversed_color() {
  for (auto elem : *figures) {
    elem->set_reversed_color();
  }
}

Figure *Composite::clone() { return new Composite(*this); }

void Composite::deform() {
  for (auto elem : *figures) {
    elem->deform();
  }
}

void Composite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (auto &elem : *figures) {
    if (elem->to_string()[0] == '0') {
      elem->draw(target, states);
    }
    target.draw(elem->vertices, elem->vertex_count, sf::TriangleFan, states);
  }
}

std::string Composite::to_string() {
  std::string output = "0-" + std::to_string(figures->size()) + ":";
  for (auto &elem : *figures) {
    output += elem->to_string();
    if (elem->to_string()[0] != '0')
      output += "/";
  }
  output += ';';
  return output;
}

void Composite::from_string(std::string str) {
  char *cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());
  int size = atoi(cstr + 2);
  char *block_start = cstr + 4;
  std::string block(block_start, str.size() - 5);
  char *temp = new char[block.length() + 1];
  strcpy(temp, block.c_str());
  delete[] cstr;

  for (int i = 0; i < size; i++) {
    int temp_size = 0;
    Figure *shape = nullptr;
    if (temp[0] == '0') {
      for (; temp[temp_size] != ';'; temp_size++)
        ;
      temp_size++;

      shape = new Composite();
    } else {
      for (; temp[temp_size] != '/'; temp_size++)
        ;
      temp_size++;

      switch (temp[0]) {
      case '1':
        shape = new Circle();
        break;
      case '2':
        shape = new Ellipse();
        break;
      case '3':
        shape = new Triangle();
        break;
      case '4':
        shape = new Rectangle();
        break;
      case '5':
        shape = new Star();
        break;
      case '6':
        shape = new Hexagon();
        break;
      }
    }
    shape->from_string(std::string(temp, temp_size));
    temp += temp_size;
    add_shape(shape);
  }
}