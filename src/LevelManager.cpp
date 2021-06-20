#include "LevelManager.h"

LevelManager::LevelManager()
{
  m_LevelChange = true;
  m_CurrentLevel = 11;

  m_NectarineBranch.LoadTexture("../resources/images/nectarineBranch_2.png");
  m_NectarineBranch.SetTexture();
  m_NectarineBlossom1.LoadTexture("../resources/images/NectarineBlossom1.png");
  m_NectarineBlossom1.SetTexture();
}

LevelManager::~LevelManager() { }

void LevelManager::BuildLevel()
{
  switch(m_CurrentLevel) {
    case 11:
    m_Level_1_1.SetParallaxCam(m_WindowSize);
    m_Level_1_1.LoadLevelMap("../maps/level_1_1");
    m_Level_1_1.LoadLevelBackground("../resources/images/Mountains_2.png");
    m_Level_1_1.AddPlatformSprite(m_NectarineBranch);
    m_Level_1_1.AddPlatformSprite(m_NectarineBlossom1);
    break;
  }
}

void LevelManager::SetBackgroundCenter(sf::Vector2f center)
{
  m_BackgroundCenter = center;
}

std::vector<Platform> LevelManager::GetVisiblePlatforms()
{
  return m_Level_1_1.GetVisiblePlatforms();
}

void LevelManager::SetWindowSize(sf::Vector2u winSize) { m_WindowSize = winSize; }

bool LevelManager::CheckLevelChange() { return m_LevelChange; }

void LevelManager::SetLevelChange(bool lvlchange) { m_LevelChange = lvlchange; }

void LevelManager::DrawLevel(Window& l_window, sf::View view)
{
  m_Level_1_1.SetBackgroundCenter(m_BackgroundCenter);
  m_Level_1_1.Draw(l_window, view);
}
