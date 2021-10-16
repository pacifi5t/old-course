#pragma once

#include "Composite.h"

class FigureSaver {
  Memento memento;

public:
  FigureSaver();
  FigureSaver(std::string);
  void save_state(Figure *);
  void load_state(Figure *&);
  std::string to_string();
};