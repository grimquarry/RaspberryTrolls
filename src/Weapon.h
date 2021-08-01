#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Player.h"

class Weapon {

public:
  Weapon();
  ~Weapon();

  void Update(Player& player);

  void SetTexture(std::string path);

  void Draw(Window& l_window)
  {
    l_window.Draw(m_WeaponSprite);
  }

protected:
  sf::Texture m_WeaponTexture;
  sf::Sprite m_WeaponSprite;

private:
    int m_MaxDistance;
    int m_DistanceTraveled;

    float m_Xpos;
    float m_Ypos;

    bool m_Returning;
};
