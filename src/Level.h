#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Platform.h"

class Level
{
public:
  Level();
  ~Level();

  std::vector<sf::Vector2i> GetVisiblePlatforms();

  void Draw(Window& l_window, sf::View view);

protected:
  sf::Texture texture;
  sf::Sprite sprite;
  Platform platform;
  std::string sLevelMap;

private:
  int m_LevelWidth;
  int m_LevelHeight;

  std::vector<sf::Vector2i> m_visibleTileCoords;
};
