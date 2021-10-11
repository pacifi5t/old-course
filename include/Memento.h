#pragma once
#include <string>

class Memento
{
	friend class Figure;
	friend class FigureSaver;

	std::string state;

public:
	Memento();
	Memento(std::string);
};