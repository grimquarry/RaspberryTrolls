#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "PlayerMovement.h"
#include "PlayerAction.h"

class Player
{
public:

  Player();

  ~Player();

  void SetMoveDirectives(std::vector<PlayerMovement> vMovements);
  void SetActionDirectives(std::vector<PlayerAction> vActions);

  void Move();
  void StopX();
  void StopY();

  void SetOnGround(bool b);
  bool GetOnGround();

  sf::Vector2f vel;

  sf::Vector2f GetPosition() const;

  void AddAnimTexture(std::string txtrLocation);

  sf::Vector2f GetSize() const;

  void WalkAnimation();

  void HandleAnimTexture();

  void SetPosition(float x, float y);

  void SetPosition(sf::Vector2f pos);

  void Draw(Window& l_window);

protected:
  sf::Texture m_PlayerTexture;
  sf::Sprite m_PlayerSprite;
  std::vector<sf::Texture> m_TxtrAnimBuff;

private:
  sf::Vector2f m_Position;
  int m_WalkAnimItr;
  int m_FrameCount;
  std::vector<PlayerMovement> m_MovementBuffer;
  std::vector<PlayerAction> m_ActionsBuffer;
  float m_MaxWalkVelocity;
  float m_MinWalkVelocity;
  float m_MaxRunVelocity;
  float m_MinRunVelocity;
  float m_VelocityIncrement;
  bool m_OnGround;
  bool m_Jump;
  bool m_Land;
  bool m_Right;
  bool m_Left;
  bool m_Stop;
  bool m_Run;
  bool m_Walk;
};
