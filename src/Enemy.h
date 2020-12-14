#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"

class Enemy {
public:
  Enemy();
  ~Enemy();

  void Draw(Window& l_window);

private:
  sf::RectangleShape m_enemy;

};
