#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"


int main()
{
  Game game;
  while(!game.GetWindow()->IsDone()){
    game.Update();
    game.Render();
  }

  return 0;
}
