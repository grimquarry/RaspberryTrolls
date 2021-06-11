#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Window.h"
#include "GameState.h"

class Menu
{
public:
  Menu();
  ~Menu();

  void SetPosition(float x, float y);
  void Draw(Window& l_window);
  void Navigate(std::vector<std::string> optionsBuffer, int menuIndex);
  void ProcessSelection(Window& window, std::vector<std::string> optionsBuffer);
  void SetOptions(std::vector<std::string> optionsBuffer);

private:
  GameState m_gameState;
  int m_selectedItemIndex;
  int m_numberOfOptions;
  sf::RectangleShape m_menuContainer;
  sf::Font m_font;
  std::vector<sf::Text> m_menu;
};
