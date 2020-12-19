#include "Level.h"
#include <iostream>

Level::Level()
{
  // if(!texture.loadFromFile("../resources/images/nectarineBranch_2.png"))
  // {
  //   std::cout << "Failed to load file" << std::endl;
  // }
  // sprite.setTexture(texture);
  // platform.LoadTexture("../resources/images/nectarineBranch_2.png");
  // platform.SetTexture();
  //AddPlatformSprite("../resources/images/nectarineBranch_2.png");

  // sLevelMap += "-...............................................................";
  // sLevelMap += ".--.............................................................";
  // sLevelMap += "...---..........................................................";
  // sLevelMap += "......----......................................................";
  // sLevelMap += "...---..........................................................";
  // sLevelMap += ".--.............................................................";
  // sLevelMap += "-...............................................................";
  // sLevelMap += ".--.............................................................";
  // sLevelMap += "...---..........................................................";
  // sLevelMap += "......----......................................................";
  // sLevelMap += "................................................................";
  // sLevelMap += "-...............................................................";
  // sLevelMap += "--..............................................................";
  // sLevelMap += "--.---..........................................................";
  // std::cout << sLevelMap << std::endl;

}

Level::~Level()
{

}

std::vector<sf::Vector2i> Level::GetVisiblePlatforms()
{
  return m_visibleTileCoords;
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
  // if(!m_LevelFile)
  // {
  //   std::cout << "This is the fucking issue" << std::endl;
  // }
  // while(m_LevelFile)
  // {
  //   getline(m_LevelFile, m_LevelMap);
  // }
  // std::cout << "What" << m_LevelMap;
  m_LevelFile.close();

  //m_LevelMap.erase(std::remove(m_LevelMap.begin(), m_LevelMap.end(), '\n'), m_LevelMap.end());

  //std::cout << m_LevelMap << std::endl;
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

  m_visibleTileCoords.clear();
  for(int y = 0; y < 14; y++)
  {
    for(int x = 0; x < 64; x++)
    {
      int platformLocationX = x * 200;
      int platformLocationY = y * 75;
      if(m_LevelMap[tileIndex] == '0' && platformLocationX > minXView && platformLocationX < maxXView)
      {
        m_PlatformSprites[0].SetPosition(platformLocationX, platformLocationY);
        m_visibleTileCoords.push_back({platformLocationX, platformLocationY});
        //std::cout << "\nX: " << x*200 << "\nY: " << y * 75 << std::endl;
        //std::cout << tileIndex << std::endl;
        //l_window.Draw(sprite);
        m_PlatformSprites[0].Draw(l_window);
      }
      tileIndex++;
    }
  }
}
