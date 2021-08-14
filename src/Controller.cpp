#include "Controller.h"

Controller::Controller()
{
  m_dPadDirection = dPad::Still;
}

Controller::~Controller() { }

int Controller::GetIndex() const
{
  return m_ControllerIndex;
}

void Controller::SetIndex(unsigned int i)
{
  m_ControllerIndex = i;
}

std::string Controller::GetName() const
{
  return m_ControllerName;
}

void Controller::SetName()
{
  m_ControllerName = sf::Joystick::getIdentification(m_ControllerIndex).name;;
}

//**************************This method will be needed for reconfiguring buttons in the options menu, but not used yet*************************************//
void Controller::ButtonCount()
{
  m_ButtonNumber = sf::Joystick::getButtonCount(m_ControllerIndex);
}


void Controller::SetDefaultButtonMap()
{
  m_ButtonMap.clear();
  ButtonCount();
  std::string defaultDirectives[3] = {"Run", "Jump", "Attack"};

  // for(int i = 0; i < 3; ++i)
  // {
  //   m_ButtonMap.insert({defaultDirectives[i], i});
  // }

  m_ButtonMap.insert({defaultDirectives[0], 0});
  m_ButtonMap.insert({defaultDirectives[1], 1});
  m_ButtonMap.insert({"Attack", 5}); //The default were okay, but it makes the attack button difficult to use.  The most logical attack button would be L or R

  m_ButtonMap.insert({"Start", m_ButtonNumber - 1});
  m_ButtonMap.insert({"Select", m_ButtonNumber - 2});
}

int Controller::ButtonPushed(std::string button)
{
  for( const auto& itr : m_ButtonMap)
  {
    if(itr.first == button)
    {
      return itr.second;
    }
  }
  return -1;  //Return -1 if button index isn't found
}

//This may not be the best approach below, and doesn't work so well with controllers (as opposed to game pads, those seem
//to work just fine).  Looks like you should spend some time looking at the JoyStickMoveEvent:
//https://www.sfml-dev.org/documentation/2.5.1/structsf_1_1Event_1_1JoystickMoveEvent.php
dPad Controller::GetDPadDirection()
{
  m_dPadXAxis = sf::Joystick::getAxisPosition(m_ControllerIndex, sf::Joystick::X);
  m_dPadYAxis = sf::Joystick::getAxisPosition(m_ControllerIndex, sf::Joystick::Y);

  if(m_dPadXAxis == 0 && m_dPadYAxis == 0)
  {
    m_dPadDirection = dPad::Still;
  }
  else if(m_dPadXAxis < 0 && m_dPadYAxis == 0)
  {
    m_dPadDirection = dPad::Left;
  }
  else if(m_dPadXAxis > 0 && m_dPadYAxis == 0)
  {
    m_dPadDirection = dPad::Right;
  }
  else if(m_dPadXAxis == 0 && m_dPadYAxis < 0)
  {
    m_dPadDirection = dPad::Up;
  }
  else if(m_dPadXAxis == 0 && m_dPadYAxis > 0)
  {
    m_dPadDirection = dPad::Down;
  }
  else if(m_dPadXAxis < 0 && m_dPadYAxis < 0)
  {
    m_dPadDirection = dPad::Upper_Left;
  }
  else if(m_dPadXAxis < 0 && m_dPadYAxis > 0)
  {
    m_dPadDirection = dPad::Lower_Left;
  }
  else if(m_dPadXAxis > 0 && m_dPadYAxis > 0)
  {
    m_dPadDirection = dPad::Lower_Right;
  }
  else if(m_dPadXAxis > 0 && m_dPadYAxis < 0)
  {
    m_dPadDirection = dPad::Upper_Right;
  }

  return m_dPadDirection;
}
