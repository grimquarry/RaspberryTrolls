#include "DisplayBar.h"

DisplayBar::DisplayBar()
{
  m_NesFont.loadFromFile("../resources/fonts/nintendo-nes-font.ttf");
  m_PlayerName.setFont(m_NesFont);
  m_PlayerName.setCharacterSize(30);
  m_PlayerName.setFillColor(sf::Color::White);
  m_PlayerName.setPosition( 25, 25);

  m_PlayerScore.setFont(m_NesFont);
  m_PlayerScore.setCharacterSize(30);
  m_PlayerScore.setFillColor(sf::Color::White);
  m_PlayerScore.setPosition( 500, 25);
}

DisplayBar::~DisplayBar() { }

void DisplayBar::GetPlayerInfo(Player& player)
{
  m_PlayerName.setString(player.GetPlayerName());
  m_PlayerScore.setString("SCORE: " + std::to_string(player.GetScore()));
}

void DisplayBar::Draw(Window& win)
{
  win.SetView(win.GetDefaultView());
  win.Draw(m_PlayerName);
  win.Draw(m_PlayerScore);
}
