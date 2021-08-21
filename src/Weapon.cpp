#include "Weapon.h"

Weapon::Weapon()
{
  m_MaxDistance = 15;
  m_DistanceTraveled = 0;
  m_XVelocity = 15;
  m_YVelocity = 20;
  m_Returning = false;
  m_YReturnAdjust = false;
}
Weapon::~Weapon() { }

void Weapon::Update(Player& player)
{
  std::string sFacingDirection = player.GetFacingDirection();
  // std::cout << "Facing direction is: " << sFacingDirection << std::endl;

  if(m_DistanceTraveled == 0 && !m_Returning)
  {
    if(sFacingDirection == "Right")
    {
      m_Xpos = player.GetPosition().x + player.GetSize().x;
      m_Direction = sFacingDirection;
    }
    else if (sFacingDirection == "Left")
    {
      m_Xpos = player.GetPosition().x;
      m_Direction = sFacingDirection;
    }
    m_Ypos = player.GetPosition().y + 43; //43 is the number of pixels from top of sprite down in last frame of animation attack.
    m_DistanceTraveled++;
  }
  else if(!m_Returning && m_DistanceTraveled > 0 && m_DistanceTraveled < m_MaxDistance)
  {
    //m_Xpos += 10;
    if(m_Direction == "Right")
    {
      m_Xpos += m_XVelocity + player.vel.x;
    }
    else if(m_Direction == "Left")
    {
      m_Xpos -= m_XVelocity - player.vel.x;
    }
    // else
    // {
    //   m_DistanceTraveled = 0;
    //   player.SetWeaponEngaged(false);
    // }
    m_DistanceTraveled++;
  }
  if(m_DistanceTraveled >= m_MaxDistance)
  {
    m_Returning = true;
  }
  if(m_Returning)
  {
    if(m_Direction == "Right")
    {
      m_Xpos -= m_XVelocity;
      if(m_Xpos <= player.GetPosition().x + player.GetSize().x)
      {
          if(!m_YReturnAdjust)
          {
            m_DistanceTraveled = 0;
            player.SetWeaponEngaged(false);
            m_Returning = false;
            player.CatchWeapon(true);
            m_Ypos = -100; //This is a not-so-elloquent way of deailing with weapon positions showing up in the spot the cycle ended.  You should fix this.
          }
          else
          {
            m_Xpos = player.GetPosition().x;
          }
      }
    }
    else if(m_Direction == "Left")
    {
      m_Xpos += m_XVelocity;
      if(m_Xpos > player.GetPosition().x)
      {
        if(!m_YReturnAdjust)
        {
          m_DistanceTraveled = 0;
          player.SetWeaponEngaged(false);
          m_Returning = false;
          player.CatchWeapon(true);
          m_Ypos = -100; //This is a not-so-elloquent way of deailing with weapon positions showing up in the spot the cycle ended.  You should fix this.
        }
        else
        {
          m_Xpos = player.GetPosition().x;
        }
      }
    }

    if(m_Ypos < player.GetPosition().y)
    {
      m_Ypos += m_YVelocity;
      m_YReturnAdjust = true;
    }
    else if(m_Ypos > player.GetPosition().y + player.GetSize().y)
    {
      m_Ypos -= m_YVelocity;
      m_YReturnAdjust = true;
    }
    else m_YReturnAdjust = false;
  }

  m_WeaponSprite.setPosition(m_Xpos, m_Ypos);
}

void Weapon::SpinAnimation()
{
  m_WeaponSprite.rotate(90.f);
  m_WeaponSprite.setOrigin(m_WeaponSprite.getGlobalBounds().width / 2, m_WeaponSprite.getGlobalBounds().height / 2);
}

sf::Vector2f Weapon::GetPosition() const
{
  return m_WeaponSprite.getPosition();
}

void Weapon::Draw(Window& l_window)
{
  SpinAnimation();
  l_window.Draw(m_WeaponSprite);
}

sf::Vector2f Weapon::GetSize() const
{
  return { m_WeaponSprite.getGlobalBounds().width, m_WeaponSprite.getGlobalBounds().height };
}

void Weapon::SetTexture(std::string path)
{
  if(!m_WeaponTexture.loadFromFile(path))
  {
    std::cout << "Failed to load file" << std::endl;
  }
  else
  {
    m_WeaponSprite.setTexture(m_WeaponTexture);
  }
}
