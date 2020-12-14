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

void Player::Draw(Window& l_window)
{
  int index = (int)GetPlayerMovement();
  m_PlayerSprite.setTexture(m_TxtrAnimBuff[0]);
  l_window.Draw(m_PlayerSprite);
}
