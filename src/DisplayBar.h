#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Window.h"
#include "Player.h"

class DisplayBar
{
public:
  DisplayBar();
  ~DisplayBar();

  void GetPlayerInfo(Player& player);
  void Draw(Window& win);

private:
  sf::Font m_NesFont;
  sf::Text m_PlayerName;
  sf::Text m_PlayerScore;
  sf::Text m_Level;

};
