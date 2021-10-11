#include "Triangle.h"

Triangle::Triangle() : Figure()
{
}

Triangle::Triangle(int w, int h, sf::Color clr, sf::Vector2f pos) : Figure(h, w, clr, pos)
{
	vertex_count = 3;
	initialize_vertices();
}

Figure* Triangle::clone()
{
	return new Triangle(*this);
}

void Triangle::deform()
{
	int vertex_id = rand() % vertex_count;
	int force = rand() % 30;
	vertices[vertex_id].position.x += force;
	force = rand() % 30;
	vertices[vertex_id].position.y -= force;
}

std::string Triangle::to_string()
{
	return "3-" + std::to_string(width) + "-" + std::to_string(height) + "-" + std::to_string(default_color.r) + "," + std::to_string(default_color.g) + "," + std::to_string(default_color.b)
		+ "-" + std::to_string((int)position.x) + "," + std::to_string((int)position.y);
}

void Triangle::from_string(std::string str)
{
	char* cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	if (atoi(strtok(cstr, "-")) != 3)
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
	vertex_count = 3;
	initialize_vertices();
}

void Triangle::initialize_vertices()
{
	vertices = new sf::Vertex[vertex_count];

	vertices[0] = sf::Vertex(sf::Vector2f(position.x, position.y - height / 2), color);
	vertices[1] = sf::Vertex(sf::Vector2f(position.x + width / 2, position.y + height / 2), color);
	vertices[2] = sf::Vertex(sf::Vector2f(position.x - width / 2, position.y + height / 2), color);
}
