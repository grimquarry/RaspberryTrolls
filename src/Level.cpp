#include "Level.h"
#include <iostream>

Level::Level()
{
  if(!texture.loadFromFile("../resources/images/nectarineBranch_2.png"))
  {
    std::cout << "Failed to load file" << std::endl;
  }
  sprite.setTexture(texture);

  sLevelMap += "-...............................................................";
  sLevelMap += ".--.............................................................";
  sLevelMap += "...---..........................................................";
  sLevelMap += "......----......................................................";
  sLevelMap += "...---..........................................................";
  sLevelMap += ".--.............................................................";
  sLevelMap += "-...............................................................";
  sLevelMap += ".--.............................................................";
  sLevelMap += "...---..........................................................";
  sLevelMap += "......----......................................................";
  sLevelMap += "................................................................";
  sLevelMap += "-...............................................................";
  sLevelMap += "--..............................................................";
  sLevelMap += "--.---..........................................................";
  std::cout << sLevelMap << std::endl;

}

Level::~Level()
{

}

std::vector<sf::Vector2i> Level::GetVisiblePlatforms()
{
  return m_visibleTileCoords;
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
      if(sLevelMap[tileIndex] == '-' && platformLocationX > minXView && platformLocationX < maxXView)
      {
        sprite.setPosition(platformLocationX, platformLocationY);
        m_visibleTileCoords.push_back({platformLocationX, platformLocationY});
        //std::cout << "\nX: " << x*200 << "\nY: " << y * 75 << std::endl;
        //std::cout << tileIndex << std::endl;
        l_window.Draw(sprite);
      }
      tileIndex++;
    }
  }

}
