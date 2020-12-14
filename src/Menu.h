#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Window.h"
#include "GameState.h"

//#define MAX_NUMBER_OF_OPTIONS 3

class Menu
{
public:
  Menu();
  ~Menu();

  void SetPosition(float x, float y);
  void Draw(Window& l_window);
  //void MoveUp(std::vector<std::string> optionsBuffer);
  void Navigate(std::vector<std::string> optionsBuffer, int menuIndex);
  void ProcessSelection(Window& window, std::vector<std::string> optionsBuffer);
  void SetOptions(std::vector<std::string> optionsBuffer);

private:
  GameState m_gameState;
  int m_selectedItemIndex;
  int m_numberOfOptions;
  sf::RectangleShape m_menuContainer;
  sf::Font m_font;
  //sf::Text m_menu[MAX_NUMBER_OF_OPTIONS];
  std::vector<sf::Text> m_menu;
  //std::string m_selection[MAX_NUMBER_OF_OPTIONS] = { "Play", "Options", "Exit" };
  //std::string m_selections[];
  //std::vector<std::string> m_optionsBuffer;
};
