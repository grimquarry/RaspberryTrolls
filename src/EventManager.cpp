#include "EventManager.h"
#include <iostream>

EventManager::EventManager()
{
  m_state = GameState::Title;
  m_quitGame = false;
  m_menuDirection = "None";
  m_PlayerMoveDirective = "Still";
  m_PreviousMoveDirective = "Still";  //Setting this to Still essentially resets it, which is necessary when a key is released
}
EventManager::~EventManager() { }

void EventManager::ActionCleanup(std::string s_changeFrom, std::string s_changeTo)
{
  for(int i = 0; i < m_ActionDirectives.size(); i++)
  {
    if(m_ActionDirectives[i] == s_changeFrom)
    {
      m_ActionDirectives.erase(m_ActionDirectives.begin() + i);
      m_ActionDirectives.push_back(s_changeTo);
    }
  }
}

void EventManager::HandleEvent(sf::Event& l_event)
{
  m_changeState = false;
  m_navigateMenu = false;
  m_menuItemSelected = false;
  m_menuDirection = "None";

  EventType sfmlEvent = (EventType)l_event.type;
  //std::cout << "Controller X Axis Postion is: " << sf::Joystick::getAxisPosition(0, sf::Joystick::X) << std::endl;
  //std::cout << "Controller Y Axis Positsion is: " << sf::Joystick::getAxisPosition(0, sf::Joystick::Y) << std::endl;
  switch(sfmlEvent)
  {
    case(EventType::JoystickButtonPressed):
      if(m_state == GameState::GamePlay)
      {
        //Start with a fresh actions buffer
        if(!m_ActionDirectives.empty())
        {
          m_ActionDirectives.clear();
        }

        if(sf::Joystick::isButtonPressed(m_Controller1.GetIndex(), m_Controller1.ButtonPushed("Run")))
        {
          m_ActionDirectives.push_back("Run");
          std::cout << "Run button was pressed" << std::endl;
        }
        if(sf::Joystick::isButtonPressed(m_Controller1.GetIndex(), m_Controller1.ButtonPushed("Jump")))
        {
          m_ActionDirectives.push_back("Jump");
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
          if(!m_ActionDirectives.empty())
          {
            ActionCleanup("Run", "Walk");
          }
        }
        if(!sf::Joystick::isButtonPressed(m_Controller1.GetIndex(), m_Controller1.ButtonPushed("Jump")))
        {
          if(!m_ActionDirectives.empty())
          {
            ActionCleanup("Jump", "Land");
          }
        }
      }
    break;
    case(EventType::Closed):
      m_quitGame = true;
    break;
    case(EventType::KeyPressed):
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
        m_quitGame = true;
      }
      if(m_state == GameState::GamePlay)
      {

        //Start with a fresh actions buffer
        if(!m_ActionDirectives.empty())
        {
          m_ActionDirectives.clear();
        }
        //This serires of conditional statements first checks to see if a key is pressed.  If it is, it then checks to see if the player is already moving in that direction.
        //If the player is already going in the direction, the conditional is passed over and the program is essentially waiting for that key to be lifted to stop the Player
        //from moving in that direction.  To account for the fact people will sometimes press another direction before they lift the key of the previous direction the m_PreviousMoveDirective
        //was created.  The logic will skip over the conditional if the previous move directive is the same as the key being pressed because the only way that could happen (I think) is
        //if two keys are being pressed at the same time.  For example: if Right is pressed, then Down is pressed, and both are held down at the same time, the
        //m_PreviousMoveDirective will be Right, causing the if statement to be passed over.  Ultimately, checking that previous directive makes it so the sprite doesn zig zag
        //between Right and Down or any other combination of two keys that are being pressed, it will only go in the direction that resulted from the most recent key press.
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_PlayerMoveDirective != "Right" && m_PreviousMoveDirective !="Right")
        {
          m_PreviousMoveDirective = m_PlayerMoveDirective;
          m_PlayerMoveDirective = "Right";
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_PlayerMoveDirective != "Left" && m_PreviousMoveDirective != "Left")
        {
          m_PreviousMoveDirective = m_PlayerMoveDirective;
          m_PlayerMoveDirective = "Left";
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_PlayerMoveDirective != "Down" && m_PreviousMoveDirective != "Down")
        {
          m_PreviousMoveDirective = m_PlayerMoveDirective;
          m_PlayerMoveDirective = "Down";
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_PlayerMoveDirective != "Up" && m_PreviousMoveDirective != "Up")
        {
          m_PreviousMoveDirective = m_PlayerMoveDirective;
          m_PlayerMoveDirective = "Up";
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
          m_ActionDirectives.push_back("Jump");
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
          m_ActionDirectives.push_back("Run");
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
          m_ActionDirectives.push_back("Walk");
        }
      }
    break;

    case(EventType::KeyReleased):
      switch (l_event.key.code)
      {
        case sf::Keyboard::Space:
          if(m_state == GameState::GamePlay)
          {
            if(m_state == GameState::GamePlay)
            {
              if(!m_ActionDirectives.empty())
              {
                ActionCleanup("Jump", "Land");
              }
            }
          }
          break;
        case sf::Keyboard::Key::A:
          if(m_state == GameState::GamePlay)
          {
            //std::cout << "A button was lifted" << std::endl;
            if(!m_ActionDirectives.empty())
            {
              ActionCleanup("Run", "Walk");
            }
          }
        break;
        case sf::Keyboard::Up:
          if(m_state == GameState::Title || m_state == GameState::Options) // might need to add the paused games stat here, too
          {
            m_navigateMenu = true;
            m_menuDirection = "Up";
          }
          else if(m_state == GameState::GamePlay)
          {
            m_PreviousMoveDirective = "Still"; //Reset this to Still so that key pressed logic will work when more than one key is pressed again
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
              m_PlayerMoveDirective = "Right";
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
              m_PlayerMoveDirective = "Left";
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
              m_PlayerMoveDirective = "Down";
            }
            else
            {
              m_PlayerMoveDirective = "Still";
            }
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
            m_PreviousMoveDirective = "Still"; //Reset this to Still so that key pressed logic will work when more than one key is pressed again
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
              m_PlayerMoveDirective = "Right";
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
              m_PlayerMoveDirective = "Left";
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
              m_PlayerMoveDirective = "Up";
            }
            else
            {
              m_PlayerMoveDirective = "Still";
            }
          }
          break;
        case sf::Keyboard::Enter:
          m_menuItemSelected = true;
          break;
        case sf::Keyboard::Right:
          if(m_state == GameState::GamePlay)
          {
            m_PreviousMoveDirective = "Still"; //Reset this to Still so that key pressed logic will work when more than one key is pressed again
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
              m_PlayerMoveDirective = "Up";
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
              m_PlayerMoveDirective = "Left";
              m_ActionDirectives.push_back("None");
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
              m_PlayerMoveDirective = "Right";
              m_ActionDirectives.push_back("None");
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
              m_PlayerMoveDirective = "Down";
            }
            else
            {
              m_PlayerMoveDirective = "Still";
            }
          }
          break;
        case sf::Keyboard::Left:
            if(m_state == GameState::GamePlay)
            {
              m_PreviousMoveDirective = "Still";//Reset this to Still so that key pressed logic will work when more than one key is pressed again
              if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
              {
                m_PlayerMoveDirective = "Right";
              }
              else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
              {
                m_PlayerMoveDirective = "Up";
              }
              else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
              {
                m_PlayerMoveDirective = "Down";
              }
              else
              {
                m_PlayerMoveDirective = "Still";
              }
            }
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

std::string EventManager::GetPlayerDirective() const { return m_PlayerMoveDirective; }
std::vector<std::string> EventManager::GetPlayerActions() const { return m_ActionDirectives; };
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

  // if(sf::Joystick::isConnected(0))
  // {
  //   m_Controller1.SetIndex(0);
  //   m_Controller1.SetName();
  //   m_Controller1.SetDefaultButtonMap();
  //   std::cout << "Controller " << m_Controller1.GetName() << " was found" << std::endl;
  //   // std::cout << "Controller X Axis Postion is: " << sf::Joystick::getAxisPosition(0, sf::Joystick::X) << std::endl;
  //   // std::cout << "Controller Y Axis Positsion is: " << sf::Joystick::getAxisPosition(0, sf::Joystick::Y) << std::endl;
  // }
}

void EventManager::CheckdPad()
{
  m_dPadDirection = m_Controller1.GetDPadDirection();
  switch(m_dPadDirection)
  {
    case(dPad::Up):
      //std::cout << "Up pushed on dpad" << std::endl;
      if(m_state == GameState::Title || m_state == GameState::Options)
      {
        m_navigateMenu = true;
        m_menuDirection = "Up";
      }
      else if(m_state == GameState::GamePlay)
      {
        m_PlayerMoveDirective = "Up";
      }
      break;
    case(dPad::Down):
      //std::cout << "Down pushed on dpad" << std::endl;
      if(m_state == GameState::Title || m_state == GameState::Options)
      {
        m_navigateMenu = true;
        m_menuDirection = "Down";
      }
      else if(m_state == GameState::GamePlay)
      {
        m_PlayerMoveDirective = "Down";
      }
      break;
    case(dPad::Right):
      //std::cout << "Right pushed on dpad" << std::endl;
      if(m_state == GameState::GamePlay)
      {
        m_PlayerMoveDirective = "Right";
      }
      break;
    case(dPad::Left):
      //std::cout << "Left pushed on dpad" << std::endl;
      {
        if(m_state == GameState::GamePlay)
        {
          m_PlayerMoveDirective = "Left";
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
      m_PlayerMoveDirective = "Still";
      break;
  }
}
