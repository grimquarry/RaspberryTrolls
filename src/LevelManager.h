#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"

class LevelManager
{
public:
  LevelManager();
  ~LevelManager();

  std::vector<sf::Vector2i> GetVisiblePlatforms();

  void BuildLevel();

  bool CheckLevelChange();
  void SetLevelChange(bool lvlchange);

  void DrawLevel(Window& l_window, sf::View view);

private:
  bool m_LevelChange;
  Level m_Level_1_1;
  int m_CurrentLevel;
};
