#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Platform.h"

class Level
{
public:
  Level();
  ~Level();

  std::vector<Platform> GetVisiblePlatforms() const;

  void LoadLevelMap(std::string mapPath);
  void AddPlatformSprite(std::string imgPath);

  void Draw(Window& l_window, sf::View view);

protected:
  sf::Texture texture;
  sf::Sprite sprite;
  Platform m_PlatformSprite;

private:
  int m_LevelWidth;
  int m_LevelHeight;

  std::string m_LevelMap;
  std::fstream m_LevelFile;

  std::vector<Platform> m_PlatformSprites;

  std::vector<Platform> m_VisibleTiles;
};
