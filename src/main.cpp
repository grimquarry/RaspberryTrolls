#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"


int main()
{
  Game game;
  while(!game.GetWindow()->IsDone()){
    std::cout << "______________________________________________________________________________" << std::endl;
    game.Update();
    game.Render();
    std::cout << "______________________________________________________________________________" << std::endl;
  }

  return 0;
}
