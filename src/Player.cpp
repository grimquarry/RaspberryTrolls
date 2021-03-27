#include "Player.h"

Player::Player()
{
  m_CurrentMovement = PlayerMovement::Still;
  m_PreviousMovement = PlayerMovement::Still;
  m_StopXDirection = PlayerMovement::Right;
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
  m_IgnoreJump = false;

  m_MinXVelocity = 6;
  m_MaxXVelocity = m_MinXVelocity;
  m_MinYVelocity = 3.0f;
  m_MaxYVelocity = 6.0f;

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

void Player::WalkAnimation()
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

void Player::HandleAnimTexture()
{
  /*Uncomment Below to test what's in the Actions Buffer at the point this method is called for troubleshooting*/
  // std::cout << "_____________________________________________________________________" << std::endl;
  // for(int i = 0; i < m_ActionsBuffer.size(); ++i)
  // {
  //   std::cout << static_cast<std::underlying_type<PlayerAction>::type>(m_ActionsBuffer[i]) << std::endl;
  // }
  // std::cout << "_____________________________________________________________________" << std::endl;
  if(m_CurrentMovement == PlayerMovement::Still && !m_IsJumping)
  {
    m_PlayerSprite.setTexture(m_TxtrAnimBuff[0]);
  }
  else if(m_IsJumping && !m_OnGround)
  {
    //std::cout << "Jump ran" << std::endl;
    m_PlayerSprite.setTexture(m_TxtrAnimBuff[14]);
  }
  else if(m_IsWalking && !m_IgnoreJump || m_IsRunning && !m_IgnoreJump)
  {
    WalkAnimation();
  }
  else if(m_IsJumping && m_IgnoreJump)
  {
    if(m_CurrentMovement == PlayerMovement::Still)
    {
      m_PlayerSprite.setTexture(m_TxtrAnimBuff[0]);
    }
    else if(m_IsWalking || m_IsRunning)
    {
      WalkAnimation();
    }
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
  m_PreviousPosX = m_PlayerPosX; //Needed for jump collision detection logic
  m_PreviousPosY = m_PlayerPosY; //Needed for jump collision detection logic
  //Account for player actions before they move
  if(!m_ActionsBuffer.empty())
  {
    // std::cout << "_____________________________________________________________________" << std::endl;
    // for(int i = 0; i < m_ActionsBuffer.size(); ++i)
    // {
    //   std::cout << static_cast<std::underlying_type<PlayerAction>::type>(m_ActionsBuffer[i]) << std::endl;
    // }
    // std::cout << "_____________________________________________________________________" << std::endl;
    for(int i = 0; i < m_ActionsBuffer.size(); ++i)
    {
      if(m_ActionsBuffer[i] == PlayerAction::Walk)
      {
        m_IsWalking = true;
        m_IsRunning = false;
      }
      else if(m_ActionsBuffer[i] == PlayerAction::Run)
      {
        m_IsRunning = true;
        m_IsWalking = false;
      }
      if(m_ActionsBuffer[i] == PlayerAction::Jump)
      {
        m_IsJumping = true;
      }
      if(m_ActionsBuffer[i] == PlayerAction::Land)
      {
        m_IsLanding = true;
        m_IgnoreJump = false;
      }
    }
  }

  if(m_IsJumping)
  {
    if(!m_IgnoreJump)
    {
      if(m_IsRunning && m_OnGround)
      {
        m_PlayerVelY = -12;
        m_IgnoreJump = true;
      }
      else if(m_IsWalking && m_OnGround)
      {
        m_PlayerVelY = -9;
        m_IgnoreJump = true;
      }
    }
    if(m_IsLanding)
    {
      m_PlayerVelY += 0.5;
      m_IgnoreJump = true;
    }
    // else if(!m_OnGround)
    // {
    //   //m_PlayerVelY += m_MaxYVelocity;
    //   //m_PlayerVelY += 0.20f;
    //   //m_PlayerVelX = m_MaxXVelocity;
    // }
    if(m_OnGround && m_IsLanding)
    {
      m_PlayerVelY = m_MinYVelocity;
      m_IsJumping = false;
      m_IsLanding = false;
      m_IgnoreJump = false;
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

  //Give player new position based on directive
  if(m_CurrentMovement == PlayerMovement::Right)
  {
    m_StopXDirection = PlayerMovement::Right;
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
    m_StopXDirection = PlayerMovement::Left;
    if(m_PreviousMovement != PlayerMovement::Left)
    {
      m_PlayerSprite.setScale({-1, 1});
      m_PlayerSprite.setOrigin((float)m_PlayerWidth, 0.0f); //Change origin for smoother animation when changing direction from right to left.
    }
    ChangeXVelocity();
    m_PlayerPosX -= (m_PlayerVelX * timeElapsed);
  }
  //Lines below commented out because they shouldn't do anything at this point (revist when duck and climb directives are created)
  else if(m_CurrentMovement == PlayerMovement::Up)
  {
    m_PlayerPosY -= (m_PlayerVelY * timeElapsed);
  }
  else if(m_CurrentMovement == PlayerMovement::Down)
  {
    if(m_IsRunning)
    {
      m_PlayerVelY += 0.90f;
    }
    else
    {
      m_PlayerVelY += 0.50f;
    }
    m_PlayerPosY += (m_PlayerVelY * timeElapsed);
  }
  else if (m_CurrentMovement == PlayerMovement::Still)
  {
    // if(m_IsJumping)
    // {
    //   ChangeXVelocity();
    //   if(m_StopXDirection == PlayerMovement::Right)
    //   {
    //     //std::cout << "Ran" << std::endl;
    //     m_PlayerPosX += m_PlayerVelX * timeElapsed;
    //   }
    //   if(m_StopXDirection == PlayerMovement::Left)
    //   {
    //     m_PlayerPosX -= m_PlayerVelX * timeElapsed;
    //   }
    // }
    if(m_IsJumping)
    {
      // if(m_PlayerVelX > 0.f)
      // {
      //   m_PlayerPosX += m_PlayerVelX * timeElapsed;
      // }
      // else if(m_PlayerVelX < 0.f)
      // {
      //   m_PlayerPosX -= m_PlayerVelX * timeElapsed;
      // }
      //ChangeXVelocity();
      std::cout << static_cast<std::underlying_type<PlayerMovement>::type>(m_StopXDirection)<< std::endl;
      if (m_PreviousMovement == PlayerMovement::Right)
      {
        m_PlayerPosX += (m_PlayerVelX * timeElapsed);
      }
      else if(m_PreviousMovement == PlayerMovement::Left)
      {
        m_PlayerPosX -= m_PlayerVelX * timeElapsed;
      }
      else if(m_PreviousMovement == PlayerMovement::Still)
      {
        m_PlayerPosX = m_PlayerPosX;
      }
      // else
      // {
      //   m_PlayerVelX = m_MaxXVelocity;
      // }
    }
    if(m_PlayerVelX != 0.f && !m_LeftCollision && !m_RightCollision)
    {
      if(m_PreviousMovement == PlayerMovement::Left)
      {
        m_StopXDirection = PlayerMovement::Left; //Ummm.... I don't think this is working?
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

    for(int j = 0; j < m_ActionsBuffer.size(); ++j)
    {
      if(m_ActionsBuffer[j] == PlayerAction::Jump || m_ActionsBuffer[j] == PlayerAction::Land) // || m_ActionsBuffer[itr] == PlayerAction::Run)
      {
        //Check Leftside collisions while jumping and adjust accordingly
        if(m_PlayerPosX > objectStartX && m_PlayerPosX < objectEndX &&
          m_PlayerPosY > objectStartY && m_PlayerPosY < objectEndY)
          {
            //When player is under the platform.
            if(m_PlayerPosY < objectEndY && m_PreviousPosY > objectEndY)
            {
              m_PlayerPosY = objectEndY + 5;
            }
            //When player collides into the platform from the left
            else if(m_PlayerPosX < objectEndX && m_PreviousPosX > objectEndX)
            {
              m_PlayerPosX = objectEndX + 5;
            }
          }
        //Check for Right side collisions while jumping and adjust accordingly
        else if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX &&
          m_PlayerPosY > objectStartX && m_PlayerPosY > objectEndX)
        {
          //When player is under the platform.
          if(m_PlayerPosY < objectEndY && m_PreviousPosY > objectEndY)
          {
            m_PlayerPosY = objectEndY + 5;
          }
          //When player collides into the platform from the left
          else if(m_PlayerPosX > objectStartX && m_PreviousPosX < objectStartX)
          {
            m_PlayerPosX = objectStartX - 5;
          }
        }
      }
    }

    //Account for collsions on player's lower left
    if(m_PlayerPosX > objectStartX && m_PlayerPosX < objectEndX &&
      m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY + m_PlayerHeight < objectEndY)
      {
        //std::cout << "Lower Left Collision" << std::endl;
        m_PlayerPosY = objectStartY - m_PlayerHeight;
      }
    //Account for collsions on player's lower right
    else if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX &&
      m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY + m_PlayerHeight < objectEndY)
      {
        //std::cout << "Lower Right Collision" << std::endl;
        m_PlayerPosY = objectStartY - m_PlayerHeight;
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
            std::cout << "Foot Collision Right" << std::endl;
            m_PlayerPosX = objectStartX - m_PlayerWidth;
            m_MaxXVelocity = m_MinXVelocity;
          }
        //Head Collision
        else if(m_PlayerPosX + m_PlayerWidth + 0.5f > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX
        && m_PlayerPosY > objectStartY && m_PlayerPosY - 0.5f < objectEndY)
        {
          //m_RightCollision = true;
          std::cout << "Head Collision Right" << std::endl;
          if(!m_IsJumping)
          {
            m_PlayerPosX = objectStartX - m_PlayerWidth;
            m_MaxXVelocity = m_MinXVelocity;
            SetPlayerMovement(PlayerMovement::Still);
          }
        }
        //Body Collision (player midpoint, which is needed because the player can be taller than the platform)
        else if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX
        && m_PlayerPosY + (m_PlayerHeight / 2) > objectStartY && m_PlayerPosY + (m_PlayerHeight / 2) < objectEndY)
        {
          std::cout << "Body Collision Right" << std::endl;
          //m_RightCollision = true;
          SetPlayerMovement(PlayerMovement::Still);
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
            std::cout << "Foot Collision Left" << std::endl;
            m_PlayerPosX = objectEndX;
            m_MaxXVelocity = m_MinXVelocity;
          }
        //Head Collision
        else if(m_PlayerPosX - .5f < objectEndX && m_PlayerPosX > objectStartX &&
          m_PlayerPosY - .5f < objectEndY && m_PlayerPosY > objectStartY)
          {
            if(!m_IsJumping)
            {
              m_PlayerPosX = objectEndX + 20.f;
              m_MaxXVelocity = m_MaxXVelocity * -1;
              SetPlayerMovement(PlayerMovement::Still);
            }
            else if(m_IsJumping)
            {
              m_MaxXVelocity = m_MaxXVelocity * -1;
              SetPlayerMovement(PlayerMovement::Still);
            }
            std::cout << "Head Collision Left" << std::endl;
            //m_LeftCollision = true;
          }
        //Body Collision
        else if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
          m_PlayerPosY + (m_PlayerHeight / 2) < objectEndY && m_PlayerPosY + (m_PlayerHeight / 2) > objectStartY)
          {
            std::cout << "Body Collision Left" << std::endl;
            //m_LeftCollision = true;
            m_PlayerPosX = objectEndX + 0.5f;  //Not fully sure why, but collision gets buggy when the .5 value isn't added (not necessary with right body collisions).
            SetPlayerMovement(PlayerMovement::Still);  //Stop run/walk animation when collision happens
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
          m_PlayerPosX = objectEndX + 0.5f;
          m_MaxXVelocity = m_MinXVelocity;
        }
      //Left Body Collision
      else if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
        m_PlayerPosY + (m_PlayerHeight / 2) < objectEndY && m_PlayerPosY + (m_PlayerHeight / 2) > objectStartY)
        {
          m_PlayerPosX = objectEndX + 0.5f; //Not fully sure why, but collision gets buggy when the .5 value isn't added (not necessary with right body collisions).
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
