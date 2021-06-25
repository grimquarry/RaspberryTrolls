#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Platform.h"
#include "Background.h"
#include "Fruit.h"

class Level
{
public:
  Level();
  ~Level();

  std::vector<Platform> GetVisiblePlatforms() const;
  std::vector<Fruit> GetVisibleFruit();

  void LoadLevelMap(std::string mapPath);
  void LoadLevelBackground(std::string filePath);

  void AddPlatformSprite(Platform& plat);
  void AddFruitSprite(Fruit& f);

  void SetParallaxCam(sf::Vector2u winSize);
  void SetBackgroundCenter(sf::Vector2f center);

  void HandleCollectedFruit(sf::Vector2f fruitPos);

  void BuildFruitMap();

  void Draw(Window& l_window, sf::View view);

protected:
  sf::Texture texture;
  sf::Sprite sprite;
  Platform m_PlatformSprite;
  Fruit m_FruitSprite;

private:
  int m_LevelWidth;
  int m_LevelHeight;
  //float m_GridUnit;

  std::string m_LevelMap;
  std::fstream m_LevelFile;

  std::vector<Platform> m_PlatformSprites;
  std::vector<Platform> m_VisibleTiles;

  std::vector<Fruit> m_FruitSprites;
  std::vector<Fruit> m_VisibleFruit;

  Background m_LevelBackground;
  sf::Vector2u m_WindowSize;
  sf::View m_ParallaxCamera;
  sf::Vector2f m_BackgroundCenter;

  sf::Vector2f m_FruitCoordinates; //Stores position of fruit player collided with

  std::vector<Fruit> m_FruitMap;

};
