#pragma once
#include "Figure.h"
class Rectangle : public Figure
{
public:
	Rectangle();
	Rectangle(int, int, sf::Color, sf::Vector2f);

	virtual Figure* clone() override;
	virtual void deform() override;
	virtual std::string to_string() override;
	virtual void from_string(std::string) override;
	virtual void initialize_vertices() override;
};