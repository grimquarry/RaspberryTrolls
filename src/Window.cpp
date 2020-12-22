#include "Window.h"

Window::Window(){
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

  m_window.create(sf::VideoMode(desktop), "Buckets & Vonni Versus the Raspberry Troll", sf::Style::Fullscreen | sf::Style::Close);
  //m_window.create(sf::VideoMode(1920, 1080, desktop.bitsPerPixel), "Buckets & Vonni Versus the Raspberry Troll", sf::Style::Fullscreen | sf::Style::Close);
  m_window.setFramerateLimit(60);
  m_window.setMouseCursorVisible(false);
  m_state = GameState::Title;
  m_menuItemSelected = false;

  // m_eventManager.SetControllers();

  // for(int i = 0; i < sf::Joystick::Count; ++i)
	// {
	// 	if(sf::Joystick::isConnected(i))
  //   {
  //     std::cout << "Controller found at index: " << i << std::endl;
  //   }
  // }
}

Window::~Window() { }

bool Window::IsDone() const { return m_isDone; }
void Window::Close() { m_isDone = true; }

void Window::SetView(sf::View view)
{
  m_window.setView(view);
}

void Window::BeginDraw() { m_window.clear(sf::Color::White); }
void Window::Draw(sf::Drawable& object)
{
  m_window.draw(object);
}
void Window::EndDraw() { m_window.display(); }

void Window::Update()
{
  sf::Event event;
  m_menuItemSelected = false;

  while (m_window.pollEvent(event))
  {
    m_eventManager.HandleEvent(event);
    m_eventManager.SetControllers();
    if(sf::Joystick::isConnected(0) || sf::Joystick::isConnected(1))
    {
      m_eventManager.CheckdPad();
    }
    if(m_eventManager.QuitGame())
    {
      Close();
    }
    else if(m_eventManager.ChangeState())
    {
      m_state = m_eventManager.GetState();
    }
    else if(m_eventManager.NavigateMenu())
    {
      m_menuDirection = m_eventManager.GetMenuDirection();
    }
    else if(m_eventManager.MenuItemSelected())
    {
      m_menuItemSelected = true;
    }

    if(m_state == GameState::GamePlay)
    {
      m_PlayerDirective = m_eventManager.GetPlayerDirective();
      m_PlayerAction = m_eventManager.GetPlayerAction();
    }
  }
}

GameState Window::GetState() const { return m_state; }
void Window::SetState(GameState l_state)
{
  m_state = l_state;
  m_eventManager.SetState(l_state);
}

std::string Window::GetMenuDirection() const
{
  return m_menuDirection;
}

void Window::ClearMenuDirection()
{
  m_menuDirection = "None";
}

bool Window::MenuItemSelected() const { return m_menuItemSelected; }

sf::Vector2u Window::GetSize()
{
  sf::Vector2u size = m_window.getSize();
  return size;
}

std::string Window::GetPlayerDirective() const { return m_PlayerDirective; }

std::string Window::GetPlayerAction() const { return m_PlayerAction; }
