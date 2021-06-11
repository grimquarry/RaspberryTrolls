#pragma once

#include <SFML/Window/Joystick.hpp>
#include <unordered_map>

enum class dPad
{
  Left, Right, Up, Down, Still, Upper_Right, Upper_Left, Lower_Right, Lower_Left
};

class Controller
{
public:
  Controller();
  ~Controller();

  int GetIndex() const;
  void SetIndex(unsigned int i);

  std::string GetName() const;
  void SetName();

  void ButtonCount();
  void SetDefaultButtonMap();

  int ButtonPushed(std::string button);

  dPad GetDPadDirection();


private:
  int m_ControllerIndex;
  std::string m_ControllerName;
  unsigned int m_ButtonNumber;

  std::unordered_map <std::string, unsigned int> m_ButtonMap;

  dPad m_dPadDirection;
  int m_dPadXAxis;
  int m_dPadYAxis;
};
