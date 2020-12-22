#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Window.h"

enum class PlayerMovement
{
  Still, Left, Right, Up, Down
};

enum class PlayerAction
{
  Jump, Attack, Run, None
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

  void SetPlayerAction(PlayerAction action);

  void MovePlayer(float timeElapsed);

  void Jump(float timeElapsed);

  void CollisionCheck(std::vector<sf::Vector2i> collidableObjects);

  //Commenting out because m_OnGround flag is set with collision checks, but not sure if new solution has bugs or not.
  // bool GetOnGround(std::vector<sf::Vector2i> platformObjects);

  bool OnGround();

  void Draw(Window& l_window);

protected:
  sf::Texture m_PlayerTexture;
  sf::Sprite m_PlayerSprite;
  std::vector<sf::Texture> m_TxtrAnimBuff; //I'm thinking 1 for still, 2 for Left & Right (flip to go right), 2 for up and Down, and 2 for attack

private:
  PlayerMovement m_CurrentMovement;
  PlayerAction m_CurrentAction;
  float m_PlayerPosX;
  float m_PlayerPosY;
  float m_PlayerVelX;
  float m_PlayerVelY;
  float m_PlayerWidth;
  float m_PlayerHeight;

  float m_Gravity;
  bool m_OnGround;
  //bool m_IsColliding;

};
