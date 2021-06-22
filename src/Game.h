#pragma once
#include <iostream>
#include <vector>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "Window.h"
#include "GameState.h"
#include "TitleScreen.h"
#include "Menu.h"
#include "OptionsScreen.h"
#include "CollisionHandler.h"
#include "LevelManager.h"
#include "Player.h"
#include "Platform.h"
#include "DisplayBar.h"


class Game {
public:
  Game();
  ~Game();

  void Update();
  void Render();

  Window* GetWindow();

protected: //Apperantly anything tied to an SFML texture must be public or protected (perhaps it's how I'm using it?  possibly incorrectly?)
  //Level m_Level_1_1;
  Player m_Player1;
  std::vector<Platform> vPlats;


private:
  Window m_window;
  sf::View m_gameCamera;
  sf::Time m_ElapsedTime;
  sf::Clock m_GameClock;
  GameState m_state;

  LevelManager m_LevelManager;

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

  std::vector<std::string> m_PlayerActions;

  CollisionHandler m_CollisionHandler;

  DisplayBar m_DisplayBar;
};
