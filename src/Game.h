#pragma once

#include <vector>

#include "Window.h"
#include "GameState.h"
#include "Enemy.h"
#include "TitleScreen.h"
#include "Menu.h"
#include "OptionsScreen.h"
#include "Level.h" //Likely will need to change this to LevelManger, this is for testing purposes.
#include "Player.h"


class Game {
public:
  Game();
  ~Game();

  void Update();
  void Render();

  Window* GetWindow();

protected: //Apperantly anything tied to an SFML texture must be public or protected (perhaps it's how I'm using it?  possibly incorrectly?)
  Level testLevel;
  Player m_Player1;

private:
  Window m_window;
  sf::View m_gameCamera;
  Enemy m_enemy;
  GameState m_state;

  TitleScreen m_titleScreen;
  Menu m_menu;
  std::vector<std::string> m_titleSelectBuffer;
  int m_menuIndex;

  OptionsScreen m_optionScreen;
  Menu m_optionsMenu;
  std::vector<std::string> m_optionsSelectBuffer;
  int m_optionsMenuIndex;

  float m_playerStartPositionX;
  float m_playerStartPositionY;

};
