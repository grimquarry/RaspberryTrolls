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
  m_LowerLeftCollision = false;
  m_RightCollision = false;
  m_IsRunning = false;
  m_IsWalking = false;
  m_IsJumping = false;
  m_IsLanding = false;
  m_IgnoreJump = false;

  m_MinXVelocity = 7;
  m_MaxXVelocity = m_MinXVelocity;
  m_MaxRunSpeed = 11;
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
  std::cout << static_cast<std::underlying_type<PlayerMovement>::type>(m_CurrentMovement) << std::endl;
  if(m_CurrentMovement == PlayerMovement::Still & !m_IsJumping)
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
        m_PlayerVelY = -16;
        m_IgnoreJump = true;
      }
      else if(m_IsWalking && m_OnGround)
      {
        m_PlayerVelY = -11;
        m_IgnoreJump = true;
      }
    }
    if(m_IsLanding)
    {
      m_PlayerVelY += 0.5;
      m_IgnoreJump = true;
    }

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
    m_MaxXVelocity = m_MaxRunSpeed;
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
    if(!m_RightCollision)
    {
      ChangeXVelocity();
      m_PlayerPosX += (m_PlayerVelX * timeElapsed);
    }
  }
  else if(m_CurrentMovement == PlayerMovement::Left)
  {
    m_StopXDirection = PlayerMovement::Left;
    if(m_PreviousMovement != PlayerMovement::Left)
    {
      m_PlayerSprite.setScale({-1, 1});
      m_PlayerSprite.setOrigin((float)m_PlayerWidth, 0.0f); //Change origin for smoother animation when changing direction from right to left.
    }
    if(!m_LeftCollision)
    {
      ChangeXVelocity();
      m_PlayerPosX -= (m_PlayerVelX * timeElapsed);
    }
  }
  //Lines below commented out because they shouldn't do anything at this point (revist when duck and climb directives are created)
  // else if(m_CurrentMovement == PlayerMovement::Up)
  // {
  //   m_PlayerPosY -= (m_PlayerVelY * timeElapsed);
  // }
  // else if(m_CurrentMovement == PlayerMovement::Down)
  // {
  //   if(m_IsRunning)
  //   {
  //     m_PlayerVelY += 0.90f;
  //   }
  //   else
  //   {
  //     m_PlayerVelY += 0.50f;
  //   }
  //   m_PlayerPosY += (m_PlayerVelY * timeElapsed);
  // }
  else if (m_CurrentMovement == PlayerMovement::Still)
  {
    if(m_IsJumping)
    {
      if (m_PreviousMovement == PlayerMovement::Right)
      {
        if(!m_RightCollision)
        {
          m_PlayerPosX += (m_PlayerVelX * timeElapsed);
        }
      }
      else if(m_PreviousMovement == PlayerMovement::Left)
      {
        if(!m_LeftCollision)
        {
          m_PlayerPosX -= m_PlayerVelX * timeElapsed;
        }
      }
      else if(m_PreviousMovement == PlayerMovement::Still)
      {
        m_PlayerPosX = m_PlayerPosX;
      }
    }

    if(m_PlayerVelX != 0.f && !m_LeftCollision && !m_RightCollision)
    {
      if(m_PreviousMovement == PlayerMovement::Left)
      {
        m_StopXDirection = PlayerMovement::Left; //Ummm.... I don't think this is working?  I don't remember this but it seems fine now
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
  //Gravity
  if(!m_OnGround)
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
  //Put player in the new postion
  SetPosition(m_PlayerPosX, m_PlayerPosY);
}

void Player::CollisionCheck(std::vector<sf::Vector2i> collidableObjects)
{
  m_OnGround = false;
  m_LeftCollision = false;
  m_RightCollision = false;
  m_LowerLeftCollision = false;
  //int testing = -1;
  int objectWidth;
  int objectHeight;
  int objectStartX;
  int objectEndX;
  int objectStartY;
  int objectEndY;
  for(int i = 0; i < collidableObjects.size(); i++)
  {
    objectWidth = 200; //This variable and objectHeight are specific to nectarine branch platform sprites
    objectHeight = 75;  //I will likely need to rework things to fit other platform sizes (25x25 for example)
    objectStartX = collidableObjects[i].x;
    objectEndX = collidableObjects[i].x + objectWidth;
    objectStartY = collidableObjects[i].y;
    objectEndY = collidableObjects[i].y + objectHeight;
    //bool testTrigger = false;
    //std::cout << "*************************************************************" << std::endl;
    switch(m_CurrentMovement){
      case PlayerMovement::Right:
      //Check Right side collisions while jumping and adjust accordingly
      if(m_IsJumping || m_IsLanding)
      {
        if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX &&
        m_PlayerPosY > objectStartY && m_PlayerPosY < objectEndY)
        {
          //When player is under the platform.
          if(m_PlayerPosY < objectEndY && m_PreviousPosY > objectEndY)
          {
            std::cout << "Jump Head Collision Right Registered" << std::endl;
            m_PlayerPosY = objectEndY + .5; //+.5 is needed to offset float when comapring to an int
          }
          //When player collides into the platform from the right
          else if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PreviousPosX < objectStartX)
          {
            std::cout << "Right facing jump collistion registered" << std::endl;
            if(m_PlayerPosY > objectStartY && m_PlayerPosY < objectEndY ||
              m_PlayerPosY + (m_PlayerWidth / 2) > objectStartY && m_PlayerPosY + (m_PlayerWidth / 2) < objectEndY ||
              m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY + m_PlayerHeight < objectEndY)
              {
                //m_PlayerVelX = 0;
                m_PlayerPosX = objectStartX;
                m_RightCollision = true;
                SetPlayerMovement(PlayerMovement::Still);
              }
          }
        }
      }
      //Account for collsions on player's lower right when landing from a jump
      if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX &&
        m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY + m_PlayerHeight < objectEndY)
        {
          std::cout << "Lower right landing collision registered" << std::endl;
            // std::cout << "m_IgnoreJump is " << m_IgnoreJump << std::endl;
            // std::cout << "m_IsJumping is " << m_IsJumping << std::endl;
            // std::cout << "m_IsLanding is " << m_IsLanding << std::endl;
            // std::cout << "m_IsWalking is " << m_IsWalking << std::endl;
            // std::cout << "m_IsRunning is " << m_IsRunning << std::endl;
            // std::cout << "m_OnGround is " << m_OnGround << std::endl;
          //m_PlayerVelX = 0;
          //m_RightCollision = true;
          //m_OnGround = true;
          //This condition is intended to stop moving the player on the Y axisis when colliding into the Platform
          //from the right rather than from the top.  Players will still be brought up to the platfrom Y coordinate
          //when their feet Y coordinate is between the start of the platform and 30 pixels from the start of the
          //platform.  This isn't ideal, but anything lower than 30 causes problems when landing on the top of the
          //platform rather than colliding into it from the side.
          if(m_PreviousPosY < m_PlayerPosY && m_PlayerPosY + m_PlayerHeight < objectStartY + 30)
          {
            std::cout << "This ran" << std::endl;
            m_PlayerPosY = objectStartY - m_PlayerHeight;
          }
          //m_PlayerPosY = objectStartY - m_PlayerHeight;
        }

      //Foot Collision
      if(m_PlayerPosX + m_PlayerWidth < objectEndX && m_PlayerPosX + m_PlayerWidth > objectStartX &&
        m_PlayerPosY + m_PlayerHeight < objectEndY && m_PlayerPosY + m_PlayerHeight > objectStartY)
        {
          std::cout << "Right Foot collision registered" << std::endl;
          m_PlayerVelX = 0;
          m_RightCollision = true;
          m_PlayerPosX = objectStartX - m_PlayerWidth;
          SetPlayerMovement(PlayerMovement::Still);
        }
      //Head Collision
      else if(m_PlayerPosX + m_PlayerWidth < objectEndX && m_PlayerPosX + m_PlayerWidth > objectStartX &&
        m_PlayerPosY < objectEndY && m_PlayerPosY > objectStartY)
        {
          std::cout << "Right side head collision detected" << std::endl;
          std::cout << "Player X Position: " << m_PlayerPosX + m_PlayerWidth << std::endl;
          std::cout << "Platform x Start Postion: " << objectStartX << std::endl;
          std::cout << "Platform x End Postion: " << objectEndX << std::endl;
          std::cout << "Player Y Position: " << m_PlayerPosY + m_PlayerHeight << std::endl;
          std::cout << "Platform Start Y Position: " << objectStartY << std::endl;
          std::cout << "Platform End Y Position: " << objectEndY << std::endl;
          m_PlayerVelX = 0;
          m_PlayerPosX = objectStartX - m_PlayerWidth;
          m_RightCollision = true;
          SetPlayerMovement(PlayerMovement::Still);
        }
      //Body Collision
      else if(m_PlayerPosX + m_PlayerWidth < objectEndX && m_PlayerPosX + m_PlayerWidth > objectStartX &&
        m_PlayerPosY + (m_PlayerHeight / 2) < objectEndY && m_PlayerPosY + (m_PlayerHeight / 2) > objectStartY)
        {
          std::cout << "Right side Body Collision detected" << std::endl;
              std::cout << "Player X Position: " << m_PlayerPosX + m_PlayerWidth << std::endl;
              std::cout << "Platform x Start Postion: " << objectStartX << std::endl;
              std::cout << "Platform x End Postion: " << objectEndX << std::endl;
              std::cout << "Player Y Position: " << m_PlayerPosY + m_PlayerHeight << std::endl;
              std::cout << "Platform Start Y Position: " << objectStartY << std::endl;
              std::cout << "Platform End Y Position: " << objectEndY << std::endl;
          //m_PlayerVelX = 0;
          m_RightCollision = true;
          m_PlayerPosX = objectStartX - m_PlayerWidth;
          SetPlayerMovement(PlayerMovement::Still);
          //m_CurrentMovement = PlayerMovement::Still;
        }

      case PlayerMovement::Left:
      //Check Leftside collisions while jumping and adjust accordingly
        if(m_IsJumping || m_IsLanding)
        {
          if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX < objectEndX &&
          m_PlayerPosY > objectStartY && m_PlayerPosY < objectEndY)
          {
            //When player is under the platform.
            if(m_PlayerPosY < objectEndY && m_PreviousPosY > objectEndY)
            {
              std::cout << "Jump Head Collision Left Registered" << std::endl;
              std::cout << "Player X Position: " << m_PlayerPosX + m_PlayerWidth << std::endl;
              std::cout << "Platform x Start Postion: " << objectStartX << std::endl;
              std::cout << "Platform x End Postion: " << objectEndX << std::endl;
              std::cout << "Player Y Position: " << m_PlayerPosY << std::endl;
              std::cout << "Platform Start Y Position: " << objectStartY << std::endl;
              std::cout << "Platform End Y Position: " << objectEndY << std::endl;
              m_PlayerPosY = objectEndY + .5f;
            }
            //When player collides into the platform from the left
            else if(m_PlayerPosY > objectStartY && m_PlayerPosY < objectEndY ||
              m_PlayerPosY + (m_PlayerWidth / 2) > objectStartY && m_PlayerPosY + (m_PlayerWidth / 2) < objectEndY ||
              m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY + m_PlayerHeight < objectEndY)
            {
              std::cout << "Left facing jump collistion registered" << std::endl;
              //m_PlayerVelX = 0;
              m_PlayerPosX = objectEndX;
              m_LeftCollision = true;
              SetPlayerMovement(PlayerMovement::Still);
            }
          }
        }
        //Account for collsions on player's lower left when landing from a jump
        if(m_PlayerPosX > objectStartX && m_PlayerPosX < objectEndX &&
          m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY + m_PlayerHeight < objectEndY)
          {
            std::cout << "Lower left landing collision registered" << std::endl;
            //m_PlayerVelX = 0;
            //m_LeftCollision = true;
            //This condition is intended to stop moving the player on the Y axisis when colliding into the Platform
            //from the right rather than from the top.  Players will still be brought up to the platfrom Y coordinate
            //when their feet Y coordinate is between the start of the platform and 30 pixels from the start of the
            //platform.  This isn't ideal, but anything lower than 30 causes problems when landing on the top of the
            //platform rather than colliding into it from the side.
            if(m_PreviousPosY < m_PlayerPosY && m_PlayerPosY + m_PlayerHeight < objectStartY + 30)
            {
              m_PlayerPosY = objectStartY - m_PlayerHeight;
            }
          }

        //Foot Collision
        if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
          m_PlayerPosY + m_PlayerHeight < objectEndY && m_PlayerPosY + m_PlayerHeight > objectStartY)
          {
            std::cout << "Left Foot collision registered" << std::endl;
            std::cout << "Player X Position: " << m_PlayerPosX << std::endl;
            std::cout << "Platform x Start Postion: " << objectStartX << std::endl;
            std::cout << "Platform x End Postion: " << objectEndX << std::endl;
            std::cout << "Player Y Position: " << m_PlayerPosY + m_PlayerHeight << std::endl;
            std::cout << "Platform Start Y Position: " << objectStartY << std::endl;
            std::cout << "Platform End Y Position: " << objectEndY << std::endl;
            m_PlayerVelX = 0;
            m_LeftCollision = true;
            m_PlayerPosX = objectEndX;
          }
        //Head Collision
        else if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
          m_PlayerPosY < objectEndY && m_PlayerPosY > objectStartY)
          {
            std::cout << "Left side head collision detected" << std::endl;
            m_PlayerVelX = 0;
            m_PlayerPosX = objectEndX + .5f;
            m_LeftCollision = true;
            SetPlayerMovement(PlayerMovement::Still);
            //m_CurrentMovement = PlayerMovement::Still;
          }
        //Body Collision
        else if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
          m_PlayerPosY + (m_PlayerHeight / 2) < objectEndY && m_PlayerPosY + (m_PlayerHeight / 2) > objectStartY)
          {
            std::cout << "Left side Body Collision detected" << std::endl;
            std::cout << "Player X Position: " << m_PlayerPosX << std::endl;
            std::cout << "Platform x Start Postion: " << objectStartX << std::endl;
            std::cout << "Platform x End Postion: " << objectEndX << std::endl;
            std::cout << "Player Y Midpiont Position: " << m_PlayerPosY + (m_PlayerHeight / 2) << std::endl;
            std::cout << "Platform Start Y Position: " << objectStartY << std::endl;
            std::cout << "Platform End Y Position: " << objectEndY << std::endl;
            m_PlayerVelX = 0;
            m_LeftCollision = true;
            m_PlayerPosX = objectEndX;
            SetPlayerMovement(PlayerMovement::Still);
            //m_CurrentMovement = PlayerMovement::Still;
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
      //Check Leftside collisions while jumping and adjust accordingly
        if(m_IsJumping || m_IsLanding)
        {
          if(m_PlayerPosX > objectStartX && m_PlayerPosX < objectEndX &&
          m_PlayerPosY > objectStartY && m_PlayerPosY < objectEndY)
          {
            //When player is under the platform.
            if(m_PlayerPosY < objectEndY && m_PreviousPosY > objectEndY)
            {
              std::cout << "Still left facing jump head collision" << std::endl;
              m_PlayerPosY = objectEndY + .5;
            }
            //When player collides into the platform from the left
            else if(m_PlayerPosX < objectEndX && m_PreviousPosX > objectEndX)
            {
              std::cout << "Still jump colliding from left" << std::endl;
              m_PlayerPosX = objectEndX;
              m_LeftCollision = true;
            }
          }
        }
        //Account for collsions on player's lower left when landing from a jump
        if(m_PlayerPosX > objectStartX && m_PlayerPosX < objectEndX &&
          m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY + m_PlayerHeight < objectEndY)
          {
            std::cout << "Still jump landing facing left" << std::endl;
            m_LeftCollision = true;
            m_PlayerPosY = objectStartY - m_PlayerHeight;
          }
      //Left Foot Collision
      if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
        m_PlayerPosY + m_PlayerHeight < objectEndY && m_PlayerPosY + m_PlayerHeight > objectStartY)
        {
          std::cout << "Still left facing foot collision" << std::endl;
          m_PlayerPosX = objectEndX;
          m_MaxXVelocity = m_MinXVelocity;
        }
      //Left Head Collision
      else if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
        m_PlayerPosY < objectEndY && m_PlayerPosY > objectStartY)
        {
          std::cout << "Still left facing head collision" << std::endl;
          m_PlayerPosX = objectEndX;
          m_MaxXVelocity = m_MinXVelocity;
        }
      //Left Body Collision
      else if(m_PlayerPosX < objectEndX && m_PlayerPosX > objectStartX &&
        m_PlayerPosY + (m_PlayerHeight / 2) < objectEndY && m_PlayerPosY + (m_PlayerHeight / 2) > objectStartY)
        {
          std::cout << "Still left facing body collision" << std::endl;
          std::cout << "Player X Position: " << m_PlayerPosX << std::endl;
          std::cout << "Platform x Start Postion: " << objectStartX << std::endl;
          std::cout << "Platform x End Postion: " << objectEndX << std::endl;
          std::cout << "Player Y Position: " << m_PlayerPosY + m_PlayerHeight << std::endl;
          std::cout << "Platform Start Y Position: " << objectStartY << std::endl;
          std::cout << "Platform End Y Position: " << objectEndY << std::endl;
          m_PlayerPosX = objectEndX;
          m_MaxXVelocity = m_MinXVelocity;
        }

        //Check for Right side collisions while jumping and adjust accordingly
        if(m_IsJumping || m_IsLanding)
        {
          if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX &&
            m_PlayerPosY > objectStartY && m_PlayerPosY < objectEndY)
          {
             //When player is under the platform.
            if(m_PlayerPosY < objectEndY && m_PreviousPosY > objectEndY)
            {
              m_PlayerPosY = objectEndY + 5;
            }
            //When player collides into the platform from the right
            else if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PreviousPosX + m_PlayerWidth < objectStartX)
            {
              m_PlayerPosX = objectStartX - 5;
            }
          }
          //Account for collsions on player's lower right when landing from a jump
          if(m_PlayerPosX + m_PlayerWidth > objectStartX && m_PlayerPosX + m_PlayerWidth < objectEndX &&
            m_PlayerPosY + m_PlayerHeight > objectStartY && m_PlayerPosY + m_PlayerHeight < objectEndY)
            {
              m_PlayerPosY = objectStartY - m_PlayerHeight;
            }
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

    //std::cout << "************************************************************************" << std::endl;

    //Determine if player is on ground or not.  m_OnGround is used/returned by the bool OnGround method
    if(objectStartY == m_PlayerPosY + m_PlayerHeight && m_PlayerPosX > objectStartX && m_PlayerPosX < objectEndX)
    {
      //std::cout << "This condition met" << std::endl;
      m_OnGround = true;
    }
    else if(objectStartY == m_PlayerPosY + m_PlayerHeight && m_PlayerPosX + m_PlayerWidth < objectEndX && m_PlayerPosX + m_PlayerWidth > objectStartX)
    {
      //std::cout << "Running" << std::endl;
      m_OnGround = true;
    }
    //Determine if player is flush with a platfrom to his Left or Right.
    // if(m_PlayerPosX == objectEndX && m_PlayerPosY < objectEndY && m_PlayerPosY > objectStartY)
    // {
    //   m_LeftCollision = true;
    // }
    // else if(m_PlayerPosX + m_PlayerWidth == objectStartX)
    // {
    //   m_RightCollision = true;
    // }
  }
  SetPosition(m_PlayerPosX, m_PlayerPosY);
}

bool Player::SideCollision()
{
  if(m_RightCollision || m_LeftCollision)
  {
    return true;
  }
  else
  {
    return false;
  }
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
