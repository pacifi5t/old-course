#include "Hexagon.h"

Hexagon::Hexagon() : Figure()
{
}

Hexagon::Hexagon(int w, int h, sf::Color clr, sf::Vector2f pos) : Figure(w, h, clr, pos)
{
	vertex_count = 6;
	initialize_vertices();
}

Figure* Hexagon::clone()
{
	return new Hexagon(*this);
}

void Hexagon::deform()
{
	int vertex_id;

	vertex_id = rand() % vertex_count;
	vertices[vertex_id].position.y += 10;
	vertex_id = rand() % vertex_count;
	vertices[vertex_id].position.x -= 20;
	vertex_id = rand() % vertex_count;
	vertices[vertex_id].position.y -= 20;
	vertex_id = rand() % vertex_count;
	vertices[vertex_id].position.x += 10;
}

std::string Hexagon::to_string()
{
	return "6-" + std::to_string(width) + "-" + std::to_string(height) + "-" + std::to_string(default_color.r) + "," + std::to_string(default_color.g) + "," + std::to_string(default_color.b)
		+ "-" + std::to_string((int)position.x) + "," + std::to_string((int)position.y);
}

void Hexagon::from_string(std::string str)
{
	sf::Color clr = sf::Color::White;
	sf::Vector2f pos;

	char* cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	if (atoi(strtok(cstr, "-")) != 6)
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
	vertex_count = 6;

	initialize_vertices();
}

void Hexagon::initialize_vertices()
{
	vertices = new sf::Vertex[vertex_count];

	auto deg = 90;
	for (int i = 0; i < vertex_count; i++)
	{
		auto offset = sf::Vector2f(width / 2, height / 2);
		offset.x *= cos(deg * 3.14 / 180);
		offset.y *= sin(deg * 3.14 / 180);
		vertices[i] = sf::Vertex(position + offset, color);
		deg += 360 / vertex_count;
	}
}
