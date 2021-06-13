#include "Level.h"
#include <iostream>

Level::Level()
{
  /*m_GridUnit = 25.0f;*/
}

Level::~Level() { }

std::vector<Platform> Level::GetVisiblePlatforms() const
{
  return m_VisibleTiles;
}

void Level::LoadLevelMap(std::string mapPath)
{
  std::string line;
  int lineCount = 0;
  m_LevelFile.open(mapPath);

  while(m_LevelFile)
  {
    getline(m_LevelFile, line);
    std::cout << line << std::endl;
    m_LevelMap += line;
    if(line.size() != 0)
    {
      lineCount++;
      m_LevelWidth = line.size();
    }
  }

  m_LevelHeight = lineCount;
  std::cout << "Level width is: " << m_LevelWidth << std::endl;
  std::cout << "Level height is: " << m_LevelHeight << std::endl;

  m_LevelFile.close();
}

void Level::LoadLevelBackground(std::string filePath)
{
  m_LevelBackground.LoadTexture(filePath);
  m_LevelBackground.SetTexture();
}

void Level::AddPlatformSprite(std::string imgPath)
{
  m_PlatformSprite.LoadTexture(imgPath);
  m_PlatformSprite.SetTexture();

  m_PlatformSprites.push_back(m_PlatformSprite);
}

void Level::SetParallaxCam(sf::Vector2u winSize)
{

  m_ParallaxCamera.setSize( { (float)winSize.x, (float)winSize.y }/*{ (float)m_window.GetSize().x, (float)m_window.GetSize().y }*/);
}

void Level::SetBackgroundCenter(sf::Vector2f center)
{
  m_BackgroundCenter = center;
  m_ParallaxCamera.setCenter(center);
}

void Level::Draw(Window& l_window, sf::View view)
{
  int tileIndex = 0;
  int minXView = view.getCenter().x - (l_window.GetSize().x / 2) - 200;
  int maxXView = view.getCenter().x + (l_window.GetSize().x / 2);


  l_window.SetView(m_ParallaxCamera);
  m_LevelBackground.SetScale({ 1.5f, 1.5f });
  m_LevelBackground.SetPosition( { 0, l_window.GetSize().y - m_LevelBackground.GetSpriteHeight() });
  m_LevelBackground.Draw(l_window);
  m_LevelBackground.SetPosition( { m_LevelBackground.GetSpriteWidth(), l_window.GetSize().y - m_LevelBackground.GetSpriteHeight() });
  m_LevelBackground.Draw(l_window);

  m_VisibleTiles.clear();
  l_window.SetView(view);
  for(int y = 0; y < m_LevelHeight; y++)
  {
    for(int x = 0; x < m_LevelWidth; x++)
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
