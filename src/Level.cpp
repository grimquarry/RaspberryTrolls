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

void Level::AddPlatformSprite(Platform& plat)
{
  // m_PlatformSprite.LoadTexture(imgPath);
  // m_PlatformSprite.SetTexture();

  m_PlatformSprites.push_back(plat);
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
      int platformLocationX = x * 25; //The X axis incremets in spans of 25 pixels
      int platformLocationY = y * 75; //The Y axis increments in spans of 75 pixels
      if(m_LevelMap[tileIndex] == '0' && platformLocationX > minXView && platformLocationX < maxXView)
      {
        m_PlatformSprites[0].SetPosition(platformLocationX, platformLocationY);
        m_VisibleTiles.push_back(m_PlatformSprites[0]);
        m_PlatformSprites[0].Draw(l_window);
      }
      else if(m_LevelMap[tileIndex] == '1' && platformLocationX > minXView && platformLocationX < maxXView)
      {
        m_PlatformSprites[1].SetPosition(platformLocationX, platformLocationY);
        m_VisibleTiles.push_back(m_PlatformSprites[1]);
        m_PlatformSprites[1].Draw(l_window);
      }
      else if(m_LevelMap[tileIndex] == 'h' && platformLocationX > minXView && platformLocationX < maxXView)
      {
        Platform rotatedBranch = m_PlatformSprites[0];

        rotatedBranch.Rotate(90.f);
        rotatedBranch.SetPosition(platformLocationX, platformLocationY - 25); //subtract 25 to make it line up properly
        m_VisibleTiles.push_back(rotatedBranch);
        rotatedBranch.Draw(l_window);

        if(m_LevelMap[tileIndex - m_LevelWidth] == '1')
        {
          m_PlatformSprites[1].SetPosition(platformLocationX, platformLocationY - 75);
          m_VisibleTiles.push_back(m_PlatformSprites[1]);
          m_PlatformSprites[1].Draw(l_window);
        }
      }

      tileIndex++;
    }
  }
}
