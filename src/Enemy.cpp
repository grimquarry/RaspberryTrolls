#include "Enemy.h"

Enemy::Enemy()
{
  m_enemy.setPosition(10.f, 10.f);
  m_enemy.setSize(sf::Vector2f(100.f, 100.f));
  m_enemy.setScale(sf::Vector2f(0.5f, 0.5f));//reduce size of rect by half
  m_enemy.setFillColor(sf::Color::Cyan);
  m_enemy.setOutlineColor(sf::Color::Green);
  m_enemy.setOutlineThickness(1.f);
}

Enemy::~Enemy() { }

void Enemy::Draw(Window& l_window)
{
  l_window.Draw(m_enemy);
}
