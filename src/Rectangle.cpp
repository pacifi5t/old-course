#include "Rectangle.h"


Rectangle::Rectangle() : Figure()
{
}

Rectangle::Rectangle(int w, int h, sf::Color clr, sf::Vector2f pos) : Figure(h, w, clr, pos)
{
	vertex_count = 4;
	initialize_vertices();
}

Figure* Rectangle::clone()
{
	return new Rectangle(*this);
}

void Rectangle::deform()
{
	int vertex_id = rand() % vertex_count;
	int force = rand() % 30;
	vertices[vertex_id].position.x += force;
	force = rand() % 30;
	vertices[vertex_id].position.y -= force;
	vertex_id = rand() % vertex_count;
	force = rand() % 30;
	vertices[vertex_id].position.x -= force;
	force = rand() % 30;
	vertices[vertex_id].position.y += force;
}

std::string Rectangle::to_string()
{
	return "4-" + std::to_string(width) + "-" + std::to_string(height) + "-" + std::to_string(default_color.r) + "," + std::to_string(default_color.g) + "," + std::to_string(default_color.b)
		+ "-" + std::to_string((int)position.x) + "," + std::to_string((int)position.y);
}

void Rectangle::from_string(std::string str)
{
	sf::Color clr = sf::Color::White;
	sf::Vector2f pos;

	char* cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	if (atoi(strtok(cstr, "-")) != 4)
		return;
	width = atoi(strtok(nullptr, "-"));
	height = atoi(strtok(nullptr, "-"));
	color.r = atoi(strtok(nullptr, ","));
	color.g = atoi(strtok(nullptr, ","));
	color.b = atoi(strtok(nullptr, "-"));
	position.x = atoi(strtok(nullptr, ","));
	position.y = atoi(strtok(nullptr, "-"));
	delete[] cstr;

	default_color = color;
	reversed_color = sf::Color::White - color;
	reversed_color.a = 255;
	vertex_count = 4;

	initialize_vertices();
}

void Rectangle::initialize_vertices()
{
	vertices = new sf::Vertex[vertex_count];

	vertices[0] = sf::Vertex(sf::Vector2f(position.x - width / 2, position.y + height / 2), color);
	vertices[1] = sf::Vertex(sf::Vector2f(position.x + width / 2, position.y + height / 2), color);
	vertices[2] = sf::Vertex(sf::Vector2f(position.x + width / 2, position.y - height / 2), color);
	vertices[3] = sf::Vertex(sf::Vector2f(position.x - width / 2, position.y - height / 2), color);
}
