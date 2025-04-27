#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

#include "Game.h"

void loadLevel(int current_level, std::vector<Blocks>& blocks, int& n,
               sf::Texture& blockTexture1, sf::Texture& blockTexture2,
               sf::Texture& blockTexture3, sf::Texture& blockTexture4,
               sf::Texture& blockTexture5);

void level1(std::vector<Blocks>& blocks, int& n, sf::Texture& blockTexture1,
            sf::Texture& blockTexture2, sf::Texture& blockTexture3,
            sf::Texture& blockTexture4, sf::Texture& blockTexture5);

void level2(std::vector<Blocks>& blocks, int& n, sf::Texture& blockTexture1,
            sf::Texture& blockTexture2, sf::Texture& blockTexture3,
            sf::Texture& blockTexture4, sf::Texture& blockTexture5);

void level3(std::vector<Blocks>& blocks, int& n, sf::Texture& blockTexture1,
            sf::Texture& blockTexture2, sf::Texture& blockTexture3,
            sf::Texture& blockTexture4, sf::Texture& blockTexture5);
