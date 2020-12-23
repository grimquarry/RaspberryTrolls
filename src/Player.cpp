#include "Player.h"

Player::Player()
{
  m_CurrentMovement = PlayerMovement::Still;
  m_PreviousMovement = PlayerMovement::Still;
  m_StopXDirection = PlayerMovement::Still;
  m_CurrentAction = PlayerAction::None;
  m_PlayerTexture.loadFromFile("../resources/images/BucketsTile.png");
  m_PlayerSprite.setTexture(m_PlayerTexture);

  m_PlayerVelX = 0.0f;
  m_PlayerVelY = 5.0f;
  m_Gravity = 5.f;

  m_OnGround = false;
  m_LeftCollision = false;
  m_RightCollision = false;
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
  m_PreviousMovement = m_CurrentMovement;
  m_CurrentMovement = movement;
}

PlayerMovement Player::GetPlayerMovement()
{
  return m_CurrentMovement;
}

void Player::SetPlayerAction(PlayerAction action)
{
  m_CurrentAction = action;
}

void Player::MovePlayer(float timeElapsed)
{
  //Give player based on directive new position
  if(m_CurrentMovement == PlayerMovement::Right)
  {
    ChangeXVelocity();
    m_PlayerPosX += (m_PlayerVelX * timeElapsed);
  }
  else if(m_CurrentMovement == PlayerMovement::Left)
  {
    ChangeXVelocity();
    m_PlayerPosX -= (m_PlayerVelX * timeElapsed);
  }
  else if(m_CurrentMovement == PlayerMovement::Up)
  {
    m_PlayerPosY -= (m_PlayerVelY * timeElapsed);
  }
  else if(m_CurrentMovement == PlayerMovement::Down)
  {
    m_PlayerPosY += (m_PlayerVelY * timeElapsed);
  }
  else if (m_CurrentMovement == PlayerMovement::Still)
  {
    if(m_PlayerVelX != 0.f && !m_LeftCollision && !m_RightCollision)
    {
      if(m_PreviousMovement == PlayerMovement::Left)
      {
        m_StopXDirection = PlayerMovement::Left;
      }
      else if(m_PreviousMovement == PlayerMovement::Right)
      {
        m_StopXDirection = PlayerMovement::Right;
      }

      m_PlayerVelX -= 0.5f;

      if(m_StopXDirection == PlayerMovement::Left)
      {
        m_PlayerPosX -= m_PlayerVelX * timeElapsed;
      }
      else if(m_StopXDirection == PlayerMovement::Right)
      {
        m_PlayerPosX += m_PlayerVelX * timeElapsed;
      }
      else if(m_LeftCollision || m_RightCollision)
      {
        m_PlayerVelX = 0;
      }

    }

  }
  //Put player in the new postion
  SetPosition(m_PlayerPosX, m_PlayerPosY);
}

void Player::Jump(float timeElapsed)
{
  m_PlayerPosY -= 10.f;
}

void Player::CollisionCheck(std::vector<sf::Vector2i> collidableObjects)
{
  m_OnGround = false;
  m_LeftCollision = false;
  m_RightCollision = false;
  for(int i = 0; i < collidableObjects.size(); i++)
  {
    int objectWidth = 200; //This variable and objectHeight are specific to nectarine branch platform sprites
    int objectHeight = 75;  //I will likely need to rework things to fit other platform sizes (25x25 for example)
    int objectStartX = collidableObjects[i].x;
    int objectEndX = collidableObjects[i].x + objectWidth;
    int objectStartY = collidableObjects[i].y;
    int objectEndY = collidableObjects[i].y + objectHeight;

    //Using if instead of switch because there can be more than one action.
    if(m_CurrentAction == PlayerAction::Jump)
    {
      //std::cout << "Triggered" << std::endl;
      if(m_PlayerPosX > objectStartX && m_PlayerPosX < objectEndX &&
        m_PlayerPosY > objectStartY && m_PlayerPosY < objectEndY)
        {
          m_PlayerPosY = objectEndY;
        }
      //Account for collisions on the player's upper left
      else if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX &&
        m_PlayerPosY > objectStartY && m_PlayerPosY < objectEndY)
        {
          m_PlayerPosY = objectEndY;
        }
    }

    switch(m_CurrentMovement){
      case PlayerMovement::Right:
        //I could have put all this in a large if statement, but decided to break it up with if/else, which probably isn't good
        //practice despite making it easier to read.  There's got to be a better way of doing this, though.
        //Foot Collision
        if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX
          && m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY + m_PlayerHeight < objectEndY)
          {
            m_PlayerPosX = objectStartX - m_PlayerWidth;
          }
        //Head Collision
        else if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX
        && m_PlayerPosY > objectStartY && m_PlayerPosY < objectEndY)
        {
          m_PlayerPosX = objectStartX - m_PlayerWidth;
        }
        //Body Collision (player midpoint, which is needed because the player can be taller than the platform)
        else if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX
        && m_PlayerPosY + (m_PlayerHeight / 2) > objectStartY && m_PlayerPosY + (m_PlayerHeight / 2) < objectEndY)
        {
          m_PlayerPosX = objectStartX - m_PlayerWidth;
        }
      break;
      case PlayerMovement::Left:
        //Foot Collision
        if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
          m_PlayerPosY + m_PlayerHeight < objectEndY && m_PlayerPosY + m_PlayerHeight > objectStartY)
          {
            m_LeftCollision = true;
            m_PlayerPosX = objectEndX;
          }
        //Head Collision
        else if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
          m_PlayerPosY < objectEndY && m_PlayerPosY > objectStartY)
          {
            m_PlayerPosX = objectEndX;
          }
        //Body Collision
        else if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
          m_PlayerPosY + (m_PlayerHeight / 2) < objectEndY && m_PlayerPosY + (m_PlayerHeight / 2) > objectStartY)
          {
            m_PlayerPosX = objectEndX;
          }
      break;
      case PlayerMovement::Up:
        //Account for collisions on the player's upper right
        if(m_PlayerPosX > objectStartX && m_PlayerPosX < objectEndX &&
          m_PlayerPosY > objectStartY && m_PlayerPosY < objectEndY)
          {
            m_PlayerPosY = objectEndY;
          }
        //Account for collisions on the player's upper left
        else if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX &&
          m_PlayerPosY > objectStartY && m_PlayerPosY < objectEndY)
          {
            m_PlayerPosY = objectEndY;
          }
      break;
      case PlayerMovement::Down:
        //Account for collsions on player's lower left
        if(m_PlayerPosX > objectStartX && m_PlayerPosX < objectEndX &&
          m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY + m_PlayerHeight < objectEndY)
          {
            m_PlayerPosY = objectStartY - m_PlayerHeight;
          }
        //Account for collsions on player's lower right
        else if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX &&
          m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY + m_PlayerHeight < objectEndY)
          {
            m_PlayerPosY = objectStartY - m_PlayerHeight;
          }
      break;
      case PlayerMovement::Still:
      //Account for collsions on player's lower left
      if(m_PlayerPosX > objectStartX && m_PlayerPosX < objectEndX &&
        m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY + m_PlayerHeight < objectEndY)
        {
          m_PlayerPosY = objectStartY - m_PlayerHeight;
        }
      //Account for collsions on player's lower right
      else if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX &&
        m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY + m_PlayerHeight < objectEndY)
        {
          m_PlayerPosY = objectStartY - m_PlayerHeight;
        }
      break;
    }

    //Determine if player is on ground or not.  m_OnGround is used/returned by the bool OnGround method
    if(objectStartY - m_PlayerHeight == m_PlayerPosY && m_PlayerPosX > objectStartX && m_PlayerPosX < objectEndX)
    {
      m_OnGround = true;
    }
    else if(objectStartY - m_PlayerHeight == m_PlayerPosY && m_PlayerPosX + m_PlayerWidth < objectEndX&& m_PlayerPosX > objectStartX)
    {
      m_OnGround = true;
    }
    //Determine if player is flush with a platfrom to his Left or Right
    if(m_PlayerPosX == objectEndX)
    {
      m_LeftCollision = true;
    }
    else if(m_PlayerPosX + m_PlayerWidth == objectStartX)
    {
      m_RightCollision = true;
    }
  }

  SetPosition(m_PlayerPosX, m_PlayerPosY);
}

bool Player::OnGround()
{
  return m_OnGround;
}
//Commenting out because m_OnGround flag is set with collision checks, but not sure if new solution has bugs or not.
// bool Player::GetOnGround(std::vector<sf::Vector2i> platformObjects)
// {
//   for(int i = 0; i < platformObjects.size(); ++i)
//   {
//     int objectWidth = 200; //This variable and objectHeight are specific to nectarine branch platform sprites
//     int objectHeight = 75;  //I will likely need to rework things to fit other platform sizes (25x25 for example)
//     int objectStartX = platformObjects[i].x;
//     int objectEndX = platformObjects[i].x + objectWidth;
//     int objectStartY = platformObjects[i].y;
//     int objectEndY = platformObjects[i].y + objectHeight;
//     if(objectStartY - m_PlayerHeight == m_PlayerPosY && m_PlayerPosX > objectStartX && m_PlayerPosX < objectEndX)
//     {
//       m_OnGround = true;
//       return true;
//     }
//     else if(objectStartY - m_PlayerHeight == m_PlayerPosY && m_PlayerPosX + m_PlayerWidth < objectEndX&& m_PlayerPosX > objectStartX)
//     {
//       m_OnGround = true;
//       return true;
//     }
//   }
//   m_OnGround = false;
//   return false;
// }

void Player::Draw(Window& l_window)
{
  int index = (int)GetPlayerMovement();
  m_PlayerSprite.setTexture(m_TxtrAnimBuff[0]);
  l_window.Draw(m_PlayerSprite);
}

void Player::ChangeXVelocity()
{
  m_PlayerVelX += 0.5f;
  if(m_PlayerVelX > 6)
  {
    m_PlayerVelX = 6;
  }
}
