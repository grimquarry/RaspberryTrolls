#pragma once
#include <SFML/Window/Joystick.hpp> //Dynamically Linked (SFML Libraries must be discoverable in your $PATH)
#include <SFML/Graphics.hpp> //Dynamically Linked (SFML Libraries must be discoverable in your $PATH)
#include <iostream>
#include <vector>
#include "GameState.h"
#include "Controller.h"

enum class EventType {
  Closed = sf::Event::Closed,
  TextEntered = sf::Event::TextEntered,
  KeyPressed = sf::Event::KeyPressed,
  KeyReleased = sf::Event::KeyReleased,
  MouseWheelScrolled = sf::Event::MouseWheelScrolled,
  MouseButtonPressed = sf::Event::MouseButtonPressed,
  MouseButtonReleased = sf::Event::MouseButtonReleased,
  MouseMoved = sf::Event::MouseMoved,
  JoystickButtonPressed = sf::Event::JoystickButtonPressed,
  JoystickButtonReleased = sf::Event::JoystickButtonReleased,
  JoystickMoved = sf::Event::JoystickMoved,
  JoystickConnected = sf::Event::JoystickConnected,
  Count = sf::Event::Count
};

class EventManager {
public:
  EventManager();
  ~EventManager();

  void HandleEvent(sf::Event& l_event);
  void Update();

  bool QuitGame() const;
  bool ChangeState() const;
  bool NavigateMenu() const;
  bool MenuItemSelected() const;
  GameState SetState(GameState l_state);
  GameState GetState() const;
  std::string GetMenuDirection() const;
  std::string GetPlayerDirective() const;
  std::vector<std::string> GetPlayerActions() const;


  void SetControllers();

  void CheckdPad();

private:
  bool m_quitGame;
  bool m_changeState;
  bool m_navigateMenu;
  bool m_menuItemSelected;
  GameState m_state;
  std::string m_menuDirection;

  Controller m_Controller1;
  Controller m_Controller2;

  dPad m_dPadDirection;

  std::string m_PlayerMoveDirective;
  std::string m_PreviousMoveDirective; //Keep track of last directive for keyboard press logic
  std::vector<std::string> m_ActionDirectives;

  //Private Methods
  //This method does some cleanup of my bad user input logic for when an action changes
  //For example when the player jumps then lands, we need to remove the jump directive
  //and replace it with the "Land directive".  This should be used for when an action
  //button is released after being pressed.
  void ActionCleanup(std::string s_changeFrom, std::string s_changeTo);
};
