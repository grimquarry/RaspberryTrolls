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
  Jump, Land, Attack, Run, Walk, None
};

class Player
{
public:
  Player();
  ~Player();

  void AddAnimTexture(std::string txtrLocation);
  void WalkAnimation();
  void HandleAnimTexture();

  float GetPlayerWidth();
  float GetPlayerHeight();

  void SetPosition(float x, float y);
  sf::Vector2f GetPosition();

  void SetPlayerMovement(PlayerMovement movement);

  PlayerMovement GetPlayerMovement();

  void SetPlayerAction(PlayerAction action);
  void ClearPlayerActions();

  void MovePlayer(float timeElapsed);

  void CollisionCheck(std::vector<sf::Vector2i> collidableObjects);

  bool OnGround();

  void Draw(Window& l_window);

protected:
  sf::Texture m_PlayerTexture;
  sf::Sprite m_PlayerSprite;
  std::vector<sf::Texture> m_TxtrAnimBuff;

private:
  PlayerMovement m_CurrentMovement;
  PlayerMovement m_PreviousMovement;
  PlayerMovement m_StopXDirection;
  PlayerAction m_AnimationAction;
  float m_PlayerPosX;
  float m_PlayerPosY;
  float m_PlayerVelX;
  float m_PlayerVelY;
  float m_PlayerWidth;
  float m_PlayerHeight;

  bool m_OnGround;
  bool m_IsRunning;
  bool m_IsWalking;
  bool m_IsJumping;
  bool m_IsLanding;
  bool m_IgnoreJump;
  bool m_LeftCollision;
  bool m_RightCollision;
  std::vector<PlayerAction> m_ActionsBuffer;
  //bool m_IsColliding;

  void ChangeXVelocity();
  float m_MaxXVelocity;
  float m_MinXVelocity;
  float m_MaxYVelocity;
  float m_MinYVelocity;

  int m_WalkAnimItr;
  int m_FrameCount;
};
