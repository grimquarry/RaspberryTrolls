#include "Platform.h"

Platform::Platform() { }

Platform::~Platform() { }

void Platform::LoadTexture(std::string imgPath)
{
  m_PlatformTexture.loadFromFile(imgPath);
}

void Platform::SetTexture()
{
  m_PlatformSprite.setTexture(m_PlatformTexture);
}

sf::Vector2f Platform::GetSize() const
{
  return { m_PlatformSprite.getGlobalBounds().width, m_PlatformSprite.getGlobalBounds().height };
}

int Platform::GetWidth()
{
  m_PlatformWidth = m_PlatformSprite.getGlobalBounds().width;
  return m_PlatformWidth;
}

int Platform::GetHeight()
{
  m_PlatformHeight = m_PlatformSprite.getGlobalBounds().height;
  return m_PlatformHeight;
}

void Platform::SetPosition(int x, int y)
{
  m_PlatformSprite.setPosition(x, y);
}

void Platform::SetPosition(sf::Vector2f pos)
{
  m_PlatformSprite.setPosition(pos);
}

void Platform::Rotate(float degrees)
{
  m_PlatformSprite.setRotation(degrees);
  m_PlatformSprite.setScale({ 1, -1 });
  m_PlatformSprite.setOrigin(m_PlatformWidth, 0.0f);
}

sf::Vector2f Platform::GetPosition() const
{
  return m_PlatformSprite.getPosition();
}

void Platform::Draw(Window& win)
{
  win.Draw(m_PlatformSprite);
}
