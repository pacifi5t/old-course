#include "Programm.h"

#include "FigureSaver.h"
#include "Rectangle.h"

#include <fstream>
#include <math.h>

const int Programm::VELOCITY = 2;
bool Programm::trail_enabled = 0;
int Programm::degrees = 0;

void Programm::build_new_figure(std::vector<Figure *> &shapes) {
  std::cout << "\n<BUILDER>\n";
  Builder bd;
  Figure *new_figure = bd.build_object();
  shapes.push_back(new_figure);
  std::cout << "</BUILDER>\n\n";
}

void Programm::change_visibility(std::vector<Figure *> &shapes) {
  for (auto &elem : shapes) {
    if (elem->selected()) {
      elem->change_visibility();
      std::cout << "Visibility changed\n";
    }
  }
}

void Programm::deform(std::vector<Figure *> &shapes) {
  for (auto &elem : shapes) {
    if (elem->selected()) {
      elem->deform();
      std::cout << "Deformation applied\n";
    }
  }
}

void Programm::add_to_composite(std::vector<Figure *> &shapes) {
  std::vector<Figure *> removable;
  Composite *com = new Composite();
  for (auto &elem : shapes) {
    if (elem->selected()) {
      com->add_shape(elem->clone());
      removable.push_back(elem);
    }
  }
  for (auto &elem : shapes) {
    for (auto &rem : removable) {
      if (rem == elem)
        shapes.erase(
            std::remove(shapes.begin(), shapes.end(), elem),
            shapes.end());
    }
  }
  shapes.push_back(com);
  std::cout << "Selected shapes has been added to composite\n";
}

void Programm::display_start_msg() {
  std::cout << "----- Controls -----\n\nLMB - select shape\nRMB - deselect "
               "shape\nS - create checkpoint\nL - load last checkpoint\nZ - "
               "load start checkpoint\nT - turn on/off movement trail\n\n\n";
  std::cout << "When shape(s) is/are selected:\n\nArrow keys - move "
               "shape(s)\nR - move round\nV - turn visible/invisible\nD - "
               "deform\nC - add to composite\nB - create new figure\n";
  system("pause");
  std::cout << "\n\nLogs:\n";
}

void Programm::check_collisions(std::vector<Figure *> &shapes) {
  for (auto &one : shapes)
    for (auto &another : shapes) {
      if (one == another)
        continue;

      one->set_default_color();

      if (one->intersects(another)) {
        one->set_reversed_color();
        break;
      }
    }
}

void Programm::handle_input(
    Viewport *view,
    std::vector<Figure *> &shapes,
    sf::Vector2f &offset) {
  offset -= offset;
  sf::Event event;
  sf::Keyboard::Key code;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    offset += sf::Vector2f(0, -1);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    offset += sf::Vector2f(0, 1);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    offset += sf::Vector2f(-1, 0);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    offset += sf::Vector2f(1, 0);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
    for (auto &elem : shapes) {
      elem->move_round(degrees, sf::Vector2f(VELOCITY, VELOCITY));
    }
    degrees++;
  }

  while (view->get_window()->pollEvent(event)) {
    code = event.key.code;
    if (event.type == sf::Event::Closed)
      view->get_window()->close();
    if (event.type == sf::Event::MouseButtonPressed)
      switch (code) {
      case sf::Mouse::Left:
        select_shape(shapes, sf::Mouse::getPosition() - sf::Vector2i(8, 32));
        break;
      case sf::Mouse::Right:
        deselect_shape(shapes, sf::Mouse::getPosition() - sf::Vector2i(8, 32));
        break;
      }
    if (event.type == sf::Event::KeyPressed) {
      switch (code) {
      case sf::Keyboard::V:
        change_visibility(shapes);
        break;
      case sf::Keyboard::D:
        deform(shapes);
        break;
      case sf::Keyboard::S:
        save_checkpoint(shapes);
        break;
      case sf::Keyboard::L:
        load_checkpoint(shapes);
        break;
      case sf::Keyboard::Z:
        load_start(shapes);
        break;
      case sf::Keyboard::T:
        trail_enabled = !trail_enabled;
        std::cout << "Trail switched\n";
        break;
      case sf::Keyboard::C:
        add_to_composite(shapes);
        break;
      case sf::Keyboard::B:
        build_new_figure(shapes);
        break;
      }
    }
  }
}

void Programm::move_shapes(std::vector<Figure *> &shapes, sf::Vector2f offset) {
  for (auto &elem : shapes) {
    if (elem->selected())
      elem->move(offset);
    if (elem->crossed_border())
      elem->move(-offset);
  }
}

void Programm::select_shape(
    std::vector<Figure *> &shapes,
    sf::Vector2i mouse_position) {
  for (auto &elem : shapes) {
    if (elem->hover(mouse_position)) {
      elem->set_selection();
      std::cout << "Shape selected\n";
    }
  }
}

void Programm::deselect_shape(
    std::vector<Figure *> &shapes,
    sf::Vector2i mouse_position) {
  int i = 0;
  for (auto &elem : shapes) {
    if (elem->hover(mouse_position)) {
      shapes.erase(shapes.begin() + i);
      std::cout << "Shape deselected\n";
      break;
    }
    i++;
  }
}

void Programm::save_start(std::vector<Figure *> &shapes) {
  FigureSaver saver;
  std::ofstream fout("data/start.txt", std::ios_base::trunc);
  for (auto &elem : shapes) {
    saver.save_state(elem);
    fout << saver.to_string();
  }
  fout.close();
}

void Programm::save_checkpoint(std::vector<Figure *> &shapes) {
  FigureSaver saver;
  std::ofstream fout("data/checkpoint.txt");
  for (auto &elem : shapes) {
    saver.save_state(elem);
    fout << saver.to_string();
  }
  fout.close();
  std::cout << "Checkpoint saved\n";
}

void Programm::load_start(std::vector<Figure *> &shapes) {
  Figure *figure = nullptr;
  std::string buff;
  std::ifstream fin("data/start.txt");
  shapes.clear();
  while (true) {
    std::getline(fin, buff);
    if (buff == "")
      return;
    FigureSaver saver(buff);
    saver.load_state(figure);
    shapes.push_back(figure->clone());
  }
  delete figure;
  fin.close();
  std::cout << "Start checkpoint loaded\n";
}

void Programm::load_checkpoint(std::vector<Figure *> &shapes) {
  Figure *figure = nullptr;
  std::string buff;
  std::ifstream fin("data/checkpoint.txt");
  shapes.clear();
  while (true) {
    std::getline(fin, buff);
    if (buff == "")
      return;
    FigureSaver saver(buff);
    saver.load_state(figure);
    shapes.push_back(figure->clone());
  }
  delete figure;
  fin.close();
  std::cout << "Last checkpoint loaded\n";
}
