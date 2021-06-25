#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Window.h"

class Fruit
{
public:

  Fruit();

  ~Fruit();

  void AddAnimTexture(std::string txtrLocation);

  void SetCollectable(bool b);
  bool GetCollectable();


  void SetPosition(int x, int y);
  sf::Vector2f GetPosition() const;

  sf::Vector2f GetSize() const;

  void HandleAnimTexture();

  void Draw(Window& win);

protected:

  sf::Texture m_FruitTexture;
  sf::Sprite m_FruitSprite;
  std::vector<sf::Texture> m_TxtrAnimBuff;


private:
  sf::Vector2f m_Position;
  bool m_Collected;
};
