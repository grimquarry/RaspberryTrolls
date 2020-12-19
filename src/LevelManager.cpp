#include "LevelManager.h"

LevelManager::LevelManager()
{

}

LevelManager::~LevelManager() { }

void LevelManager::BuildLevel()
{
  m_Level_1_1.LoadLevelMap("../maps/level_1_1");
  m_Level_1_1.AddPlatformSprite("../resources/images/nectarineBranch_2.png");
}

std::vector<sf::Vector2i> LevelManager::GetVisiblePlatforms()
{
  return m_Level_1_1.GetVisiblePlatforms();
}

void LevelManager::DrawLevel(Window& l_window, sf::View view)
{
  m_Level_1_1.Draw(l_window, view);
}
