#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"
#include <iostream>


class TitleScreen {
public:
  TitleScreen();
  ~TitleScreen();

  void Draw(Window& l_window);

private:
  sf::Texture m_titleTexture;
  sf::Sprite m_titleImage;
};
