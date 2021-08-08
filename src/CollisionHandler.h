/*This class borrows very heavily from the swept AABB collision detection code demonstrated by the OneLoneCoder in this video:
https://youtu.be/8JJ-4JgR7Dg*/
#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <string>
#include "Platform.h"
#include "Player.h"
#include "Window.h"
#include "Fruit.h"
#include "Weapon.h"

class CollisionHandler
{
private:
  //Player player;
  std::string m_DebugMessage;
public:
  //std::vector<Platform> vPlats;
  CollisionHandler();
  ~CollisionHandler();

  // sf::Time timer;
  // sf::Clock clock;

  std::string DebugMessage();

  bool PointVsRect(const sf::Vector2f& p, const Platform& r);

  bool RectVsRect(const Player& r1, Fruit& r2);
  bool RectVsRect(const Weapon& r1, Fruit& r2);

  //Uses Swept AABB algorithm explained really well in this video: https://youtu.be/8JJ-4JgR7Dg
  bool RayVsRect(const sf::Vector2f& ray_origin, const sf::Vector2f& ray_dir,
    const sf::RectangleShape& target, sf::Vector2f& contact_point,
    sf::Vector2f& contact_normal, float& t_hit_near);

  bool DynamicRectVsRect(const Player* r_dynamic, const float fTimeStep, const Platform r_static,
    sf::Vector2f& contact_point, sf::Vector2f& contact_normal, float& contact_time);

  bool ResolveDynamicRectVsRect(Player* r_dynamic, const float fTimeStep, Platform r_static);

  sf::Vector2f NormalizeVector(sf::Vector2f vector);

  bool OnUserUpdate(Window& win, std::vector<Platform>& vPlats, Player& player, Weapon& weapon, std::vector<Fruit>& vFruit, float fElapsedTime);
};
