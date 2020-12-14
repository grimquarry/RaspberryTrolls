#include "Menu.h"

Menu::Menu()
{
  if(!m_font.loadFromFile("../resources/fonts/Ubuntu-Medium.ttf"))
  {
    std::cout << "There was a problem loading the Font file" << std::endl;
  }

  m_gameState = GameState::Title;

  m_selectedItemIndex = 0;
}

Menu::~Menu() { }

void Menu::SetPosition(float x, float y)
{
  m_menuContainer.setSize(sf::Vector2f(x / 4, y / 4));
  m_menuContainer.setOutlineColor(sf::Color::Red);
  m_menuContainer.setOutlineThickness(5);
  m_menuContainer.setFillColor(sf::Color(0, 0, 0, 200));
  float menuContainerWidth = m_menuContainer.getSize().x;
  float menuContainerHeight = m_menuContainer.getSize().y;
  m_menuContainer.setPosition(x / 2 - (menuContainerWidth / 2), y / 2 - (menuContainerHeight / 2));
  float verticalSpacing = menuContainerHeight / m_numberOfOptions;

  for(int i = 0; i < m_numberOfOptions; i++)
  {
    sf::FloatRect textBoxSize = m_menu[i].getLocalBounds();
    float textBoxWidth = textBoxSize.width;
    float textBoxHeight = textBoxSize.height;

    m_menu[i].setPosition(sf::Vector2f(m_menuContainer.getPosition().x + (m_menuContainer.getSize().x / 2) - (textBoxWidth / 2),
      (m_menuContainer.getPosition().y - (verticalSpacing * .75)) + ((i+1) * verticalSpacing)));
  }
}

void Menu::Draw(Window& l_window)
{
  l_window.Draw(m_menuContainer);
  for(int i = 0; i < m_numberOfOptions; i++)
  {
    l_window.Draw(m_menu[i]);
  }
}

void Menu::Navigate(std::vector<std::string> optionsBuffer, int menuIndex)
{
  m_selectedItemIndex = menuIndex;
  int buffSize = optionsBuffer.size();
  for(int i = 0; i < buffSize; ++i)
  {
    if(i == m_selectedItemIndex)
    {
      m_menu[i].setFillColor(sf::Color::Red);
    }
    else
    {
      m_menu[i].setFillColor(sf::Color::White);
    }
  }
}

void Menu::ProcessSelection(Window& window, std::vector<std::string> optionsBuffer)
{
  m_gameState = window.GetState();
  switch(m_gameState)
  {
    case(GameState::Title):
      if(m_selectedItemIndex == 0)
      {
        window.SetState(GameState::GamePlay);
      }
      else if(m_selectedItemIndex == 1)
      {
        window.SetState(GameState::Options);
      }
      else if(m_selectedItemIndex == 2)
      {
        window.Close();
      }
      break;
    case(GameState::Options):
      if(m_selectedItemIndex == 0)
      {
        window.SetState(GameState::GamePlay);
      }
      else if(m_selectedItemIndex == 1)
      {
        window.SetState(GameState::GamepadConfig);
      }
      else if(m_selectedItemIndex == 2)
      {
        window.SetState(GameState::KeyboardConfig);
      }
      else if(m_selectedItemIndex == 3)
      {
        window.SetState(GameState::Title);
      }
      else if(m_selectedItemIndex == 4)
      {
        window.Close();
      }
     break;
    case(GameState::GamepadConfig):
      //Add Gamepad Config Logic
      break;
    case(GameState::KeyboardConfig):
      //Add Keyboard Config Logic
      break;
  }

}

void Menu::SetOptions(std::vector<std::string> optionsBuffer)
{
  m_menu.clear();
  sf::Text element;
  for(int i = 0; i < optionsBuffer.size(); i++)
  {
    element.setString(optionsBuffer[i]);
    m_menu.push_back(element);
  }

  for(int i = 0; i < m_menu.size(); i++)
  {
    m_menu[i].setFont(m_font);
    if(i == 0)
      m_menu[i].setFillColor(sf::Color::Red);
    else
      m_menu[i].setFillColor(sf::Color::White);

    m_menu[i].setString(optionsBuffer[i]);
  }

  m_numberOfOptions = m_menu.size();
}
