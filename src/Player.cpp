#include "Player.h"

Player::Player()
{
  m_CurrentMovement = PlayerMovement::Still;
  m_PreviousMovement = PlayerMovement::Still;
  m_StopXDirection = PlayerMovement::Still;
  m_AnimationAction = PlayerAction::None;

  //m_PlayerTexture and m_PlayerSprite are commented out because this is now
  //handled in the Game class construtor using the AddAnimTexture and
  //HandleAnimTexture Player class methods.  Keeping for reference, but can remove later.
  // m_PlayerTexture.loadFromFile("../resources/images/BucketsMovement_0.png");
  // m_PlayerSprite.setTexture(m_PlayerTexture);

  m_PlayerVelX = 0.0f;
  m_PlayerVelY = 5.0f;

  m_OnGround = false;
  m_LeftCollision = false;
  m_RightCollision = false;
  m_IsRunning = false;
  m_IsWalking = false;
  m_IsJumping = false;
  m_IsLanding = false;

  m_MinXVelocity = 6;
  m_MaxXVelocity = m_MinXVelocity;
  m_MinYVelocity = 3.0f;
  m_MaxYVelocity = 7.0f;

  //Walk and Run Player Action animation iterates through the m_TxtrAnimBuff
  //(Texture Animation Buffer).  Index 0 is for No action and indexes 1 - 13
  //are for walking and running.  We set the iterator to 1 because that's the
  //first frame in the animation series.
  m_WalkAnimItr = 1;
  m_FrameCount = 0;
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

void Player::HandleAnimTexture()
{
  if(m_IsWalking && m_IsRunning)
  {
    m_IsRunning = false;
  }

  std::cout << "_____________________________________________________________________" << std::endl;
  for(int i = 0; i < m_ActionsBuffer.size(); ++i)
  {
    std::cout << static_cast<std::underlying_type<PlayerAction>::type>(m_ActionsBuffer[i]) << std::endl;
  }
  std::cout << "_____________________________________________________________________" << std::endl;
  if(m_CurrentMovement == PlayerMovement::Still)
  {
    m_PlayerSprite.setTexture(m_TxtrAnimBuff[0]);
  }
  else if(m_IsWalking || m_IsRunning)
  {
    if(m_WalkAnimItr < 1 || m_WalkAnimItr > 13)
    {
      m_WalkAnimItr = 1;
    }
    m_PlayerSprite.setTexture(m_TxtrAnimBuff[m_WalkAnimItr]);

    m_FrameCount++;
    if(m_FrameCount > 60)
    {
      m_FrameCount = 1;
    }

    if(m_FrameCount > 2 && m_FrameCount % 3 == 0 && m_IsRunning)
    {
      m_WalkAnimItr++;
    }
    else if(m_FrameCount > 4 && m_FrameCount % 5 == 0 && !m_IsRunning)
    {
      m_WalkAnimItr++;
    }
  }
}

/****Commenting out this code because it's beastly and replaced above, but keeping for now in case it's needed for reference****/
// void Player::HandleAnimTexture()
// {
//   if(!m_ActionsBuffer.empty())
//   {
//     bool b_checkActions = true;
//     int itr = 0;
//     while(b_checkActions)
//     {
//       if(itr > b_checkActions)
//       {
//         m_AnimationAction = PlayerAction::None;
//         b_checkActions = false;
//       }
//       else if(m_ActionsBuffer[itr] == PlayerAction::Walk && m_CurrentMovement == PlayerMovement::Right ||
//         m_ActionsBuffer[itr] == PlayerAction::Walk && m_CurrentMovement == PlayerMovement::Left)
//       {
//         m_AnimationAction = PlayerAction::Walk;
//         b_checkActions = false;
//       }
//       else if(m_ActionsBuffer[itr] == PlayerAction::Run && m_CurrentMovement == PlayerMovement::Right ||
//         m_ActionsBuffer[itr] == PlayerAction::Run && m_CurrentMovement == PlayerMovement::Left)
//       {
//         m_AnimationAction = PlayerAction::Run;
//         b_checkActions = false;
//       }
//       itr++;
//     }
//
//     // std::cout << "_____________________________________________________________________" << std::endl;
//     // for(int i = 0; i < m_ActionsBuffer.size(); ++i)
//     // {
//     //   std::cout << static_cast<std::underlying_type<PlayerAction>::type>(m_ActionsBuffer[i]) << std::endl;
//     //   if(m_ActionsBuffer[i] == PlayerAction::Walk && m_CurrentMovement == PlayerMovement::Right ||
//     //     m_ActionsBuffer[i] == PlayerAction::Walk && m_CurrentMovement == PlayerMovement::Left)
//     //   {
//     //     m_AnimationAction = PlayerAction::Walk;
//     //     std::cout << "Condition met" << static_cast<std::underlying_type<PlayerAction>::type>(m_ActionsBuffer[i]) << std::endl;
//     //   }
//     //   else /*if(m_ActionsBuffer[i] == PlayerAction::None && m_CurrentMovement == PlayerMovement::Still)*/
//     //   {
//     //     m_AnimationAction = PlayerAction::None;
//     //   }
//     // }
//   }
//   // else
//   // {
//   //   std::cout << "Actions Buffer empty" << std::endl;
//   // }
//   // std::cout << "_____________________________________________________________________" << std::endl;
//
//   // std::cout << static_cast<std::underlying_type<PlayerAction>::type>(m_AnimationAction) << std::endl;
//   // if(!m_ActionsBuffer.empty())
//   // {
//   //   for(int i = 0; i < m_ActionsBuffer.size(); ++i)
//   //   {
//   //     if(m_ActionsBuffer[i] == PlayerAction::None)
//   //     {
//   //       m_PlayerSprite.setTexture(m_TxtrAnimBuff[0]);
//   //     }
//   //     else if(m_ActionsBuffer[i] == PlayerAction::Walk)
//   //     {
//   //       if(m_WalkAnimItr < 1 || m_WalkAnimItr > 13)
//   //       {
//   //         m_WalkAnimItr = 1;
//   //       }
//   //       m_PlayerSprite.setTexture(m_TxtrAnimBuff[m_WalkAnimItr]);
//   //       m_WalkAnimItr++;
//   //     }
//   //   }
//   // }
//
//   switch (m_AnimationAction){
//     case PlayerAction::None :
//       m_PlayerSprite.setTexture(m_TxtrAnimBuff[0]);
//     break;
//     case PlayerAction::Walk :
//       if(m_WalkAnimItr < 1 || m_WalkAnimItr > 13)
//       {
//         m_WalkAnimItr = 1;
//       }
//       m_PlayerSprite.setTexture(m_TxtrAnimBuff[m_WalkAnimItr]);
//
//       m_FrameCount++;
//       if(m_FrameCount > 60)
//       {
//         m_FrameCount = 1;
//       }
//
//       if(m_FrameCount > 2 && m_FrameCount % 3 == 0 && m_IsRunning)
//       {
//         m_WalkAnimItr++;
//       }
//       else if(m_FrameCount > 4 && m_FrameCount % 5 == 0 && !m_IsRunning)
//       {
//         m_WalkAnimItr++;
//       }
//     break;
//     case PlayerAction::Run :
//       if(m_WalkAnimItr < 1 || m_WalkAnimItr > 13)
//       {
//         m_WalkAnimItr = 1;
//       }
//       m_PlayerSprite.setTexture(m_TxtrAnimBuff[m_WalkAnimItr]);
//
//       m_FrameCount++;
//       if(m_FrameCount > 60)
//       {
//         m_FrameCount = 1;
//       }
//
//       if(m_FrameCount > 2 && m_FrameCount % 3 == 0)
//       {
//         m_WalkAnimItr++;
//       }
//       // else if(m_FrameCount > 4 && m_FrameCount % 5 == 0 && !m_IsRunning)
//       // {
//       //   m_WalkAnimItr++;
//       // }
//     break;
//   // if(m_AnimationAction == PlayerAction::None)
//   // {
//   //   m_PlayerSprite.setTexture(m_TxtrAnimBuff[0]);
//   // }
//   }
// }


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
  m_ActionsBuffer.push_back(action);
  if(action == PlayerAction::Walk)
  {
    m_AnimationAction = action;
  }
}
void Player::ClearPlayerActions()
{
  m_ActionsBuffer.clear();
}

void Player::MovePlayer(float timeElapsed)
{
  //Account for player actions before they move
  if(!m_ActionsBuffer.empty())
  {
    bool b_checkRunFlag = true;
    int itr = 0;
    while(b_checkRunFlag)
    {
      if(itr > m_ActionsBuffer.size())
      {
        m_IsRunning = false;
        b_checkRunFlag = false;
      }
      else if(m_ActionsBuffer[itr] == PlayerAction::Run)
      {
        m_IsRunning = true;
        b_checkRunFlag = false;
      }
      itr++;
    }

    itr = 0;
    bool b_checkWalkFlag = true;
    while(b_checkWalkFlag)
    {
      if(itr > m_ActionsBuffer.size())
      {
        m_IsWalking = false;
        b_checkWalkFlag = false;
      }
      else if(m_ActionsBuffer[itr] == PlayerAction::Walk)
      {
        m_IsWalking = true;
        m_IsRunning = false;
        b_checkWalkFlag = false;
      }
      itr++;
    }

    for(int i = 0; i < m_ActionsBuffer.size(); ++i)
    {
      //std::cout << static_cast<std::underlying_type<PlayerAction>::type>(m_ActionsBuffer[i]) << std::endl;
      // if(m_ActionsBuffer[i] == PlayerAction::Run)
      // {
      //   m_IsRunning = true;
      // }
      // else if(m_ActionsBuffer[i] == PlayerAction::Walk)
      // {
      //   m_IsRunning = false;
      // }

      if(m_ActionsBuffer[i] == PlayerAction::Jump)
      {
        m_IsJumping = true;
      }
      if(m_ActionsBuffer[i] == PlayerAction::Land)
      {
        m_IsLanding = true;
      }
    }
  }

  if(m_IsJumping)
  {
    if(m_OnGround)
    {
      m_PlayerVelY = -1 * m_MaxYVelocity;
    }
    else if(!m_OnGround)
    {
      m_PlayerVelY += 0.20f;
    }
    if(m_OnGround && m_IsLanding)
    {
      m_PlayerVelY = m_MinYVelocity;
      m_IsJumping = false;
      m_IsLanding = false;
    }
    m_PlayerPosY += (m_PlayerVelY * timeElapsed);
  }


  if(m_IsRunning)
  {
    m_MaxXVelocity = 10.0f;
  }
  else if(!m_IsRunning)
  {
    if(m_MaxXVelocity > m_MaxXVelocity)
    {
      m_MaxXVelocity -= .5f;
    }
    else
    {
      m_MaxXVelocity = m_MinXVelocity;
    }
  }

  //Give player based on directive new position
  if(m_CurrentMovement == PlayerMovement::Right)
  {
    if(m_PreviousMovement != PlayerMovement::Right)
    {
      m_PlayerSprite.setScale({1, 1});
      m_PlayerSprite.setOrigin(0.f, 0.f);
    }
    ChangeXVelocity();
    m_PlayerPosX += (m_PlayerVelX * timeElapsed);
  }
  else if(m_CurrentMovement == PlayerMovement::Left)
  {
    if(m_PreviousMovement != PlayerMovement::Left)
    {
      m_PlayerSprite.setScale({-1, 1});
      m_PlayerSprite.setOrigin((float)m_PlayerWidth, 0.0f); //Change origin for smoother animation when changing direction from right to left.
    }
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
    //!!!!!!!!!!!!!!Logic for this needs fixing, I think by adding m_IsLanding conditions!!!!!!!!!!!!!!!!!!!!!!!
    if(m_IsJumping)
    {
      if(m_StopXDirection == PlayerMovement::Right)
      {
        std::cout << "Ran" << std::endl;
        m_PlayerPosX += m_PlayerVelX * timeElapsed;
      }
      if(m_StopXDirection == PlayerMovement::Left)
      {
        m_PlayerPosX -= m_PlayerVelX * timeElapsed;
      }
    }
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

// void Player::Jump(float timeElapsed)
// {
//   m_PlayerPosY -= 10.f;
// }

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
    if(!m_ActionsBuffer.empty())
    {
      for(int i = 0; i < m_ActionsBuffer.size(); ++i)
      {
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
        //Account for collisions on the player's upper right
        else if(m_PlayerPosX > objectStartX && m_PlayerPosX < objectEndX &&
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
    }

    switch(m_CurrentMovement){
      case PlayerMovement::Right:
        //I could have put all this in a large if statement, but decided to break it up with if/else, which probably isn't good
        //practice despite making it easier to read.  There's got to be a better way of doing this, though.
        //Foot Collision
        if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX
          && m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY + m_PlayerHeight < objectEndY)
          {
            //m_RightCollision = true;
            m_PlayerPosX = objectStartX - m_PlayerWidth;
            m_MaxXVelocity = m_MinXVelocity;
          }
        //Head Collision
        else if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX
        && m_PlayerPosY > objectStartY && m_PlayerPosY < objectEndY)
        {
          //m_RightCollision = true;
          m_PlayerPosX = objectStartX - m_PlayerWidth;
          m_MaxXVelocity = m_MinXVelocity;
        }
        //Body Collision (player midpoint, which is needed because the player can be taller than the platform)
        else if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX
        && m_PlayerPosY + (m_PlayerHeight / 2) > objectStartY && m_PlayerPosY + (m_PlayerHeight / 2) < objectEndY)
        {
          //m_RightCollision = true;
          m_PlayerPosX = objectStartX - m_PlayerWidth;
          m_MaxXVelocity = m_MinXVelocity;
        }
      break;
      case PlayerMovement::Left:
        //Foot Collision
        if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
          m_PlayerPosY + m_PlayerHeight < objectEndY && m_PlayerPosY + m_PlayerHeight > objectStartY)
          {
            //m_LeftCollision = true;
            m_PlayerPosX = objectEndX;
            m_MaxXVelocity = m_MinXVelocity;
          }
        //Head Collision
        else if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
          m_PlayerPosY < objectEndY && m_PlayerPosY > objectStartY)
          {
            //m_LeftCollision = true;
            m_PlayerPosX = objectEndX;
            m_MaxXVelocity = m_MinXVelocity;
          }
        //Body Collision
        else if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
          m_PlayerPosY + (m_PlayerHeight / 2) < objectEndY && m_PlayerPosY + (m_PlayerHeight / 2) > objectStartY)
          {
            //m_LeftCollision = true;
            m_PlayerPosX = objectEndX;
            m_MaxXVelocity = m_MinXVelocity;
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
      //The code for this below was lifted from both the PlayerMovement::Right and PlayerMovement::Left cases above.
      //Probably not the most eloquent solution, but it's necessary because the player can still be moving
      //when they're "standing still" (due to changing velocity to give the effect of player momentum).  I suspect
      //this could be refactored to be more effecient, but don't currently have good ideas on that, so
      //I'll leave as is for now, and maybe revisit.
      //Left Foot Collision
      if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
        m_PlayerPosY + m_PlayerHeight < objectEndY && m_PlayerPosY + m_PlayerHeight > objectStartY)
        {
          m_PlayerPosX = objectEndX;
          m_MaxXVelocity = m_MinXVelocity;
        }
      //Left Head Collision
      else if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
        m_PlayerPosY < objectEndY && m_PlayerPosY > objectStartY)
        {
          m_PlayerPosX = objectEndX;
          m_MaxXVelocity = m_MinXVelocity;
        }
      //Left Body Collision
      else if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
        m_PlayerPosY + (m_PlayerHeight / 2) < objectEndY && m_PlayerPosY + (m_PlayerHeight / 2) > objectStartY)
        {
          m_PlayerPosX = objectEndX;
          m_MaxXVelocity = m_MinXVelocity;
        }

        //Right Foot Collision
        if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX
          && m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY + m_PlayerHeight < objectEndY)
          {
            m_PlayerPosX = objectStartX - m_PlayerWidth;
            m_MaxXVelocity = m_MinXVelocity;
          }
        //Right Head Collision
        else if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX
        && m_PlayerPosY > objectStartY && m_PlayerPosY < objectEndY)
        {
          m_PlayerPosX = objectStartX - m_PlayerWidth;
          m_MaxXVelocity = m_MinXVelocity;
        }
        //Right Body Collision (player midpoint, which is needed because the player can be taller than the platform)
        else if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX
        && m_PlayerPosY + (m_PlayerHeight / 2) > objectStartY && m_PlayerPosY + (m_PlayerHeight / 2) < objectEndY)
        {
          m_PlayerPosX = objectStartX - m_PlayerWidth;
          m_MaxXVelocity = m_MinXVelocity;
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
    //Determine if player is flush with a platfrom to his Left or Right.
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
  //m_PlayerSprite.setTexture(m_TxtrAnimBuff[0]);
  HandleAnimTexture();
  l_window.Draw(m_PlayerSprite);
}

void Player::ChangeXVelocity()
{
  m_PlayerVelX += 0.5f;
  if(m_PlayerVelX > m_MaxXVelocity)
  {
    m_PlayerVelX = m_MaxXVelocity;
  }
}
