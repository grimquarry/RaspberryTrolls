/*This class borrows very heavily from the swept AABB collision detection code demonstrated by the OneLoneCoder in this video:
https://youtu.be/8JJ-4JgR7Dg*/
#include "CollisionHandler.h"

CollisionHandler::CollisionHandler() { }

CollisionHandler::~CollisionHandler() { }

std::string CollisionHandler::DebugMessage()
{
  return m_DebugMessage;
}

bool CollisionHandler::PointVsRect(const sf::Vector2f& p, const Platform& r)
{
  return (p.x >= r.GetPosition().x && p.y >= r.GetPosition().y &&
    p.x < r.GetPosition().x + r.GetSize().x && p.y < r.GetPosition().y + r.GetSize().y);
}

bool CollisionHandler::RectVsRect(const Player& r1, Fruit& r2)
{
  return (r1.GetPosition().x < r2.GetPosition().x + r2.GetSize().x &&
    r1.GetPosition().x + r1.GetSize().x > r2.GetPosition().x &&
    r1.GetPosition().y < r2.GetPosition().y + r2.GetSize().y &&
    r1.GetPosition().y + r1.GetSize().y > r2.GetPosition().y);
}

//Uses Swept AABB algorithm explained really well in this video: https://youtu.be/8JJ-4JgR7Dg
bool CollisionHandler::RayVsRect(const sf::Vector2f& ray_origin, const sf::Vector2f& ray_dir,
  const sf::RectangleShape& target, sf::Vector2f& contact_point,
  sf::Vector2f& contact_normal, float& t_hit_near)
{
  contact_normal = { 0,0 };
  contact_point = { 0,0 };

  sf::Vector2f invdir;
  invdir.x = 1.0f / ray_dir.x;
  invdir.y = 1.0f / ray_dir.y;
  //Store x, y point values for near and far collision points
  sf::Vector2f t_near;
  sf::Vector2f t_far;

  //Set x, y values for near and far collision points
  t_near.x = (target.getPosition().x - ray_origin.x) * invdir.x;
  t_near.y = (target.getPosition().y - ray_origin.y) * invdir.y;
  t_far.x = (target.getPosition().x + target.getSize().x - ray_origin.x) * invdir.x;
  t_far.y = (target.getPosition().y + target.getSize().y - ray_origin.y) * invdir.y;

  //Can't divide by zero, so we need to account for that
  if(std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
  if(std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

  //Near values should always less than far values, if they're not we need to swap them
  if(t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
  if(t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

  //Collisions only occur when the near x value is less than the far y
  //and when near y is less than far x, if not we can return false because no
  //collision occured
  if(t_near.x > t_far.y || t_near.y > t_far.x) return false;

  //Find at what point the ray hits the rectangle
  // float t_hit_near = std::max(t_near.x, t_near.y); //commented out because it's now a parameter
  t_hit_near = std::max(t_near.x, t_near.y);
  float t_hit_far = std::min(t_far.x, t_far.y);

  //Hits that occure behind the ray direction aren't useful, so we can return false
  //when that happens
  if(t_hit_far < 0) return false;

  contact_point.x = ray_origin.x + t_hit_near * ray_dir.x;
  contact_point.y = ray_origin.y + t_hit_near * ray_dir.y;

  if(t_near.x > t_near.y)
  {
    if(invdir.x < 0)
    {
      contact_normal.x = 1;
      contact_normal.y = 0;
    }
    else
    {
      contact_normal.x = -1;
      contact_normal.y = 0;
    }
  }
  else if(t_near.x < t_near.y)
  {
    if(invdir.y < 0)
    {
      contact_normal.x = 0;
      contact_normal.y = 1;
    }
    else
    {
      contact_normal.x = 0;
      contact_normal.y = -1;
    }
  }

  return true;
}

bool CollisionHandler::DynamicRectVsRect(const Player* r_dynamic, const float fTimeStep, const Platform r_static,
  sf::Vector2f& contact_point, sf::Vector2f& contact_normal, float& contact_time)
{

  if(r_dynamic->vel.x == 0 && r_dynamic->vel.y == 0)
  {
    return false;
  }

  sf::RectangleShape expanded_target;
  expanded_target.setPosition(r_static.GetPosition() - r_dynamic->GetSize() / 2.0f);
  expanded_target.setSize(r_static.GetSize() + r_dynamic->GetSize());

  if(RayVsRect(r_dynamic->GetPosition() + r_dynamic->GetSize() / 2.0f, r_dynamic->vel * fTimeStep,
    expanded_target, contact_point, contact_normal, contact_time))
  {
    return (contact_time >= 0.0f && contact_time < 1.0f);
  }
  else
  {
    return false;
  }
}

bool CollisionHandler::ResolveDynamicRectVsRect(Player* r_dynamic, const float fTimeStep, Platform r_static)
{
	sf::Vector2f contact_point, contact_normal;
	float contact_time = 0.0f;
	if (DynamicRectVsRect(r_dynamic, fTimeStep, r_static, contact_point, contact_normal, contact_time))
	{
		r_dynamic->vel.x += contact_normal.x * std::abs(r_dynamic->vel.x) * (1 - contact_time);
    r_dynamic->vel.y += contact_normal.y * std::abs(r_dynamic->vel.y) * (1 - contact_time);
		return true;
	}

	return false;
}

sf::Vector2f CollisionHandler::NormalizeVector(sf::Vector2f vector)
{
  float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);
  sf::Vector2f unitVector;
  unitVector.x = vector.x / magnitude;
  unitVector.y = vector.y / magnitude;

  return unitVector;
}

bool CollisionHandler::OnUserUpdate(Window& win, std::vector<Platform>& vPlats, Player& player, std::vector<Fruit>& vFruit, float fElapsedTime)
{
  player.SetMoveDirectives(win.GetPlayerDirectives());
  player.SetActionDirectives(win.GetPlayerActions());
  player.Move();

  //std::cout << "Visible Fruit vector size is: " << vFruit.size() << std::endl;
  for(int i = 0; i < vFruit.size(); ++i)
  {
    // std::cout << "Player position: " << player.GetPosition().x << ", " << player.GetPosition().y << std::endl;
    // std::cout << "Fruit Position is: " << vFruit[i].GetPosition().x << ", " << vFruit[i].GetPosition().y << std::endl;
    if(RectVsRect(player, vFruit[i]))
    {
      vFruit[i].SetCollectable(false);
      std::cout << "We got a hit" << std::endl;
    }

  }

  sf::Vector2f cp, cn;
  float t = 0, min_t = INFINITY;
  std::vector<std::pair<int, float>> z;

  for(size_t i = 0; i < vPlats.size(); i++)
  {
    if(DynamicRectVsRect(&player, fElapsedTime, vPlats[i], cp, cn, t))
    {
      z.push_back({ i, t });
    }
  }

  std::sort(z.begin(), z.end(), [](const std::pair<int, float>& a, const std::pair<int, float>& b)
    {
      return a.second < b.second;
    });

  for (auto j : z)
  {
    ResolveDynamicRectVsRect(&player, fElapsedTime, vPlats[j.first]);
  }

  for(int i = 0; i < vPlats.size(); ++i)
  {
    if(player.GetPosition().y + player.GetSize().y == vPlats[i].GetPosition().y)
    {
      player.SetOnGround(true);
      //m_DebugMessage = "Player is on the ground";
      break;
    }
    else
    {
      player.SetOnGround(false);
      //m_DebugMessage = "Player not on ground";
    }
  }

  for(int i = 0; i < vPlats.size(); ++i)
  {
    if(player.GetPosition().x + player.GetSize().x == vPlats[i].GetPosition().x)
    {
      player.SetSideCollision(true);
      break;
    }
    else if (player.GetPosition().x == vPlats[i].GetPosition().x + vPlats[i].GetWidth())
    {
      player.SetSideCollision(true);
      break;
    }
    else
    {
      player.SetSideCollision(false);
    }
  }

  player.SetPosition(player.GetPosition() + player.vel * fElapsedTime);

  return true;
}
