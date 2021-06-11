#pragma once
#include <SFML/Graphics.hpp>
#include "EventManager.h"
#include "GameState.h"
#include "PlayerAction.h"
#include "PlayerMovement.h"
#include <iostream>

class Window {
public:
  Window();
  ~Window();

  bool IsDone() const;
  void Close();
  void Update();
  void SetView(sf::View view);
  sf::View GetDefaultView();

  void BeginDraw();
  void EndDraw();

  void Draw(sf::Drawable& object);

  sf::Vector2u GetSize();

  GameState GetState() const;
  void SetState(GameState l_state);

  std::string GetMenuDirection() const;
  void ClearMenuDirection();
  bool MenuItemSelected() const;

  std::vector<PlayerMovement> GetPlayerDirectives() const;
  std::vector<PlayerAction> GetPlayerActions() const;

private:
  sf::RenderWindow m_window;
  EventManager m_eventManager;
  bool m_isDone;
  bool m_menuItemSelected;
  GameState m_state;
  std::string m_menuDirection;
  std::vector<PlayerMovement> m_PlayerDirectives;
  std::vector<PlayerAction> m_PlayerActions;

};
