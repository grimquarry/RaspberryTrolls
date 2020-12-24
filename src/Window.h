#pragma once
#include <SFML/Graphics.hpp>
#include "EventManager.h"
#include "GameState.h"
#include <iostream>

class Window {
public:
  Window();
  ~Window();

  bool IsDone() const;
  void Close();
  void Update();

  void SetView(sf::View view);

  void BeginDraw();
  void EndDraw();

  void Draw(sf::Drawable& object);

  sf::Vector2u GetSize();

  GameState GetState() const;
  void SetState(GameState l_state);

  std::string GetMenuDirection() const;
  void ClearMenuDirection();
  bool MenuItemSelected() const;

  std::string GetPlayerDirective() const;
  //std::string GetPlayerAction() const;
  std::vector<std::string> GetPlayerActions() const;

private:
  sf::RenderWindow m_window;
  EventManager m_eventManager;
  bool m_isDone;
  bool m_menuItemSelected;
  GameState m_state;
  std::string m_menuDirection;
  std::string m_PlayerDirective;
  //std::string m_PlayerAction;
  std::vector<std::string> m_PlayerActions;

};
