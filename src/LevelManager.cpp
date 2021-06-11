#include "LevelManager.h"

LevelManager::LevelManager()
{
  m_LevelChange = true;
  m_CurrentLevel = 11;
}

LevelManager::~LevelManager() { }

void LevelManager::BuildLevel()
{
  switch(m_CurrentLevel) {
    case 11:
    m_Level_1_1.LoadLevelMap("../maps/level_1_1");
    m_Level_1_1.AddPlatformSprite("../resources/images/nectarineBranch_2.png");
    break;
  }

}

std::vector<Platform> LevelManager::GetVisiblePlatforms()
{
  return m_Level_1_1.GetVisiblePlatforms();
}

bool LevelManager::CheckLevelChange()
{
  return m_LevelChange;
}
void LevelManager::SetLevelChange(bool lvlchange)
{
  m_LevelChange = lvlchange;
}

void LevelManager::DrawLevel(Window& l_window, sf::View view)
{
  m_Level_1_1.Draw(l_window, view);
}
