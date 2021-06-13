#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Window.h"

class Background
{
public:
  Background();
  ~Background();

  void LoadTexture(std::string imgPath);
  void SetTexture();

  float GetSpriteWidth();
  float GetSpriteHeight();

  void SetPosition(sf::Vector2f pos);
  void SetScale(sf::Vector2f scale);

  void Draw(Window& win);

protected:
  sf::Texture m_BackgroundTexture;
  sf::Sprite m_BackgroundSprite;

private:
  float m_SpriteWidth;
  float m_SpriteHeight;
};
