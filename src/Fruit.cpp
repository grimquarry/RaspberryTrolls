#include "Fruit.h"

Fruit::Fruit()
{
  m_Collected = true;
}

Fruit::~Fruit() { }

void Fruit::AddAnimTexture(std::string txtrLocation)
{
  if(!m_FruitTexture.loadFromFile(txtrLocation))
  {
    std::cout << "Failed to load file" << std::endl;
  }
  else
  {
    m_TxtrAnimBuff.push_back(m_FruitTexture);
  }
}

void Fruit::SetCollectable(bool b) { m_Collected = b; }

bool Fruit::GetCollectable() { return m_Collected; }

void Fruit::SetPosition(int x, int y)
{
  m_Position.x = x;
  m_Position.y = y;
  m_FruitSprite.setPosition(m_Position.x, m_Position.y);
}

sf::Vector2f Fruit::GetPosition() const { return m_Position; }

sf::Vector2f Fruit::GetSize() const
{
  return { m_FruitSprite.getGlobalBounds().width, m_FruitSprite.getGlobalBounds().height };
}

void Fruit::HandleAnimTexture()
{
  m_FruitSprite.setTexture(m_TxtrAnimBuff[0]);
}

void Fruit::Draw(Window& win)
{
  HandleAnimTexture();
  win.Draw(m_FruitSprite);
}
