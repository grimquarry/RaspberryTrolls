#include "Weapon.h"

Weapon::Weapon()
{
  m_MaxDistance = 25;
  m_DistanceTraveled = 0;
  m_Returning = false;
}
Weapon::~Weapon() { }

void Weapon::Update(Player& player)
{
  if(m_DistanceTraveled == 0 && !m_Returning)
  {
    // if(player.m_Right)
    // {
      m_Xpos = player.GetPosition().x + player.GetSize().x;
    // }
    // else if (player.m_Left)
    // {
      //m_Xpos = player.GetPosition().x;
    // }
    m_Ypos = player.GetPosition().y + 43; //43 is the number of pixels from top of sprite down in last frame of animation attack.
    m_DistanceTraveled++;
  }
  else if(!m_Returning && m_DistanceTraveled > 0 && m_DistanceTraveled < m_MaxDistance)
  {
    m_Xpos += 10;
    // if(player.m_Right)
    // {
      // m_Xpos += 10;
    // }
    // else if(player.m_Left)
    // {
    //   m_Xpos--;
    // }
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
    m_Xpos -= 10;
    if(m_Xpos < player.GetPosition().x)
    {
      m_DistanceTraveled = 0;
      player.SetWeaponEngaged(false);
      m_Returning = false;
      m_Ypos = -100; //This is a not-so-elloquent way of deailing with weapon positions showing up in the spot the cycle ended.  You should fix this.
    }
  }

  m_WeaponSprite.setPosition(m_Xpos, m_Ypos);
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
