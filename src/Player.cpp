#include "Player.h"

  Player::Player()
  {
    m_Score = 0;
    m_WalkAnimItr = 0;
    m_MaxWalkVelocity = 6.0f;
    m_MinWalkVelocity = -6.0f;
    m_MaxRunVelocity = 10.0f;
    m_MinRunVelocity = -10.0f;
    m_VelocityIncrement = 0.5f;
    m_Right = false;
    m_Left = false;
    m_Stop = true;
    m_Walk = false;
    m_Run = false;
    m_Jump = false;
    m_Land = false;
    m_SideCollision = false;
  }

  Player::~Player() { }

  void Player::SetPlayerName(std::string name) { m_Name = name; }
  std::string Player::GetPlayerName() const { return m_Name; }

  void Player::ScoreIncrement(int increment) { m_Score += increment; }
  int Player::GetScore() const { return m_Score; }

  void Player::SetMoveDirectives(std::vector<PlayerMovement> vMovements)
  {
    m_MovementBuffer.clear();
    m_MovementBuffer = vMovements;
  }
  void Player::SetActionDirectives(std::vector<PlayerAction> vActions)
  {
    m_ActionsBuffer.clear();
    m_ActionsBuffer = vActions;
  }

  void Player::Move()
  {
    /*Uncomment Below to test what's in the MovemeBuffer at the point this method is called for troubleshooting*/
    // std::cout << "_____________________________________________________________________" << std::endl;
    // for(int i = 0; i < m_MovementBuffer.size(); ++i)
    // {
    //   std::cout << "Movement code is: " << static_cast<std::underlying_type<PlayerMovement>::type>(m_MovementBuffer[i]) << std::endl;
    // }
    // std::cout << "_____________________________________________________________________" << std::endl;

    /*Uncomment Below to test what's in the Actions Buffer at the point this method is called for troubleshooting*/
    // for(int i = 0; i < m_ActionsBuffer.size(); ++i)
    // {
    //   std::cout << "Action code is: " << static_cast<std::underlying_type<PlayerAction>::type>(m_ActionsBuffer[i]) << std::endl;
    // }
    // std::cout << "_____________________________________________________________________" << std::endl;
    //
    // std::cout << "Actions Buffer Size in Player: " << m_ActionsBuffer.size() << std::endl;

    //Gravity
    vel.y += 1.0f;



    for(int i = 0; i < m_MovementBuffer.size(); ++i)
    {
      if(m_MovementBuffer[i] == PlayerMovement::Right)
      {
        m_Right = true;
        m_Left = false;
        m_Stop = false;
      }
      else if(m_MovementBuffer[i] == PlayerMovement::Left)
      {
        m_Left = true;
        m_Right = false;
        m_Stop = false;
      }
      else
      {
        m_Stop = true;
        m_Right = false;
        m_Left = false;
      }
      if(m_MovementBuffer[i] == PlayerMovement::Up)
      {
        vel.y -= .1f;
        if(vel.y < -5.0f) { vel.y = -5.0f; }
      }
      else if(m_MovementBuffer[i] == PlayerMovement::Down)
      {
        vel.y += .1f;
        if(vel.y > 5) { vel.y = 5.0f; }
      }
      else
      {
        StopY();
      }
      if(m_MovementBuffer[i] == PlayerMovement::StillX)
      {
        m_Stop = true;
        m_Right = false;
        m_Left = false;
      }
      if(m_MovementBuffer[i] == PlayerMovement::StillY)
      {
        StopY();
      }
    }

    if(!m_ActionsBuffer.empty())
    {
      for(int i = 0; i < m_ActionsBuffer.size(); ++i)
      {
        if(m_ActionsBuffer[i] == PlayerAction::Jump && m_OnGround)
        {
          std::cout << "Jump is registered in Player Class" << std::endl;
          m_Jump = true;
        }
        else if(m_ActionsBuffer[i] == PlayerAction::Land /*&& !m_OnGround*/)
        {
          m_Land = true;
          m_Jump = false;
          std::cout << "THIS RAN!" << std::endl;
          vel.y += 10.0f;
        }

        if(m_ActionsBuffer[i] == PlayerAction::Run)
        {
          m_Run = true;
          m_Walk = false;
        }
        else if(m_ActionsBuffer[i] == PlayerAction::Walk)
        {
          m_Walk = true;
          m_Run = false;
        }
        else if (m_ActionsBuffer[i] == PlayerAction::Stop)
        {
          m_Walk = false;
          m_Run = false;
        }

      }
    }

    if(m_Right && m_Walk)
    {
      vel.x += m_VelocityIncrement;
      if(vel.x > m_MaxWalkVelocity) { vel.x = m_MaxWalkVelocity; }
    }
    else if(m_Left && m_Walk)
    {
      vel.x -= m_VelocityIncrement;
      if(vel.x < m_MinWalkVelocity) {vel.x = m_MinWalkVelocity; }
    }
    else if(m_Stop)
    {
      StopX();
    }

    if(m_Jump)
    {
      vel.y = -37.0f;
    }
    else if(m_Land)
    {
      vel.y += 0.9f;
    }

    if(m_Run)
    {
      if(m_Right)
      {
        vel.x += m_VelocityIncrement;
        if(vel.x > m_MaxRunVelocity) { vel.x = m_MaxRunVelocity; }
      }
      else if(m_Left)
      {
        vel.x -= m_VelocityIncrement;
        if(vel.x < m_MinRunVelocity) { vel.x = m_MinRunVelocity; }
      }

    }
  }

  void Player::StopX()
  {
    if(vel.x < 1.0f && vel.x > -1.0f) {vel.x = 0.0f; } //Check condition for setting velocity to 0 first
    else if(vel.x > 0.0f) { vel.x -= .5f; }
    else if(vel.x < 0.0f) {vel.x += .5f; }
  }

  void Player::StopY()
  {
    if(vel.y > 0.0f) { vel.y -= .1f; }
    else if(vel.y < 0.0f) {vel.y += .1f; }
    else if(vel.y < 0.9f && vel.y > -0.9f) { vel.y = 0.0f; }
  }

  void Player::SetOnGround(bool b) { m_OnGround = b; }

  bool Player::GetOnGround() { return m_OnGround; }

  void Player::SetSideCollision(bool b) { m_SideCollision = b; }

  sf::Vector2f Player::GetSize() const
  {
    return { m_PlayerSprite.getGlobalBounds().width, m_PlayerSprite.getGlobalBounds().height };
  }

  sf::Vector2f Player::GetPosition() const
  {
    return m_Position;
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

    if(m_FrameCount > 2 && m_FrameCount % 3 == 0 && m_Run)
    {
      m_WalkAnimItr++;
    }
    else if(m_FrameCount > 4 && m_FrameCount % 5 == 0 && !m_Run)
    {
      m_WalkAnimItr++;
    }
  }

  void Player::HandleAnimTexture()
  {
    /*Uncomment below to get movement and action states for debugging at this point*/
    // std::cout << "m_Stop: " << m_Stop << std::endl;
    // std::cout << "m_Jump: " << m_Jump << std::endl;
    // std::cout << "m_Land: " << m_Land << std::endl;
    // std::cout << "m_Right: " << m_Right << std::endl;
    // std::cout << "m_Left: " << m_Left << std::endl;
    // std::cout << "m_Walk: " << m_Walk << std::endl;
    // std::cout << "m_Run: " << m_Run << std::endl;
    // std::cout << "m_OnGround: " << m_OnGround << std::endl;

    if(m_Land && m_OnGround)
    {
      m_Land = false;
    }

    if(m_Right)
    {

      m_PlayerSprite.setScale({1, 1});
      m_PlayerSprite.setOrigin(0.f, 0.f);

    }
    else if(m_Left)
    {

      m_PlayerSprite.setScale({-1, 1});
      m_PlayerSprite.setOrigin((float)m_PlayerSprite.getGlobalBounds().width, 0.0f); //Change origin for smoother animation when changing direction from right to left.
    }

    if(m_Jump || m_Land) { m_PlayerSprite.setTexture(m_TxtrAnimBuff[14]); }
    else if(m_Stop && !m_Jump || m_Stop && !m_Land) { m_PlayerSprite.setTexture(m_TxtrAnimBuff[0]); }
    else if(m_Walk && !m_Jump || m_Run && !m_Jump)
    {
      if(!m_Jump || m_Land)
      {
        if(!m_SideCollision)
        {
          WalkAnimation();
        }
        else if (m_SideCollision)
        {
          m_PlayerSprite.setTexture(m_TxtrAnimBuff[0]);
        }
      }
    }

    //Because this code is set to register button pushes only once, we need to set the original jump directive to false
    //after it's pushed.  Otherwise there's no other logic to stop the player from decreasing movement in the y axis
    //and the player will just keep rising into the air... like he just don't care.
    if(m_Jump) { m_Jump = false; m_Land = true; }
  }

  void Player::SetPosition(float x, float y)
  {
    m_Position.x = x;
    m_Position.y = y;
    m_PlayerSprite.setPosition(m_Position.x, m_Position.y);
  }

  void Player::SetPosition(sf::Vector2f pos)
  {
    m_Position = pos;
    m_PlayerSprite.setPosition(m_Position);
  }


  void Player::Draw(Window& l_window)
  {
    //m_PlayerSprite.setTexture(m_TxtrAnimBuff[0]);
    HandleAnimTexture();
    l_window.Draw(m_PlayerSprite);
  }
