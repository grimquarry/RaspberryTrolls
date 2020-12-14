#include "TitleScreen.h"

TitleScreen::TitleScreen()
{
  m_titleTexture.loadFromFile("../resources/images/example2.png");
  m_titleTexture.setSmooth(true);
  m_titleImage.setTexture(m_titleTexture);
  sf::VideoMode mode = sf::VideoMode::getDesktopMode();
  float screenSizeX = mode.width;
  float screenSizeY = mode.height;

  sf::Vector2u textureSize = m_titleTexture.getSize();

  float scaleDegree = screenSizeY / textureSize.y;
  m_titleImage.setScale(scaleDegree, scaleDegree);
}

TitleScreen::~TitleScreen() { }

void TitleScreen::Draw(Window& l_window)
{
  l_window.Draw(m_titleImage);
}
