#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Window.h"

class Platform
{
public:
  Platform();

  ~Platform();

  void LoadTexture(std::string imgPath);

  void SetTexture();

  sf::Vector2f GetSize() const;

  int GetWidth();

  int GetHeight();

  void SetPosition(int x, int y);

  void SetPosition(sf::Vector2f pos);

  sf::Vector2f GetPosition() const;

  void Draw(Window& win);

protected:
  sf::Texture m_PlatformTexture;
  sf::Sprite m_PlatformSprite;

private:
  int m_PlatformWidth;
  int m_PlatformHeight;
};
