#pragma once
#include <vector>
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Star.h"
#include "Hexagon.h"

using sf::RenderTarget, sf::RenderStates;

class Composite: public Figure
{
	std::vector<Figure*>* figures;

public:
	Composite();
	~Composite();
	void add_shape(Figure*);
	void remove_shape(Figure*);
	bool selected() override;
	virtual bool crossed_border() override;
	virtual void change_visibility() override;
	virtual bool intersects(Figure*) override;
	virtual bool hover(sf::Vector2i) override;
	virtual void move(sf::Vector2f) override;
	virtual void move_round(int, sf::Vector2f) override;
	virtual void set_selection() override;
	virtual void set_default_color() override;
	virtual void set_reversed_color() override;
	virtual std::string to_string() override;
	virtual void from_string(std::string) override;
	virtual Figure* clone() override;
	virtual void deform() override;
	virtual void draw(RenderTarget& target, RenderStates states) const;
};