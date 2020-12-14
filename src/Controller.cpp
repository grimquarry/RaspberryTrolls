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
  std::string defalutDirectives[3] = {"Run", "Jump", "Attack"};

  for(int i = 0; i < 3; ++i)
  {
    m_ButtonMap.insert({defalutDirectives[i], i});
  }

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
