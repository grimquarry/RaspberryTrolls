#include "Platform.h"
#include <iostream>

Platform::Platform() { std::cout << "Platform Constructor Ran" << std::endl;}

Platform::~Platform() { }

void Platform::LoadTexture(std::string imgPath)
{
  m_PlatformTexture.loadFromFile(imgPath);
}

void Platform::SetTexture()
{
  m_PlatformSprite.setTexture(m_PlatformTexture);
  // m_PlatformWidth = m_PlatformSprite.getGlobalBounds().width;
  // m_PlatformHeight = m_PlatformSprite.getGlobalBounds().height;
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

void Platform::Draw(Window& l_window)
{
  l_window.Draw(m_PlatformSprite);
}
