#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Window.h"

enum class PlayerMovement
{
  Still, Left, Right, Up, Down, Jump, Attack
};

class Player
{
public:
  Player();
  ~Player();

  void AddAnimTexture(std::string txtrLocation);

  float GetPlayerWidth();
  float GetPlayerHeight();

  void SetPosition(float x, float y);
  sf::Vector2f GetPosition();

  void SetPlayerMovement(PlayerMovement movement);

  PlayerMovement GetPlayerMovement();

  void MovePlayer();

  void CollisionCheck(std::vector<sf::Vector2i> collidableObjects);

  void Draw(Window& l_window);

protected:
  sf::Texture m_PlayerTexture;
  sf::Sprite m_PlayerSprite;
  std::vector<sf::Texture> m_TxtrAnimBuff; //I'm thinking 1 for still, 2 for Left & Right (flip to go right), 2 for up and Down, and 2 for attack

private:
  PlayerMovement m_CurrentMovement;
  float m_PlayerPosX;
  float m_PlayerPosY;
  float m_PlayerVelX;
  float m_PlayerVelY;
  float m_PlayerWidth;
  float m_PlayerHeight;

};
