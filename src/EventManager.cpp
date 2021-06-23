#include "EventManager.h"
#include <iostream>

EventManager::EventManager()
{
  m_state = GameState::Title;
  m_quitGame = false;
  m_menuDirection = "None";
  m_LeftButtonDown = false;
  m_RightButtonDown = false;
  m_RunButtonDown = false;
  m_JumpButtonDown = false;
}
EventManager::~EventManager() { }

void EventManager::HandleEvent(sf::Event& l_event)
{
  m_changeState = false;
  m_navigateMenu = false;
  m_menuItemSelected = false;
  m_menuDirection = "None";

  EventType sfmlEvent = (EventType)l_event.type;
  switch(sfmlEvent)
  {
    case(EventType::JoystickButtonPressed):
      if(m_state == GameState::GamePlay)
      {

        if(sf::Joystick::isButtonPressed(m_Controller1.GetIndex(), m_Controller1.ButtonPushed("Run")))
        {
          m_RunButtonDown = true;
          if(!m_ActionDirectives.empty())
          {
            // std::cout << "Values in EventManager PlayerAction Vector: " << std::endl;
            // for(int i = 0; i < m_ActionDirectives.size(); ++i)
            // {
            //   std::cout << i << ": " << static_cast<std::underlying_type<PlayerAction>::type>(m_ActionDirectives[i]) << std::endl;
            // }

            std::replace (m_ActionDirectives.begin(), m_ActionDirectives.end(), PlayerAction::Walk, PlayerAction::Run);
          }
          else { m_ActionDirectives.push_back(PlayerAction::Run); }
        }
        if(sf::Joystick::isButtonPressed(m_Controller1.GetIndex(), m_Controller1.ButtonPushed("Jump")))
        {
          m_JumpButtonDown = true;
          m_ActionDirectives.push_back(PlayerAction::Jump);
          std::cout << "Jump button was pressed" << std::endl;
        }
        if(sf::Joystick::isButtonPressed(m_Controller1.GetIndex(), m_Controller1.ButtonPushed("Attack")))
        {
          std::cout << "Attack button was pressed" << std::endl;
        }
        if(sf::Joystick::isButtonPressed(m_Controller1.GetIndex(), m_Controller1.ButtonPushed("Select")))
        {
          std::cout << "Select button was pressed" << std::endl;
        }
        if(sf::Joystick::isButtonPressed(m_Controller1.GetIndex(), m_Controller1.ButtonPushed("Start")))
        {
          std::cout << "Start button was pressed" << std::endl;
        }
      }
      else if(m_state == GameState::Title)
      {
        if(sf::Joystick::isButtonPressed(m_Controller1.GetIndex(), m_Controller1.ButtonPushed("Start")))
        {
          std::cout << "Start button was pressed" << std::endl;
          m_menuItemSelected = true;
        }
      }
    break;
    case(EventType::JoystickButtonReleased):
      if(m_state == GameState::GamePlay)
      {
        if(!sf::Joystick::isButtonPressed(m_Controller1.GetIndex(), m_Controller1.ButtonPushed("Run")))
        {
          m_RunButtonDown = false;
          if(!m_ActionDirectives.empty())
          {
            std::replace (m_ActionDirectives.begin(), m_ActionDirectives.end(), PlayerAction::Run, PlayerAction::Walk);
          }
          else { m_ActionDirectives.push_back(PlayerAction::Walk); }
        }
        if(!sf::Joystick::isButtonPressed(m_Controller1.GetIndex(), m_Controller1.ButtonPushed("Jump")))
        {
          m_ActionDirectives.push_back(PlayerAction::Land);
          m_JumpButtonDown = false;
        }
      }
    break;
    case(EventType::Closed):
      m_quitGame = true;
    break;
    case(EventType::KeyPressed):
      if(l_event.key.code == sf::Keyboard::Escape)
      {
        m_quitGame = true;
      }
      if(m_state == GameState::GamePlay)
      {
        if(l_event.key.code == sf::Keyboard::Right)
        {
          m_RightButtonDown = true;
          m_MoveDirectives.push_back(PlayerMovement::Right);
          if(m_RunButtonDown)
          {
            m_ActionDirectives.push_back(PlayerAction::Run);
          }
          else
          {
            m_ActionDirectives.push_back(PlayerAction::Walk);
          }

        }
        else if(l_event.key.code == sf::Keyboard::Left)
        {
          m_LeftButtonDown = true;
          m_MoveDirectives.push_back(PlayerMovement::Left);
          if(m_RunButtonDown)
          {
            m_ActionDirectives.push_back(PlayerAction::Run);
          }
          else
          {
            m_ActionDirectives.push_back(PlayerAction::Walk);
          }
        }

        if(l_event.key.code == sf::Keyboard::Down)
        {
          m_MoveDirectives.push_back(PlayerMovement::Down);
        }
        else if(l_event.key.code == sf::Keyboard::Up)
        {
          m_MoveDirectives.push_back(PlayerMovement::Up);
        }

        if(l_event.key.code == sf::Keyboard::Space)
        {
          m_ActionDirectives.push_back(PlayerAction::Jump);
        }
        if(l_event.key.code == sf::Keyboard::A)
        {
          m_RunButtonDown = true;
          if(!m_ActionDirectives.empty())
          {
            std::replace (m_ActionDirectives.begin(), m_ActionDirectives.end(), PlayerAction::Walk, PlayerAction::Run);
          }
          else { m_ActionDirectives.push_back(PlayerAction::Run); }
        }
      }
    break;

    case(EventType::KeyReleased):
      switch (l_event.key.code)
      {
        case sf::Keyboard::Up:
          if(m_state == GameState::Title || m_state == GameState::Options) // might need to add the paused games state here, too
          {
            m_navigateMenu = true;
            m_menuDirection = "Up";
          }
          else if(m_state == GameState::GamePlay)
          {
            m_MoveDirectives.push_back(PlayerMovement::StillY);
          }
          break;
        case sf::Keyboard::Down:
          if(m_state == GameState::Title || m_state == GameState::Options)
          {
            m_navigateMenu = true;
            m_menuDirection = "Down";
          }
          else if(m_state == GameState::GamePlay)
          {
            m_MoveDirectives.push_back(PlayerMovement::StillY);
          }
          break;
        case sf::Keyboard::Enter:
          m_menuItemSelected = true;
          break;
        case sf::Keyboard::Right:
          if(m_state == GameState::GamePlay)
          {
            m_RightButtonDown = false;
            if(!m_LeftButtonDown)
            {
              if(!m_MoveDirectives.empty() && !m_LeftButtonDown)
              {
                std::replace (m_MoveDirectives.begin(), m_MoveDirectives.end(), PlayerMovement::Right, PlayerMovement::StillX);
                std::replace(m_ActionDirectives.begin(), m_ActionDirectives.end(), PlayerAction::Walk, PlayerAction::Stop);
              }
              else
              {
                m_MoveDirectives.push_back(PlayerMovement::StillX);
                m_ActionDirectives.push_back(PlayerAction::Stop);
              }
            }
          }
        break;
        case sf::Keyboard::Left:
            if(m_state == GameState::GamePlay)
            {
              m_LeftButtonDown = false;
              if(!m_RightButtonDown)
              {
                if(!m_MoveDirectives.empty())
                {
                  std::replace (m_MoveDirectives.begin(), m_MoveDirectives.end(), PlayerMovement::Left, PlayerMovement::StillX);
                  std::replace(m_ActionDirectives.begin(), m_ActionDirectives.end(), PlayerAction::Walk, PlayerAction::Stop);
                }
                else
                {
                  m_MoveDirectives.push_back(PlayerMovement::StillX);
                  m_ActionDirectives.push_back(PlayerAction::Stop);
                }
              }
            }
          break;
          case sf::Keyboard::Space:
            if(m_state == GameState::GamePlay)
            {
              if(!m_ActionDirectives.empty())
              {
                std::replace (m_ActionDirectives.begin(), m_ActionDirectives.end(), PlayerAction::Jump, PlayerAction::Land);
              }
              else { m_ActionDirectives.push_back(PlayerAction::Land); }
            }
          break;
          case sf::Keyboard::A:
            if(m_state == GameState::GamePlay)
            {
              m_RunButtonDown = false;
              if(!m_ActionDirectives.empty())
              {
                std::replace (m_ActionDirectives.begin(), m_ActionDirectives.end(), PlayerAction::Run, PlayerAction::Walk);
              }
              else { m_ActionDirectives.push_back(PlayerAction::Walk); }
            }
          break;
      }
      break;
  }
}

void EventManager::Update()
{
  return;
}

bool EventManager::QuitGame() const { return m_quitGame; }
bool EventManager::ChangeState() const { return m_changeState; }
bool EventManager::NavigateMenu() const { return m_navigateMenu; }
bool EventManager::MenuItemSelected() const { return m_menuItemSelected; }

GameState EventManager::SetState(GameState l_state)
{
  m_state = l_state;
  return m_state;
}

GameState EventManager::GetState() const { return m_state; }

std::string EventManager::GetMenuDirection() const { return m_menuDirection; }

void EventManager::ClearMovementDirectives() { m_MoveDirectives.clear(); }
void EventManager::ClearActionDirectives() { m_ActionDirectives.clear(); }

std::vector<PlayerMovement> EventManager::GetPlayerDirectives() const { return m_MoveDirectives; }
std::vector<PlayerAction> EventManager::GetPlayerActions() const { return m_ActionDirectives; };
void EventManager::SetControllers()
{
  for(int i = 0; i < sf::Joystick::Count; ++i)
  {
    if(sf::Joystick::isConnected(i))
    {
      if(i == 0)
      {
        m_Controller1.SetIndex(i);
        m_Controller1.SetName();
        m_Controller1.SetDefaultButtonMap();
      }
      else if(i == 1)
      {
        m_Controller2.SetIndex(i);
        m_Controller2.SetName();
        m_Controller2.SetDefaultButtonMap();
      }
    }
  }

  if(sf::Joystick::isConnected(0))
  {
    m_Controller1.SetIndex(0);
    m_Controller1.SetName();
    m_Controller1.SetDefaultButtonMap();
    std::cout << "Controller " << m_Controller1.GetName() << " was found" << std::endl;
    // std::cout << "Controller X Axis Postion is: " << sf::Joystick::getAxisPosition(0, sf::Joystick::X) << std::endl;
    // std::cout << "Controller Y Axis Positsion is: " << sf::Joystick::getAxisPosition(0, sf::Joystick::Y) << std::endl;
  }
}

void EventManager::CheckdPad()
{
  m_dPadDirection = m_Controller1.GetDPadDirection();
  switch(m_dPadDirection)
  {
    case(dPad::Up):
      if(m_state == GameState::Title || m_state == GameState::Options)
      {
        m_navigateMenu = true;
        m_menuDirection = "Up";
      }
      else if(m_state == GameState::GamePlay)
      {
        m_MoveDirectives.push_back(PlayerMovement::Up);
      }
      break;
    case(dPad::Down):
      if(m_state == GameState::Title || m_state == GameState::Options)
      {
        m_navigateMenu = true;
        m_menuDirection = "Down";
      }
      else if(m_state == GameState::GamePlay)
      {
        m_MoveDirectives.push_back(PlayerMovement::Down);
      }
      break;
    case(dPad::Right):
      if(m_state == GameState::GamePlay)
      {
        m_RightButtonDown = true;
        m_LeftButtonDown = false;
        m_MoveDirectives.push_back(PlayerMovement::Right);
        if(!m_RunButtonDown)
        {
          m_ActionDirectives.push_back(PlayerAction::Walk);
        }
        else { m_ActionDirectives.push_back(PlayerAction::Run); }
      }
      break;
    case(dPad::Left):
      {
        if(m_state == GameState::GamePlay)
        {
          m_LeftButtonDown = true;
          m_RightButtonDown = false;
          m_MoveDirectives.push_back(PlayerMovement::Left);
          if(!m_RunButtonDown)
          {
            m_ActionDirectives.push_back(PlayerAction::Walk);
          }
          else { m_ActionDirectives.push_back(PlayerAction::Run); }

        }
      }
      break;
    case(dPad::Upper_Right):
      std::cout << "Upper_Right pushed on dpad" << std::endl;
      break;
    case(dPad::Lower_Right):
      std::cout << "Lower_Right pushed on dpad" << std::endl;
      break;
    case(dPad::Upper_Left):
      std::cout << "Upper_Left pushed on dpad" << std::endl;
      break;
    case(dPad::Lower_Left):
      std::cout << "Lower_Left pushed on dpad" << std::endl;
      break;
    default:
      m_MoveDirectives.push_back(PlayerMovement::StillX);
      m_ActionDirectives.push_back(PlayerAction::Stop);
      break;
  }
}
