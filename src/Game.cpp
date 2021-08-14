#include "Game.h"
#include <SFML/Graphics.hpp>
#include <string>

Game::Game()
{
  m_ElapsedTime = sf::seconds(0.01f);

  m_state = GameState::Title;
  m_titleSelectBuffer.push_back("Play");
  m_titleSelectBuffer.push_back("Options");
  m_titleSelectBuffer.push_back("Exit");
  m_menu.SetOptions(m_titleSelectBuffer);
  m_menuIndex = 0;

  m_optionsSelectBuffer.push_back("Play/Resume Game");
  m_optionsSelectBuffer.push_back("Configure Gamepad");
  m_optionsSelectBuffer.push_back("Change Keyboard Controlls");
  m_optionsSelectBuffer.push_back("Exit to Title Screen");
  m_optionsSelectBuffer.push_back("Exit Game");
  m_optionsMenu.SetOptions(m_optionsSelectBuffer);
  m_optionsMenuIndex = 0;


  m_Player1.SetPlayerName("BUCKETS");
  std::string pathToTexture;

  /* For loop below should have a basic index for identifying what animation frames are:
    0 : Stand still with weapon
    1 -13 : Walk/Run Animation with weapon
    14 : jump
    15 - 20 : Attack animation
    21 : Stand still without Weapon
    22 - 34 : Walk/Run Animation wihout weapon
  */
  for(int i = 0; i <= 34; i++)
  {
    pathToTexture = "../resources/images/BucketsMovement_" + std::to_string(i) + ".png";
    //std::cout << pathToTexture << std::endl;
    m_Player1.AddAnimTexture(pathToTexture);
  }

  m_Player1.HandleAnimTexture();
  m_playerStartPositionX = ((float)m_window.GetSize().x / 2) - (m_Player1.GetSize().x / 2);
  m_playerStartPositionY = ((float)m_window.GetSize().y / 2) - (m_Player1.GetSize().y / 2);

  m_Player1.SetPosition(m_playerStartPositionX, m_playerStartPositionY);

  m_PlayerWeapon.SetTexture("../resources/images/Honey.png");

  m_gameCamera.setSize({ (float)m_window.GetSize().x, (float)m_window.GetSize().y });
  m_LevelManager.SetWindowSize(m_window.GetSize());
}
Game::~Game() { m_window.Close(); }

Window* Game::GetWindow() { return &m_window; }

void Game::Update()
{
  m_ElapsedTime = m_GameClock.restart();
  m_window.Update();
  m_state = m_window.GetState();

  if(m_state == GameState::Title)
  {
    m_menu.SetPosition(m_window.GetSize().x, m_window.GetSize().y);
    if(m_window.GetMenuDirection() == "Up")
    {
      m_menuIndex--;
      if(m_menuIndex < 0)
      {
        m_menuIndex = 0;
      }
      else
      {
        m_menu.Navigate(m_titleSelectBuffer, m_menuIndex);
      }

      m_window.ClearMenuDirection();
    }
    else if(m_window.GetMenuDirection() == "Down")
    {
        m_menuIndex++;
        int buffSize = m_titleSelectBuffer.size()-1;
        if(m_menuIndex > buffSize)
        {
          m_menuIndex = buffSize;
        }
        else
        {
          m_menu.Navigate(m_titleSelectBuffer, m_menuIndex);
        }

        m_window.ClearMenuDirection();
    }
    else if(m_window.MenuItemSelected())
    {
      m_menu.ProcessSelection(m_window, m_titleSelectBuffer);
    }
  }
  else if(m_state == GameState::Options)
  {
    m_optionsMenu.SetPosition(m_window.GetSize().x, m_window.GetSize().y);
    if(m_window.GetMenuDirection() == "Up")
    {
      m_optionsMenuIndex--;
      if(m_optionsMenuIndex < 0)
      {
        m_optionsMenuIndex = 0;
      }
      else
      {
        m_optionsMenu.Navigate(m_optionsSelectBuffer, m_optionsMenuIndex);
      }

      m_window.ClearMenuDirection();
    }
    else if(m_window.GetMenuDirection() == "Down")
    {
        m_optionsMenuIndex++;
        int buffSize = m_optionsSelectBuffer.size()-1;
        if(m_optionsMenuIndex > buffSize)
        {
          m_optionsMenuIndex = buffSize;
        }
        else
        {
          m_optionsMenu.Navigate(m_optionsSelectBuffer, m_optionsMenuIndex);
        }

        m_window.ClearMenuDirection();
    }
    else if(m_window.MenuItemSelected())
    {
      m_optionsMenu.ProcessSelection(m_window, m_optionsSelectBuffer);
    }
  }
  if(m_state == GameState::GamePlay)
  {
    // if(m_Player1.GetPosition().x < m_playerStartPositionX)
    // {
    //   m_gameCamera.setCenter(m_playerStartPositionX + (m_Player1.GetSize().x / 2), m_playerStartPositionY + (m_Player1.GetSize().y / 2));
    //   m_LevelManager.SetBackgroundCenter( { m_playerStartPositionX + (m_Player1.GetSize().x / 2), m_playerStartPositionY + (m_Player1.GetSize().y / 2) } );
    // }
    // else
    // {
    //   m_gameCamera.setCenter(m_Player1.GetPosition().x + (m_Player1.GetSize().x / 2), m_window.GetSize().y / 2);
    //   //Why add 480 to x center in the line below?  It offsets the backround image, but I don't really know why 480 is the magic number?  I came to it by trial and error
    //   //and I'm probably going to kick myself for tnot understanding this later.
    //   m_LevelManager.SetBackgroundCenter( { (m_Player1.GetPosition().x + (m_Player1.GetSize().x / 2)) / 2.0f + 480, (m_window.GetSize().y / 2.0f)} );
    // }

    // m_window.SetView(m_gameCamera);

    if(m_LevelManager.CheckLevelChange())
    {
      m_LevelManager.BuildLevel();
      m_LevelManager.SetLevelChange(false);
    }


    //Now that all movements are accounted for, check for collisions
    std::vector<Platform> VisiblePlats = m_LevelManager.GetVisiblePlatforms();
    std::vector<Fruit> VisibleFruit = m_LevelManager.GetVisibleFruit();
    float fTimeElapsed = m_ElapsedTime.asSeconds() * 60; //multiplying by max framerate (set in Window class) to keep player from moving slowly
    m_CollisionHandler.OnUserUpdate(m_window, VisiblePlats, m_Player1, m_PlayerWeapon, VisibleFruit, fTimeElapsed);
    for(int i = 0; i < VisibleFruit.size(); ++i)
    {
      //std::cout << "VisibleFruit Size: " << VisibleFruit.size() << std::endl;
      if(!VisibleFruit[i].GetCollectable())
      {
        // std::cout << "Fruit X Position is: " << VisibleFruit[i].GetPosition().x << std::endl;
        // std::cout << "Fruit Y Position is: " << VisibleFruit[i].GetPosition().y << "\n" << std::endl;
        m_LevelManager.HandleCollectedFruit(VisibleFruit[i].GetPosition());
        m_Player1.ScoreIncrement(50);
      }
    }

    if(m_Player1.GetPosition().x < m_playerStartPositionX)
    {
      m_gameCamera.setCenter(m_playerStartPositionX + (m_Player1.GetSize().x / 2), m_playerStartPositionY + (m_Player1.GetSize().y / 2));
      m_LevelManager.SetBackgroundCenter( { m_playerStartPositionX + (m_Player1.GetSize().x / 2), m_playerStartPositionY + (m_Player1.GetSize().y / 2) } );
    }
    else
    {
      m_gameCamera.setCenter(m_Player1.GetPosition().x + (m_Player1.GetSize().x / 2), m_window.GetSize().y / 2);
      //Why add 480 to x center in the line below?  It offsets the backround image, but I don't really know why 480 is the magic number?  I came to it by trial and error
      //and I'm probably going to kick myself for tnot understanding this later.
      m_LevelManager.SetBackgroundCenter( { (m_Player1.GetPosition().x + (m_Player1.GetSize().x / 2)) / 2.0f + 480, (m_window.GetSize().y / 2.0f)} );
    }
    /*A static display bar with score and stuff can be put here.  When you do, make sure to create a Window function fot GetDefaultView as outlined in SFML documentation:
    https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderTarget.php#ad3b533c3f899d7044d981ed607aef9be
    Then it's a matter of running m_window.setView(m_window.GetDefaultView()) as explained in this video: https://youtu.be/SAXmkvICHbI?t=600
    It's necessary to draw the bar outside of the Gameview because we don't want it to move, hence setting back to default view.  I'll likely make the info/score bar its
    own class, so remember that.*/

  }
}



void Game::Render()
{
  // sf::Font font;
  // font.loadFromFile("../resources/fonts/Ubuntu-Medium.ttf");

  //Text object commented out below, but used to test debuging messages by uncommenting
  //sf::Text text("Initial Test", font);
  // text.setCharacterSize(30);
  // text.setStyle(sf::Text::Bold);
  // text.setFillColor(sf::Color::Red);
  m_window.BeginDraw();
  if(m_state == GameState::Title)
  {
    m_titleScreen.Draw(m_window);
    m_menu.Draw(m_window);
  }
  else if(m_state == GameState::GamePlay)
  {
    m_window.SetView(m_gameCamera);
    m_LevelManager.DrawLevel(m_window, m_gameCamera);
    m_Player1.Draw(m_window);
    //std::cout << "Get Weapon Engaged is: " << m_Player1.GetWeaponEngaged() << std::endl;
    if(m_Player1.GetWeaponEngaged())
    {
      m_PlayerWeapon.Draw(m_window);
    }
    //m_window.SetView(m_window.GetDefaultView());
    m_DisplayBar.GetPlayerInfo(m_Player1);
    m_DisplayBar.Draw(m_window);
    //text.setString(m_CollisionHandler.DebugMessage());
    //m_window.Draw(text);
  }
  else if(m_state == GameState::Options)
  {
    m_optionScreen.Draw(m_window);
    m_optionsMenu.Draw(m_window);
  }
  m_window.EndDraw();
}
