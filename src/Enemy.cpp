#include "Enemy.h"

Enemy::Enemy()
{

}
Enemy::~Enemy() { }

void Enemy::SetPosition(float x, float y)
{
  m_Position.x = x;
  m_Position.y = y;
  m_EnemySprite.setPosition(m_Position.x, m_Position.y);
}

void Enemy::SetPosition(sf::Vector2f pos)
{
  m_Position = pos;
  m_EnemySprite.setPosition(m_Position);
}

sf::Vector2f vel;

void Enemy::AddAnimTexture(std::string txtrLocation)
{
  if(!m_EnemyTexture.loadFromFile(txtrLocation))
  {
    std::cout << "Failed to load file" << std::endl;
  }
  else
  {
    m_TxtrAnimBuff.push_back(m_EnemyTexture);
    m_EnemySprite.setTexture(m_TxtrAnimBuff[0]);
  }
}

void Enemy::Draw(Window& l_window)
{
  l_window.Draw(m_EnemySprite);
}
