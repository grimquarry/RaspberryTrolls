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

std::vector<Fruit> Level::GetVisibleFruit()
{
  return m_VisibleFruit;
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

void Level::AddFruitSprite(Fruit& f) { m_FruitSprites.push_back(f); }

void Level::SetParallaxCam(sf::Vector2u winSize)
{

  m_ParallaxCamera.setSize( { (float)winSize.x, (float)winSize.y }/*{ (float)m_window.GetSize().x, (float)m_window.GetSize().y }*/);
}

void Level::SetBackgroundCenter(sf::Vector2f center)
{
  m_BackgroundCenter = center;
  m_ParallaxCamera.setCenter(center);
}

//fruitPos is the possion of a fruite that the player has collided with that's passed down from the
//CollisionHandler to let the Level object know to delete the fruit object from the map when the player collects it
void Level::HandleCollectedFruit(sf::Vector2f fruitPos)
{
  m_FruitCoordinates = fruitPos;
}

void Level::BuildFruitMap()
{
  int tileIndex = 0;
  for(int y = 0; y < m_LevelHeight; y++)
  {
    for(int x = 0; x < m_LevelWidth; x++)
    {
      int gridLocationX = x * 25; //The X axis incremets in spans of 25 pixels
      int gridLocationY = y * 75; //The Y axis increments in spans of 75 pixels
      if(m_LevelMap[tileIndex] == '4')
      {
        m_FruitSprites[0].SetPosition(gridLocationX, gridLocationY);
        m_FruitMap.push_back(m_FruitSprites[0]);
      }
      tileIndex++;
    }
  }
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

  l_window.SetView(view);

  m_VisibleTiles.clear();
  //Find and erase from the vector fruit that has been collected by player
  for(int i = 0; i < m_VisibleFruit.size(); ++i)
  {
    if(m_FruitMap[i].GetPosition() == m_FruitCoordinates)
    {
      m_FruitMap.erase(m_FruitMap.begin() + i);
    }
  }
  m_VisibleFruit.clear();

  for(int i = 0; i < m_FruitMap.size(); ++i)
  {
    if(m_FruitMap[i].GetPosition().x > minXView && m_FruitMap[i].GetPosition().y < maxXView)
    {
      m_VisibleFruit.push_back(m_FruitMap[i]);
      m_FruitMap[i].Draw(l_window);
    }

    //std::cout << "Player position: " << player.GetPosition().x << ", " << player.GetPosition().y << std::endl;
    std::cout << "Fruit Position is: " << m_VisibleFruit[i].GetPosition().x << ", " << m_VisibleFruit[i].GetPosition().y << std::endl;

  }

  for(int y = 0; y < m_LevelHeight; y++)
  {
    for(int x = 0; x < m_LevelWidth; x++)
    {
      int platformLocationX = x * 25; //The X axis incremets in spans of 25 pixels
      int platformLocationY = y * 75; //The Y axis increments in spans of 75 pixels
      if(m_LevelMap[tileIndex] == '0' && platformLocationX > minXView && platformLocationX < maxXView) // Nectarine branch
      {
        m_PlatformSprites[0].SetPosition(platformLocationX, platformLocationY);
        //std::cout << "Branch Platform Location is: " << m_PlatformSprites[0].GetPosition().x << ", " << m_PlatformSprites[0].GetPosition().y << std::endl;
        m_VisibleTiles.push_back(m_PlatformSprites[0]);
        m_PlatformSprites[0].Draw(l_window);

        if(m_LevelMap[tileIndex - 2] == '1') //Look for nectarine blossoms and offset appropriately
        {
          m_PlatformSprites[1].SetPosition(platformLocationX - 50, platformLocationY);
          m_VisibleTiles.push_back(m_PlatformSprites[1]);
          m_PlatformSprites[1].Draw(l_window);
        }

      }
      else if(m_LevelMap[tileIndex] == '1' && platformLocationX > minXView && platformLocationX < maxXView) //Nectarine Blossom 1
      {
        m_PlatformSprites[1].SetPosition(platformLocationX, platformLocationY);
        m_VisibleTiles.push_back(m_PlatformSprites[1]);
        m_PlatformSprites[1].Draw(l_window);
      }
      else if(m_LevelMap[tileIndex] == '2' && platformLocationX > minXView && platformLocationX < maxXView) //Rotated Nectarine Branch
      {
        m_PlatformSprites[2].SetPosition(platformLocationX, platformLocationY - 25); //subtract 25 to make it line up properly
        m_VisibleTiles.push_back(m_PlatformSprites[2]);
        m_PlatformSprites[2].Draw(l_window);

        if(m_LevelMap[tileIndex - m_LevelWidth] == '1') //Looking for Nectarine blossoms above the rotated nectarine branch and offset accordingling
        {
          m_PlatformSprites[1].SetPosition(platformLocationX, platformLocationY - 75);
          m_VisibleTiles.push_back(m_PlatformSprites[1]);
          m_PlatformSprites[1].Draw(l_window);
        }
        if(m_LevelMap[tileIndex - 2] == '1') // Looking for nectarine blossoms to the left
        {
          m_PlatformSprites[1].SetPosition(platformLocationX - 50, platformLocationY);
          m_VisibleTiles.push_back(m_PlatformSprites[1]);
          m_PlatformSprites[1].Draw(l_window);
        }
        if(m_LevelMap[tileIndex - 2] == '3') // Looking for nectarineleaves1
        {
          m_PlatformSprites[3].SetPosition(platformLocationX - 60, platformLocationY - 30);
          m_VisibleTiles.push_back(m_PlatformSprites[3]);
          m_PlatformSprites[3].Draw(l_window);
        }
      }
      else if(m_LevelMap[tileIndex] == '3' && platformLocationX > minXView && platformLocationX < maxXView) //Nectarine Leaves
      {
        //std::cout << "Leaf Platform Location is: " << m_PlatformSprites[0].GetPosition().x << ", " << m_PlatformSprites[0].GetPosition().y << std::endl;
        if(m_LevelMap[tileIndex + 2] != '2')
        {
          m_PlatformSprites[3].SetPosition(platformLocationX, platformLocationY);
          m_VisibleTiles.push_back(m_PlatformSprites[3]);
          m_PlatformSprites[3].Draw(l_window);
        }
      }
      // else if(m_LevelMap[tileIndex] == '4' && platformLocationX > minXView && platformLocationX < maxXView)
      // {
      //   m_FruitSprites[0].SetPosition(platformLocationX, platformLocationY);
      //   //std::cout << "Fruit Position is: " << m_FruitSprites[0].GetPosition().x << ", " << m_FruitSprites[0].GetPosition().y << std::endl;
      //   m_VisibleFruit.push_back(m_FruitSprites[0]);
      //
      //   //m_FruitSprites[0].Draw(l_window);
      // }
      tileIndex++;
    }
  }
}
