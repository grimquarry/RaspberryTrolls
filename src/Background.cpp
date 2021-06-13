#include "Background.h"

Background::Background() { }
Background::~Background() { }

void Background::LoadTexture(std::string imgPath)
{
  m_BackgroundTexture.loadFromFile(imgPath);
}

void Background::SetTexture()
{
  m_BackgroundSprite.setTexture(m_BackgroundTexture);

  m_SpriteWidth = m_BackgroundSprite.getGlobalBounds().width;
  m_SpriteHeight = m_BackgroundSprite.getGlobalBounds().height;
}

float Background::GetSpriteWidth() { return m_SpriteWidth; }

float Background::GetSpriteHeight() { return m_SpriteHeight; }

void Background::SetPosition(sf::Vector2f pos) { m_BackgroundSprite.setPosition(pos); }

void Background::SetScale(sf::Vector2f scale)
{
  m_BackgroundSprite.setScale(scale);

  m_SpriteWidth = m_BackgroundSprite.getGlobalBounds().width;
  m_SpriteHeight = m_BackgroundSprite.getGlobalBounds().height;
}

void Background::Draw(Window& win) { win.Draw(m_BackgroundSprite); }
