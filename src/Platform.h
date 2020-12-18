#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Window.h"

class Platform
{
public:
  Platform();
  ~Platform();

  void LoadTexture(std::string imgPath);

  void SetTexture();

  void SetPosition(int x, int y);

  void Draw(Window& l_window);

protected:
  sf::Texture m_PlatformTexture;
  sf::Sprite m_PlatformSprite;

private:
  int m_PlatformWidth;
  int m_PlatformHeight;

};
