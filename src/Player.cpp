#include "Player.h"

Player::Player()
{
  m_CurrentMovement = PlayerMovement::Still;
  m_PlayerTexture.loadFromFile("../resources/images/BucketsTile.png");
  m_PlayerSprite.setTexture(m_PlayerTexture);

  // m_PlayerPosX = 5.0f;
  // m_PlayerPosY = 19.0f;
  //
  // m_PlayerSprite.setOrigin(m_PlayerPosX, m_PlayerPosY);

  //m_PlayerSprite.setPosition(m_PlayerPosX, m_PlayerPosY);
}

Player::~Player() { }

float Player::GetPlayerWidth()
{
  m_PlayerWidth = m_PlayerSprite.getGlobalBounds().width;
  return m_PlayerWidth;
}

float Player::GetPlayerHeight()
{
  m_PlayerHeight = m_PlayerSprite.getGlobalBounds().height;
  return m_PlayerHeight;
}

sf::Vector2f Player::GetPosition()
{
  //std::cout << "X: " << m_PlayerPosX << "\nY: " << m_PlayerPosY << std::endl;
  return { m_PlayerPosX, m_PlayerPosY };
}

void Player::AddAnimTexture(std::string txtrLocation)
{
  if(!m_PlayerTexture.loadFromFile(txtrLocation))
  {
    std::cout << "Failed to load file" << std::endl;
  }
  else
  {
    m_TxtrAnimBuff.push_back(m_PlayerTexture);
  }
}

void Player::SetPosition(float x, float y)
{
  m_PlayerPosX = x;
  m_PlayerPosY = y;
  m_PlayerSprite.setPosition(m_PlayerPosX, m_PlayerPosY);
}

void Player::SetPlayerMovement(PlayerMovement movement)
{
  m_CurrentMovement = movement;
}

PlayerMovement Player::GetPlayerMovement()
{
  return m_CurrentMovement;
}

void Player::MovePlayer()
{
  //std::cout << "Player X Position: " << m_PlayerPosX << std::endl;
  if(m_CurrentMovement == PlayerMovement::Right)
  {
    m_PlayerPosX += 5.0f;
    SetPosition(m_PlayerPosX, m_PlayerPosY);
    //std::cout << "I ran" << std::endl;
  }
  else if(m_CurrentMovement == PlayerMovement::Left)
  {
    m_PlayerPosX -= 5.0f;
    SetPosition(m_PlayerPosX, m_PlayerPosY);
  }
  else if(m_CurrentMovement == PlayerMovement::Up)
  {
    m_PlayerPosY -= 5.0f;
    SetPosition(m_PlayerPosX, m_PlayerPosY);
  }
  else if(m_CurrentMovement == PlayerMovement::Down)
  {
    m_PlayerPosY += 5.0f;
    SetPosition(m_PlayerPosX, m_PlayerPosY);
  }
  else if (m_CurrentMovement == PlayerMovement::Still)
  {
    m_PlayerPosX += 0.0f;
    SetPosition(m_PlayerPosX, m_PlayerPosY);
  }

}

void Player::CollisionCheck(std::vector<sf::Vector2i> collidableObjects)
{
  // std::cout << collidableObjects.size() << std::endl;
  // std::cout << "Player: " << m_PlayerPosX << ", " << m_PlayerPosY << std::endl;
  for(int i = 0; i < collidableObjects.size(); i++)
  {
    int objectWidth = 200; //This variable and objectHeight are specific to nectarine branch platform sprites
    int objectHeight = 75;  //I will likely need to rework things to fit other platform sizes (25x25 for example)
    int objectStartX = collidableObjects[i].x;
    int objectEndX = collidableObjects[i].x + objectWidth;
    int objectStartY = collidableObjects[i].y;
    int objectEndY = collidableObjects[i].y + objectHeight;

    if(m_PlayerPosX > objectStartX && m_PlayerPosX < objectEndX && m_PlayerPosY > objectStartY && m_PlayerPosY < objectEndY)
    {
      //m_IsColliding = true;
      switch (m_CurrentMovement)
      {
        case PlayerMovement::Right:
        m_PlayerPosX = objectStartX - m_PlayerWidth;
        break;
        case PlayerMovement::Left:
        m_PlayerPosX = objectEndX;
        break;
        case PlayerMovement::Up:
        // std::cout << "Player Y position before: " << m_PlayerPosY << std::endl;
        // std::cout << "Object Y position before: " << objectEndY << std::endl;
        // m_PlayerPosY = objectEndY;
        // std::cout << "Player Y position after: " << m_PlayerPosY << std::endl;
        // std::cout << "Object Y position after: " << objectEndY << std::endl;
        // std::cout << "**************************************************" << std::endl;
        break;
        case PlayerMovement::Down:
        m_PlayerPosY = objectStartY - m_PlayerHeight;
        break;
      }
      //std::cout << "Collision Detected" << std::endl;
    }
    if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX < objectEndX &&
      m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY < objectEndY)
      {
        //m_IsColliding = true;
        switch (m_CurrentMovement)
        {
          case PlayerMovement::Right:
          m_PlayerPosX = objectStartX - m_PlayerWidth;
          break;
          case PlayerMovement::Left:
          m_PlayerPosX = objectEndX;
          break;
          case PlayerMovement::Up:
          m_PlayerPosY = objectEndY;
          break;
          case PlayerMovement::Down:
          m_PlayerPosY = objectStartY - m_PlayerHeight;
          break;
        }
      }
      // else
      // {
      //   m_IsColliding = false;
      // }
      SetPosition(m_PlayerPosX, m_PlayerPosY);
    //std::cout << "Object " << i << ": " << collidableObjects[i].x << " , " << collidableObjects[i].y << std::endl;
  }
}

void Player::Draw(Window& l_window)
{
  int index = (int)GetPlayerMovement();
  m_PlayerSprite.setTexture(m_TxtrAnimBuff[0]);
  l_window.Draw(m_PlayerSprite);
}
