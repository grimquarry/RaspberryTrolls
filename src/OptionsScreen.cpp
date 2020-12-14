#include "OptionsScreen.h"

OptionsScreen::OptionsScreen()
{
  m_titleTexture.loadFromFile("../resources/images/OptionsGraphic.png");
  m_titleTexture.setSmooth(true);
  m_titleImage.setTexture(m_titleTexture);
  sf::VideoMode mode = sf::VideoMode::getDesktopMode();
  float screenSizeX = mode.width;
  float screenSizeY = mode.height;

  sf::Vector2u textureSize = m_titleTexture.getSize();

  float scaleDegreeY = screenSizeY / textureSize.y;
  float scaleDegreeX = screenSizeX / textureSize.x;
  m_titleImage.setScale(scaleDegreeX, scaleDegreeY);
}

OptionsScreen::~OptionsScreen() { }

void OptionsScreen::Draw(Window& l_window)
{
  l_window.Draw(m_titleImage);  //Need to make an OptionsScreen.
}
