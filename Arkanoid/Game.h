#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <sstream>
#include <vector>

struct Blocks {
  sf::Sprite block;
  int life;
};

void gameMenu(sf::RenderWindow& window);

void gamePlay(sf::RenderWindow& play);

bool levelLose(sf::RenderWindow& play, sf::Sprite sBackground, sf::Sprite life3,
               std::vector<Blocks> block, sf::Sprite sPaddle, int n);

bool levelWon(sf::RenderWindow& play, sf::Sprite sBackground, sf::Sprite life1,
              sf::Sprite life2, sf::Sprite life3, std::vector<Blocks> block,
              sf::Sprite sPaddle, int n);

bool gameExit(sf::RenderWindow& play);

bool gameWon(sf::RenderWindow& play, sf::Sprite sBackground, sf::Sprite life1,
             sf::Sprite life2, sf::Sprite life3, std::vector<Blocks> block,
             sf::Sprite sPaddle, int n);