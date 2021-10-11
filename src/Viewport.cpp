#include "Viewport.h"

Viewport* Viewport::instance = nullptr;

Viewport::Viewport()
{
    window = new sf::RenderWindow(sf::VideoMode(1600, 900), "Graphics");
    window->setFramerateLimit(150);
    window->setPosition(sf::Vector2i(0,0));
}

Viewport::~Viewport()
{
    delete window;
}

Viewport* Viewport::get_instance()
{
    if (!instance)
        instance = new Viewport();
    return instance;
}

sf::RenderWindow* Viewport::get_window()
{
    return get_instance()->window;
}

void Viewport::lock_window()
{
    window->setPosition(sf::Vector2i(0, 0));
    window->setSize(sf::Vector2u(1600, 900));
}
