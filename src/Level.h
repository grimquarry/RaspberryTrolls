#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Platform.h"
#include "Background.h"

class Level
{
public:
  Level();
  ~Level();

  std::vector<Platform> GetVisiblePlatforms() const;

  void LoadLevelMap(std::string mapPath);
  void LoadLevelBackground(std::string filePath);
  void AddPlatformSprite(Platform& plat);

  void SetParallaxCam(sf::Vector2u winSize);
  void SetBackgroundCenter(sf::Vector2f center);

  void Draw(Window& l_window, sf::View view);

protected:
  sf::Texture texture;
  sf::Sprite sprite;
  Platform m_PlatformSprite;

private:
  int m_LevelWidth;
  int m_LevelHeight;
  //float m_GridUnit;

  std::string m_LevelMap;
  std::fstream m_LevelFile;

  std::vector<Platform> m_PlatformSprites;
  std::vector<Platform> m_VisibleTiles;

  Background m_LevelBackground;
  sf::Vector2u m_WindowSize;
  sf::View m_ParallaxCamera;
  sf::Vector2f m_BackgroundCenter;

};
