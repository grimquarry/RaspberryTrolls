#include "Level.h"
#include <iostream>

Level::Level() { }

Level::~Level() { }

std::vector<Platform> Level::GetVisiblePlatforms() const
{
  return m_VisibleTiles;
}

void Level::LoadLevelMap(std::string mapPath)
{
  std::string line;
  m_LevelFile.open(mapPath);

  while(m_LevelFile)
  {
    getline(m_LevelFile, line);
    std::cout << line << std::endl;
    m_LevelMap += line;
  }

  m_LevelFile.close();
}

void Level::AddPlatformSprite(std::string imgPath)
{
  m_PlatformSprite.LoadTexture(imgPath);
  m_PlatformSprite.SetTexture();

  m_PlatformSprites.push_back(m_PlatformSprite);
}

void Level::Draw(Window& l_window, sf::View view)
{
  int tileIndex = 0;
  int minXView = view.getCenter().x - (l_window.GetSize().x / 2) - 200;
  int maxXView = view.getCenter().x + (l_window.GetSize().x / 2);

  m_VisibleTiles.clear();
  for(int y = 0; y < 14; y++)
  {
    for(int x = 0; x < 64; x++)
    {
      int platformLocationX = x * 200;
      int platformLocationY = y * 75;
      if(m_LevelMap[tileIndex] == '0' && platformLocationX > minXView && platformLocationX < maxXView)
      {
        m_PlatformSprites[0].SetPosition(platformLocationX, platformLocationY);
        m_VisibleTiles.push_back(m_PlatformSprites[0]);
        m_PlatformSprites[0].Draw(l_window);
      }
      tileIndex++;
    }
  }
}
