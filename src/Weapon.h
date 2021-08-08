#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Player.h"

class Weapon {

public:
  Weapon();
  ~Weapon();

  void Update(Player& player);

  void SpinAnimation();

  void SetTexture(std::string path);

  sf::Vector2f GetSize() const;

  sf::Vector2f GetPosition() const;

  void Draw(Window& l_window);

protected:
  sf::Texture m_WeaponTexture;
  sf::Sprite m_WeaponSprite;

private:
    int m_MaxDistance;
    int m_DistanceTraveled;

    int m_XVelocity;
    int m_YVelocity;

    float m_Xpos;
    float m_Ypos;

    bool m_Returning;
    bool m_YReturnAdjust;

    std::string m_Direction;
};
