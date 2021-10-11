#pragma once
#include <SFML/Graphics.hpp>

class Viewport
{
    Viewport();
    sf::RenderWindow* window;
    static Viewport* instance;
    ~Viewport();

public:
    static Viewport* get_instance();
    static sf::RenderWindow* get_window();
    void lock_window();
};