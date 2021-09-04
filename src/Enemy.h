#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"

class Enemy
{
public:
  Enemy();
  ~Enemy();

  void SetPosition(float x, float y);
  void SetPosition(sf::Vector2f pos);

  sf::Vector2f vel;

  void AddAnimTexture(std::string txtrLocation);

  void Draw(Window& l_window);

protected:
  sf::Texture m_EnemyTexture;
  sf::Sprite m_EnemySprite;
  std::vector<sf::Texture> m_TxtrAnimBuff;

private:
  sf::Vector2f m_Position;

};
