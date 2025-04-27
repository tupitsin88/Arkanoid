#include "Game.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(1024, 768), "Arkanoid");
  sf::Image icon;
  icon.loadFromFile("images/icon.png");
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
  gameMenu(window);
}
// 1049 строк кода