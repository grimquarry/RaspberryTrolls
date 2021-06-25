#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Platform.h"
#include "Fruit.h"

class LevelManager
{
public:
  LevelManager();
  ~LevelManager();

  std::vector<Platform> GetVisiblePlatforms();
  std::vector<Fruit> GetVisibleFruit();

  void SetWindowSize(sf::Vector2u winSize);
  void BuildLevel();
  void SetBackgroundCenter(sf::Vector2f center);

  bool CheckLevelChange();
  void SetLevelChange(bool lvlchange);

  void HandleCollectedFruit(sf::Vector2f fruitPos);

  void DrawLevel(Window& l_window, sf::View view);

private:
  bool m_LevelChange;
  Level m_Level_1_1;
  int m_CurrentLevel;
  sf::Vector2u m_WindowSize;
  sf::Vector2f m_BackgroundCenter;

  Platform m_NectarineBranch;
  Platform m_NectarineBlossom1;
  Platform m_RotatedNectBranch;
  Platform m_NectarineLeaves1;

  Fruit m_Nectarine;
};
