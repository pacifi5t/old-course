#include <iostream>
#include "Programm.h"
#include "Builder.h"

int main()
{
	srand(time(0));
	std::vector<Figure*> shapes;
	sf::Vector2f offset(0, 0);
	
	Circle circle(120, sf::Color::Magenta, sf::Vector2f(250, 300));
	Ellipse ellipse(200, 100, sf::Color::Red, sf::Vector2f(1200, 400));
	Triangle triangle(200, 100, sf::Color::Cyan, sf::Vector2f(800, 600));
	Rectangle rectangle(150, 120, (sf::Color::Blue), sf::Vector2f(200, 700));
	Star star(100, sf::Color::Yellow, sf::Vector2f(1300, 800));
	Hexagon hexagon(200, 200, sf::Color::Green, sf::Vector2f(500, 400));

	shapes.push_back(circle.clone());
	shapes.push_back(ellipse.clone());
	shapes.push_back(triangle.clone());
	shapes.push_back(rectangle.clone());
	shapes.push_back(star.clone());
	shapes.push_back(hexagon.clone());

	Programm::display_start_msg();
	Viewport* view = Viewport::get_instance();
	Programm::save_start(shapes);

	while (view->get_window()->isOpen())
	{
		view->lock_window();
		Programm::check_collisions(shapes);
		Programm::handle_input(view, shapes, offset);
		offset = sf::Vector2f(offset.x * Programm::VELOCITY, offset.y * Programm::VELOCITY);
		Programm::move_shapes(shapes, offset);

		if (!Programm::trail_enabled) 
			view->get_window()->clear();
		
		for (int i = 0; i < shapes.size(); i++)
			view->get_window()->draw(*shapes[i]);
		view->get_window()->display();
	}

	return 0;
}