#include "Game.h"

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

  m_Player1.AddAnimTexture("../resources/images/BucketsTile.png");
  m_playerStartPositionX = ((float)m_window.GetSize().x / 2) - (m_Player1.GetPlayerWidth() / 2);
  m_playerStartPositionY = ((float)m_window.GetSize().y / 2) - (m_Player1.GetPlayerHeight() / 2);

  m_Player1.SetPosition(m_playerStartPositionX, m_playerStartPositionY);

  m_gameCamera.setSize({ (float)m_window.GetSize().x, (float)m_window.GetSize().y });
  //m_gameCamera.setCenter(m_Player1.GetPosition().x + (930 + m_Player1.GetPlayerWidth()/ 2), m_Player1.GetPosition().y + (540 - m_Player1.GetPlayerHeight() /2));
  // m_gameCamera.setCenter(930, 482);

  //std::cout << "Camera Center: " << m_gameCamera.getCenter().x << std::endl;
  //testLevel.LoadLevelMap("../maps/level_1_1");
  //m_LevelManager.BuildLevel();
}
Game::~Game() { m_window.Close(); }

Window* Game::GetWindow() { return &m_window; }

void Game::Update()
{
  // std::cout << "Controller X Axis Postion is: " << sf::Joystick::getAxisPosition(0, sf::Joystick::X) << std::endl;
  // std::cout << "Controller Y Axis Positsion is: " << sf::Joystick::getAxisPosition(0, sf::Joystick::Y) << std::endl;

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
  else if(m_state == GameState::GamePlay)
  {
    if(m_Player1.GetPosition().x < m_playerStartPositionX)
    {
      m_gameCamera.setCenter(m_playerStartPositionX + (m_Player1.GetPlayerWidth() / 2), m_playerStartPositionY + (m_Player1.GetPlayerHeight() / 2));
    }
    else
    {
      m_gameCamera.setCenter(m_Player1.GetPosition().x + (m_Player1.GetPlayerWidth() / 2), m_window.GetSize().y / 2);
    }

    m_window.SetView(m_gameCamera);
    float fTimeElapsed = m_ElapsedTime.asSeconds() * 60; //multiplying by max framerate (set in Window class) to keep player from moving slowly

    //Check to see if player is on ground, if not call "gravity" by setting player movement down, move the player, then check for collision
    //Commenting out because m_OnGround flag is set with collision checks, but not sure if new solution has bugs or not.
    // if(!m_Player1.GetOnGround(m_LevelManager.GetVisiblePlatforms()))
    // {
    //   m_Player1.SetPlayerMovement(PlayerMovement::Down);
    //   m_Player1.MovePlayer(fTimeElapsed);
    //   m_Player1.CollisionCheck(m_LevelManager.GetVisiblePlatforms());
    // }
    if(!m_Player1.OnGround())
    {
      m_Player1.SetPlayerMovement(PlayerMovement::Down);
      m_Player1.MovePlayer(fTimeElapsed);
      m_Player1.CollisionCheck(m_LevelManager.GetVisiblePlatforms());
    }

    //Get the user input directive to set player movement
    if(m_window.GetPlayerDirective() == "Right")
    {
      m_Player1.SetPlayerMovement(PlayerMovement::Right);
    }
    else if(m_window.GetPlayerDirective() == "Left")
    {
      m_Player1.SetPlayerMovement(PlayerMovement::Left);
    }
    else if(m_window.GetPlayerDirective() == "Up")
    {
      m_Player1.SetPlayerMovement(PlayerMovement::Up);
    }
    else if(m_window.GetPlayerDirective() == "Down")
    {
      m_Player1.SetPlayerMovement(PlayerMovement::Down);
    }
    else if (m_window.GetPlayerDirective() == "Still")
    {
      m_Player1.SetPlayerMovement(PlayerMovement::Still);
    }
    else
    {
      m_Player1.SetPlayerMovement(PlayerMovement::Still);
    }
    //Move the player with the directive given by user input
    m_Player1.MovePlayer(fTimeElapsed);

    //Get Player action.  Actions should probably be put in a buffer as more than 1 can be executed.
    m_PlayerActions.clear();
    m_Player1.ClearPlayerActions();
    m_PlayerActions = m_window.GetPlayerActions();
    if(!m_PlayerActions.empty())
    {
      //std::cout << "This ran" << std::endl;
      for(int i = 0; i < m_PlayerActions.size(); ++i)
      {
        if(m_PlayerActions[i] == "Jump")
        {
          m_Player1.SetPlayerAction(PlayerAction::Jump);
          m_Player1.Jump(fTimeElapsed);
        }
        else if(m_PlayerActions[i] == "Run")
        {
          m_Player1.SetPlayerAction(PlayerAction::Run);
        }
        else if(m_PlayerActions[i] == "Walk")
        {
          m_Player1.SetPlayerAction(PlayerAction::Walk);
        }
      }
    }
    else
    {
      m_Player1.SetPlayerAction(PlayerAction::None);
    }
    // if(m_window.GetPlayerAction() == "Jump")
    // {
    //   m_Player1.SetPlayerAction(PlayerAction::Jump);
    //   m_Player1.Jump(fTimeElapsed);
    // }
    // else if(m_window.GetPlayerAction() == "None")
    // {
    //   m_Player1.SetPlayerAction(PlayerAction::None);
    // }

    //Now that all movements are accounted for, check for collisions
    m_Player1.CollisionCheck(m_LevelManager.GetVisiblePlatforms());

    if(m_LevelManager.CheckLevelChange())
    {
      m_LevelManager.BuildLevel();
      m_LevelManager.SetLevelChange(false);
    }

    /*A static display bar with score and stuff can be put here.  When you do, make sure to create a Window function fot GetDefaultView as outlined in SFML documentation:
    https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderTarget.php#ad3b533c3f899d7044d981ed607aef9be
    Then it's a matter of running m_window.setView(m_window.GetDefaultView()) as explained in this video: https://youtu.be/SAXmkvICHbI?t=600
    It's necessary to draw the bar outside of the Gameview because we don't want it to move, hence setting back to default view.  I'll likely make the info/score bar its
    own class, so remember that.*/
  }
}



void Game::Render() {
  m_window.BeginDraw();
  if(m_state == GameState::Title)
  {
    m_titleScreen.Draw(m_window);
    m_menu.Draw(m_window);
  }
  else if(m_state == GameState::GamePlay)
  {
    //m_enemy.Draw(m_window);
    m_LevelManager.DrawLevel(m_window, m_gameCamera);
    m_Player1.Draw(m_window);
  }
  else if(m_state == GameState::Options)
  {
    m_optionScreen.Draw(m_window);
    m_optionsMenu.Draw(m_window);
  }
  m_window.EndDraw();
}
