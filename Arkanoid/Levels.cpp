#pragma warning(disable : 4996)

#include "Levels.h"

void loadLevel(int current_level, std::vector<Blocks>& blocks, int& n,
               sf::Texture& blockTexture1, sf::Texture& blockTexture2,
               sf::Texture& blockTexture3, sf::Texture& blockTexture4,
               sf::Texture& blockTexture5) {
  if (current_level == 1)
    level1(blocks, n, blockTexture1, blockTexture2, blockTexture3,
           blockTexture4, blockTexture5);
  if (current_level == 2)
    level2(blocks, n, blockTexture1, blockTexture2, blockTexture3,
           blockTexture4, blockTexture5);
  if (current_level == 3)
    level3(blocks, n, blockTexture1, blockTexture2, blockTexture3,
           blockTexture4, blockTexture5);
}

void level1(std::vector<Blocks>& blocks, int& n, sf::Texture& blockTexture1,
            sf::Texture& blockTexture2, sf::Texture& blockTexture3,
            sf::Texture& blockTexture4, sf::Texture& blockTexture5) {
  std::ifstream fin("level_1.txt");
  fin >> n;
  int ni = 0;
  int mi = 0;
  fin >> ni >> mi;
  int k = 0;
  for (int i = 1; i <= ni; i++) {
    for (int j = 1; j <= mi; j++) {
      int t = 0;
      fin >> t;
      if (t == 0) {
        continue;
      }
      if (t == 1) {
        blocks[k].block.setPosition(i * 71 + 63 * 3, j * 48 + 30);
        blocks[k].block.setTexture(blockTexture1);
        blocks[k].life = 1;
      }
      if (t == 2) {
        blocks[k].block.setPosition(i * 71 + 63 * 3, j * 48 + 30);
        blocks[k].block.setTexture(blockTexture2);
        blocks[k].life = 2;
      }
      if (t == 3) {
        blocks[k].block.setPosition(i * 71 + 63 * 3, j * 48 + 30);
        blocks[k].block.setTexture(blockTexture3);
        blocks[k].life = 3;
      }
      k++;
    }
  }
  fclose(stdin);
}

void level2(std::vector<Blocks>& blocks, int& n, sf::Texture& blockTexture1,
            sf::Texture& blockTexture2, sf::Texture& blockTexture3,
            sf::Texture& blockTexture4, sf::Texture& blockTexture5) {
  std::ifstream fin("level_2.txt");
  fin >> n;
  int ni = 0;
  int mi = 0;
  fin >> ni >> mi;
  int k = 0;
  for (int i = 1; i <= ni; i++) {
    for (int j = 1; j <= mi; j++) {
      int t = 0;
      fin >> t;
      if (t == 0) {
        continue;
      }
      if (t == 1) {
        blocks[k].block.setPosition(i * 81 + 63 * 3, j * 48 + 30);
        blocks[k].block.setTexture(blockTexture1);
        blocks[k].life = 1;
      }
      if (t == 2) {
        blocks[k].block.setPosition(i * 81 + 63 * 3, j * 48 + 30);
        blocks[k].block.setTexture(blockTexture2);
        blocks[k].life = 2;
      }
      if (t == 3) {
        blocks[k].block.setPosition(i * 81 + 63 * 3, j * 48 + 30);
        blocks[k].block.setTexture(blockTexture3);
        blocks[k].life = 3;
      }
      if (t == 4) {
        blocks[k].block.setPosition(i * 81 + 63 * 3, j * 48 + 30);
        blocks[k].block.setTexture(blockTexture4);
        blocks[k].life = 4;
      }
      if (t == 5) {
        blocks[k].block.setPosition(i * 81 + 63 * 3, j * 48 + 30);
        blocks[k].block.setTexture(blockTexture5);
        blocks[k].life = 5;
      }
      k++;
    }
  }
  fclose(stdin);
}

void level3(std::vector<Blocks>& blocks, int& n, sf::Texture& blockTexture1,
            sf::Texture& blockTexture2, sf::Texture& blockTexture3,
            sf::Texture& blockTexture4, sf::Texture& blockTexture5) {
  std::ifstream fin("level_3.txt");
  fin >> n;
  int ni = 0;
  int mi = 0;
  fin >> ni >> mi;
  int k = 0;
  for (int i = 1; i <= ni; i++) {
    for (int j = 1; j <= mi; j++) {
      int t = 0;
      fin >> t;
      if (t == 0) {
        continue;
      }
      if (t == 1) {
        blocks[k].block.setPosition(i * 81, j * 48 + 30);
        blocks[k].block.setTexture(blockTexture1);
        blocks[k].life = 1;
      }
      if (t == 2) {
        blocks[k].block.setPosition(i * 81, j * 48 + 30);
        blocks[k].block.setTexture(blockTexture2);
        blocks[k].life = 2;
      }
      if (t == 3) {
        blocks[k].block.setPosition(i * 81, j * 48 + 30);
        blocks[k].block.setTexture(blockTexture3);
        blocks[k].life = 3;
      }
      if (t == 4) {
        blocks[k].block.setPosition(i * 81, j * 48 + 30);
        blocks[k].block.setTexture(blockTexture4);
        blocks[k].life = 4;
      }
      if (t == 5) {
        blocks[k].block.setPosition(i * 81, j * 48 + 30);
        blocks[k].block.setTexture(blockTexture5);
        blocks[k].life = 5;
      }
      k++;
    }
  }
  fclose(stdin);
}