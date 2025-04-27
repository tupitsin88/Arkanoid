#define _CRT_SECURE_NO_WARNINGS ;
#include "Game.h"

#include "Levels.h"

#define width_ball 18
#define height_ball 18

void gameMenu(sf::RenderWindow& window) {
  window.setFramerateLimit(60);
  // ��������
  sf::Texture menuTexture1, nameTexture, menuBackground;  // �������:
  menuTexture1.loadFromFile("images/button_menu.png");    // ������
  nameTexture.loadFromFile("images/arkanoid.png");        // ��������
  menuBackground.loadFromFile("images/background.png");   // ����

  sf::Font font;
  font.loadFromFile("fonts/Arkanoid.ttf");  // ������

  sf::Text start("START", font), exit("EXIT", font);  // �������� ��������
  // ������ ��������
  start.setCharacterSize(45);  // START
  exit.setCharacterSize(45);   // EXIT
  // ���������� ��������
  start.setPosition(441, 457);  // START
  exit.setPosition(456, 560);   // EXIT

  sf::Sprite menu1(menuTexture1), menu2(menuTexture1),
      name(nameTexture),  // �������� �������� �������
      menuBg(menuBackground);
  // ���������� ��������
  menu1.setPosition(421, 450);  // ��� START
  menu2.setPosition(421, 552);  // ��� EXIR
  name.setPosition(162, 150);   // �������
  menuBg.setPosition(0, 0);     // ���

  bool isMenu = 1;
  int menuNum = 0;  // ������� ��� ������
  double time = 0;  // �������

  while (window.isOpen()) {  // ���� ���� �������
    // ������� �������� ����� ����
    start.setFillColor(sf::Color::White);
    exit.setFillColor(sf::Color::White);
    menuNum = 0;  // ������� ����� ������� ������

    sf::Event event;
    while (window.pollEvent(event)) {  // �������� �������� ����
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Color color(
        sin(time) * 127 + 128,
        sin(time + 2) * 127 + 128,  // ������� ����� ����� �� �������
        sin(time + 4) * 127 + 128);

    if (sf::IntRect(421, 450, 182, 68)  // ���� ���� �������� �� ������ �����
            .contains(sf::Mouse::getPosition(window))) {
      start.setFillColor(color);  // �� ������� ���� �������
      menuNum = 1;                // ����� ���� ������� �� 1
    }

    if (sf::IntRect(421, 552, 182, 68)  // ���� ���� �������� �� ������ �����
            .contains(sf::Mouse::getPosition(window))) {
      exit.setFillColor(color);  // �� ������� ���� �������
      menuNum = 2;               // ����� ���� ������� �� 2
    }

    if (sf::Mouse::isButtonPressed(
            sf::Mouse::Left)) {  // ���� ����� ������ ���� ������, ��
      switch (menuNum) {
        case 1:              // ��� ���� � ������� 1
          gamePlay(window);  // �������� ����
          break;
        case 2:            // ��� ���� � ������� 2
          window.close();  // ������� ����
          break;
      }
    }

    time += 0.05;  // ������� ������������� ��������� ����� ��������

    window.clear();  // ������� �����
    // ��������:
    window.draw(menuBg);  // ���
    window.draw(name);    // �������
    window.draw(menu1);   // ������ 1
    window.draw(start);   // ������� START
    window.draw(menu2);   // ������ 2
    window.draw(exit);    // ������� EXIT

    window.display();  // ������� �� ������
  }
}

void gamePlay(sf::RenderWindow& play) {
  srand(time(NULL));

  play.clear();                // ������� �����
  play.setFramerateLimit(60);  // ��������� ������� ������ � 60
  // �������� ������
  sf::Font font, font1;
  font.loadFromFile("fonts/Arkanoid.ttf");
  font1.loadFromFile("fonts/TimesNewRomanRegular.ttf");
  // �������� ������� SCORE
  sf::Text score("SCORE", font1);
  // ������� ��������� �������
  score.setCharacterSize(35);  // ������ ��������
  score.setPosition(10, 0);    // �������
  // �������� ������ ������� ��� ������ �����
  sf::Text text("", font1, 35);
  // �������� �������
  text.setPosition(150, 0);
  // �������� ������� ������
  sf::Texture blockTexture1, blockTexture2, blockTexture3, blockTexture4,
      blockTexture5;
  blockTexture1.loadFromFile("images/block01.png");  // ������
  blockTexture2.loadFromFile("images/block02.png");  // �������
  blockTexture3.loadFromFile("images/block03.png");  // �������
  blockTexture4.loadFromFile("images/block04.png");  // �����
  blockTexture5.loadFromFile("images/block05.png");  // �����
  // �������� �������
  sf::Texture backgroundTexture, ballTexture, paddleTexture, lifeTexture;
  backgroundTexture.loadFromFile("images/background2.png");  // ����
  ballTexture.loadFromFile("images/ball1.png");              // ������
  paddleTexture.loadFromFile("images/paddle.png");           // �������
  lifeTexture.loadFromFile("images/life.png");               // �����
  // �������� ������� � ���������
  sf::Sprite sBackground(backgroundTexture), sBall(ballTexture),
      sPaddle(paddleTexture), life1(lifeTexture), life2(lifeTexture),
      life3(lifeTexture);
  // �������� ����������
  life1.setPosition(832, 704);  // ������
  life2.setPosition(896, 704);
  life3.setPosition(960, 704);

  sBackground.setPosition(0, 0);  // ����
  // ������� ����������, ������� ����� ��� ����
  int n = 0;  // ���������� ������, ������� ����� ����������

  std::vector<Blocks> arr(100000);  // ������ ������

  double dx = -6;  // �������� �� ��� �
  double dy = -5;  // �������� �� ��� Y

  int Score = 0;  // ����

  double time = 0;  // �������

  double x_ball = 475, y_ball = 720;      // ���������� ������
  double x_paddle = 422, y_paddle = 738;  // ���������� �������

  bool ballLaunched = false;  // ���� ��� ������� ������

  int lifes = 3;  // �����

  int current_level = 1;  // ������� �������
  int destroyed_blocks = 0;  // ���������� ������������ ������
  // �������� ������ 1
  level1(arr, n, blockTexture1, blockTexture2, blockTexture3, blockTexture4,
         blockTexture5);

  while (play.isOpen()) {  // ���� ���� �������
    sf::Event event;
    while (play.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        play.close();

      else if (event.type == sf::Event::KeyPressed) {  // ���� ������ �������
        if (event.key.code == sf::Keyboard::Escape) {  // Esc, ��
          if (gameExit(play))  // ���� ������ YES, ��
            gameMenu(play);    // ��������� ����
        }
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {  // ���� ����� ������
      ballLaunched = true;  // �� ��������� ���
    }

    if (!ballLaunched) {  // ���� ��� �� �������, ��
      if (sf::Keyboard::isKeyPressed(
              sf::Keyboard::Right) ||  // ���� ������ �������
          sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {  // D
        x_paddle += 15;  // ����������� ���������� ������� �� �
        x_ball += 15;  // ����������� ���������� ������ �� �
      }
      if (sf::Keyboard::isKeyPressed(
              sf::Keyboard::Left) ||  // ���� ������ �������
          sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {  // A
        x_paddle -= 15;  // ��������� ���������� ������ �� �
        x_ball -= 15;  // ��������� ���������� ������ �� �
      }
      // ��������� ����� ������ �� ������� ����
      if (x_ball <= 53) x_ball = 53;    // ����� �������
      if (x_ball >= 947) x_ball = 947;  // ������ �������

    } else {
      // x_paddle = x_ball - 65 + 9; // CHEAT

      x_ball += dx;  // ������ ���������� ������ �� �
      // ������ ���������� �� ���� ������
      for (int i = 0; i < n; i++)  // ���������
        if (sf::FloatRect(x_ball, y_ball, width_ball / 2,
                          height_ball / 2)  // ����� �� ��� � i-�� ����
                .intersects(arr[i].block.getGlobalBounds())) {  // ���� ��, ��
          dx = -dx;  // ������ �������� �� ��� � �� ���������������
          Score += arr[i].life;  // ����������� ���� �� ���������� ����� �����
          arr[i].block.setPosition(-100,
                                   0);  // ������������ ���� �� ��������� ����
          destroyed_blocks++;  // ����������� ������� ������������ ������
          break;  // ������� �� �����
        }

      y_ball += dy;  // ������ ���������� ������ �� �
      for (int i = 0; i < n; i++)  // ���������
        if (sf::FloatRect(x_ball, y_ball, width_ball / 2,
                          height_ball / 2)  // ����� �� ��� � i-�� ����
                .intersects(arr[i].block.getGlobalBounds())) {  // ���� ��, ��
          dy = -dy;  // ������ �������� �� ��� Y �� ���������������
          Score += arr[i].life;  // ����������� ���� �� ���������� ����� �����
          arr[i].block.setPosition(-100,
                                   0);  // ������������ ���� �� ��������� ����
          destroyed_blocks++;  // ����������� ������� ������������ ������
          break;  // ������� �� �����
        }

      if (sf::FloatRect(x_ball, y_ball, width_ball, height_ball)  // ���������
              .intersects(
                  sPaddle.getGlobalBounds()))  // ����� �� ����� � �������
        dy = -(rand() % 5 + 4);  // ������ ��������� �������� �� ��� Y

      if (sf::Keyboard::isKeyPressed(
              sf::Keyboard::Right) ||  // ���� ������ ������� ������ -> ���
          sf::Keyboard::isKeyPressed(sf::Keyboard::D))  // ������� D, ��
        x_paddle += 15;  // ����������� ���������� ������� �� ��� X
      if (sf::Keyboard::isKeyPressed(
              sf::Keyboard::Left) ||  // ���� ������ ������� ����� <- ���
          sf::Keyboard::isKeyPressed(sf::Keyboard::A))  // ������� �, ��
        x_paddle -= 15;  // ��������� ���������� ������� �� ��� X

      // �������� �� ������ ������ �� ����
      if (x_ball <= 0 || x_ball >= 1000) dx = -dx;  // ����� � ������
      if (y_ball <= 0) dy = -dy;                    // �������

      if (destroyed_blocks == n) {  // ���� ���������� ������������ ������ �����
                                    // ���������� ������ � ������, ��
        if (current_level == 3) {  // ���� ������� ������� 3, ��
          if (gameWon(play, sBackground, life1, life2, life3, arr,
                      sPaddle,  // ���� ����� �������, ��
                      n)) {
            gameMenu(play);     // ��������� ����
          } else {              // ����� �������� ������
            current_level = 1;  // ������� ������� 1
            destroyed_blocks = 0;  // ���������� ������������ ������ 0
            // ������� ������
            life1.setPosition(832, 704);
            life2.setPosition(896, 704);
            life3.setPosition(960, 704);

            Score = 0;                   // ���� 0
            lifes = 3;                   // ���������� ������ 3
            x_ball = 475, y_ball = 720;  // ��������� ���������� ������
            x_paddle = 422, y_paddle = 738;  // ��������� ���������� �������
            ballLaunched = false;  // ���� false, ��� ��� ��� �� �������
            loadLevel(current_level, arr, n, blockTexture1,
                      blockTexture2,  // �������� ������
                      blockTexture3, blockTexture4, blockTexture5);
          }
        } else {  // ����� ���� ������� ����
          if (levelWon(play, sBackground, life1, life2, life3, arr,
                       sPaddle,  // �� ������� ������� � ����������
                       n)) {
            current_level++;  // ������� ������� ����������� �� 1
            destroyed_blocks = 0;  // ���������� ������������ ������ 0
            loadLevel(current_level, arr, n, blockTexture1,
                      blockTexture2,  // �������� ���������� ������
                      blockTexture3, blockTexture4, blockTexture5);
            ballLaunched = false;  // ���� false, ��� ��� ��� �� �������
            // ��������� ���������� ������
            x_ball = 475;
            y_ball = 716;
            // ��������� ���������� �������
            x_paddle = 422;
            y_paddle = 738;

          } else {           // ����� ������� � ����
            gameMenu(play);  //
          }
        }
      }
      // �������� �� ������ ������
      if (y_ball > 756) {  // ���� ��� ���� ����,��
        --lifes;  // ��������� ���������� ������ �� 1
        Score -= 30;       // ��������� ���� �� 30 �����
        if (lifes == 2) {  // ���� �������� ������ 2, ��
          life1.setPosition(-111, 0);  // ������������ ������������ �� �������
          ballLaunched = false;  // ���� false, ��� ��� ��� �� �������
          // ��������� ���������� ������
          x_ball = 475;
          y_ball = 716;
          // ��������� ���������� �������
          x_paddle = 422;
          y_paddle = 738;
        }

        if (lifes == 1) {  // ���� �������� ������ 1, ��
          life2.setPosition(-111, 0);  // ������������ ������������ �� �������
          ballLaunched = false;  // ���� false, ��� ��� ��� �� �������
          // ��������� ���������� ������
          x_ball = 475;
          y_ball = 716;
          // ��������� ���������� �������
          x_paddle = 422;
          y_paddle = 738;
        }

        if (lifes == 0) {  // ���� �������� ������ 1, ��
          life3.setPosition(-111, 0);  // ������������ ������������ �� �������
          // ��������� ��������� ��������� ������
          if (levelLose(play, sBackground, life3, arr, sPaddle,
                        n)) {  // ���� ����������, ��
            gamePlay(play);    // ������
          } else {             // �����
            gameMenu(play);    // ����
          }
        }
      }
    }
    // �������� �� ����� ������� �� ������� ������
    if (x_paddle <= 0) x_paddle = 0;
    if (x_paddle >= 894) x_paddle = 894;

    // ���������� ����������
    sBall.setPosition(x_ball, y_ball);        // ������
    sPaddle.setPosition(x_paddle, y_paddle);  // �������

    // ����� ����� �� �����
    std::ostringstream playerScoreString;
    playerScoreString << Score;
    text.setString(playerScoreString.str());

    sf::Color color(sin(time) * 127 + 128,
                    sin(time + 2) * 127 + 128,  // ������ ���� ��������
                    sin(time + 4) * 127 + 128);
    time += 0.05;  // ������� ������������� ��������� ����� ��������
    // ������� ���� ��������
    score.setFillColor(color);
    text.setFillColor(color);

    play.clear();  // ������� �����
    // ��������
    play.draw(sBackground);  // ���
    play.draw(life1);        // ����� 1
    play.draw(life2);        // ����� 2
    play.draw(life3);        // ����� 3
    play.draw(sBall);        // ���
    play.draw(sPaddle);      // �������
    play.draw(score);        // ������� SCORE
    play.draw(text);         // ����

    for (int i = 0; i < n; i++) {  // ��������� ������
      play.draw(arr[i].block);
    }

    play.display();  // ������� �� ������
  }
}

bool levelLose(sf::RenderWindow& play, sf::Sprite sBackground, sf::Sprite life3,
               std::vector<Blocks> block, sf::Sprite sPaddle, int n) {
  play.setFramerateLimit(60);

  sf::Font font;
  font.loadFromFile("fonts/Arkanoid.ttf");  // �������� �����

  sf::Text yes("YES", font), no("NO", font),
      lose("YOU LOSE", font),  // �������� �������
      info("TRY AGAIN?", font);
  // ������� ��:
  yes.setCharacterSize(45);  // ������
  no.setCharacterSize(45);
  lose.setCharacterSize(45);
  info.setCharacterSize(45);

  yes.setPosition(310, 460);  // �������
  no.setPosition(625, 460);
  lose.setPosition(390, 250);
  info.setPosition(345, 310);

  sf::Texture backgroundTexture;  // ������� �������� ����

  backgroundTexture.loadFromFile("images/back_exit.png");  // �������� �

  sf::Sprite sBack(backgroundTexture);  // �������� ������ ����

  sBack.setPosition(256, 200);  // �������� ��� ����������

  sf::VertexArray lines(sf::Lines, 8);  // ������� ������ ����� ������� ����
  // �������� �� ����������
  lines[0].position = sf::Vector2f(256, 201);
  lines[1].position = sf::Vector2f(768, 201);
  lines[2].position = sf::Vector2f(256, 541);
  lines[3].position = sf::Vector2f(768, 541);

  lines[4].position = sf::Vector2f(256, 201);
  lines[5].position = sf::Vector2f(256, 541);

  lines[6].position = sf::Vector2f(768, 201);
  lines[7].position = sf::Vector2f(768, 541);

  int buttonNum = 0;  // ����� ������
  double time = 0;    // �������

  while (play.isOpen()) {  // ���� ���� �������
    // ������� ������� � ����� ����
    yes.setFillColor(sf::Color::White);
    no.setFillColor(sf::Color::White);
    // �������� �� �������� ����
    sf::Event event;
    while (play.pollEvent(event)) {
      if (event.type == sf::Event::Closed) play.close();
    }

    sf::Color color(
        sin(time) * 127 + 128,
        sin(time + 2) * 127 + 128,  // ������� �� ������� ����� �����
        sin(time + 4) * 127 + 128);
    // ������ ���� ������
    lines[0].color = color;
    lines[1].color = color;
    lines[2].color = color;
    lines[3].color = color;
    lines[4].color = color;
    lines[5].color = color;
    lines[6].color = color;
    lines[7].color = color;

    if (sf::IntRect(270, 450, 182, 68)
            .contains(sf::Mouse::getPosition(
                play))) {  // ���� ���� �������� �� ������ ��
      yes.setFillColor(color);  // �� ������� ���� �������
      buttonNum = 1;            // ����� ���� ������� �� 1
    }

    if (sf::IntRect(574, 450, 182, 68)
            .contains(sf::Mouse::getPosition(
                play))) {  // ���� ���� �������� �� ������ ���
      no.setFillColor(color);  // �� ������� ���� �������
      buttonNum = 2;           // ����� ���� ������� �� 2
    }

    if (sf::Mouse::isButtonPressed(
            sf::Mouse::Left)) {  // ���� ����� ������ ���� ������, ��
      switch (buttonNum) {
        case 1:         // ��� ���� � ������� 1
          return true;  // ������ ������
          break;
        case 2:          // ��� ���� � ������� 2
          return false;  // ������ ����
          break;
      }
    }
    // ������� �������� 1 � 2 ����
    info.setFillColor(color);
    lose.setFillColor(color);

    time += 0.05;  // �������� �������

    play.clear();  // ������� �����
    // ��������
    play.draw(sBackground);  // ���

    for (int i = 0; i < n; i++) play.draw(block[i].block);  // �����

    play.draw(life3);    // ����� 3
    play.draw(sBack);    // ��� ����
    play.draw(sPaddle);  // �������
    play.draw(lose);     // ������� 1
    play.draw(info);     // ������� 2
    play.draw(yes);      // ������� 3
    play.draw(no);       // ������� 4
    play.draw(lines);    // ����� �������

    play.display();  // ������� ��  ������
  }
}

bool levelWon(sf::RenderWindow& play, sf::Sprite sBackground, sf::Sprite life1,
              sf::Sprite life2, sf::Sprite life3, std::vector<Blocks> block,
              sf::Sprite sPaddle, int n) {
  play.setFramerateLimit(60);
  // �������� �����
  sf::Font font;
  font.loadFromFile("fonts/Arkanoid.ttf");

  sf::Text back("MENU", font), next("NEXT", font),
      won("YOU WON", font),  // �������� �������
      info("NEXT LEVEL?", font);
  // ������� ��:
  back.setCharacterSize(45);  // ������
  next.setCharacterSize(45);
  won.setCharacterSize(45);
  info.setCharacterSize(45);

  back.setPosition(298, 460);  // �������
  next.setPosition(602, 460);
  won.setPosition(390, 250);
  info.setPosition(345, 310);

  sf::Texture backgroundTexture;  // �������� �������� ���� ����

  backgroundTexture.loadFromFile("images/back_exit.png");  // �������� �

  sf::Sprite sBack(backgroundTexture);  // �������� ������ ���� ����

  sBack.setPosition(256, 200);  // ������� �������

  sf::VertexArray lines(sf::Lines, 8);  // ������� ������ ����� �������
  // ������ ����� �������� ����������
  lines[0].position = sf::Vector2f(256, 201);
  lines[1].position = sf::Vector2f(768, 201);
  lines[2].position = sf::Vector2f(256, 541);
  lines[3].position = sf::Vector2f(768, 541);

  lines[4].position = sf::Vector2f(256, 201);
  lines[5].position = sf::Vector2f(256, 541);

  lines[6].position = sf::Vector2f(768, 201);
  lines[7].position = sf::Vector2f(768, 541);

  int buttonNum = 0;  // ����� ������
  double time = 0;    // �������

  while (play.isOpen()) {  // ���� ���� �������
    // ���������� ������� � ����� ����
    back.setFillColor(sf::Color::White);
    next.setFillColor(sf::Color::White);
    // �������� �� �������� ����
    sf::Event event;
    while (play.pollEvent(event)) {
      if (event.type == sf::Event::Closed) play.close();
    }
    // ��������� ����� ����� �� �������
    sf::Color color(sin(time) * 127 + 128, sin(time + 2) * 127 + 128,
                    sin(time + 4) * 127 + 128);
    // ������� ����� �������
    lines[0].color = color;
    lines[1].color = color;
    lines[2].color = color;
    lines[3].color = color;
    lines[4].color = color;
    lines[5].color = color;
    lines[6].color = color;
    lines[7].color = color;

    if (sf::IntRect(270, 450, 182, 68)
            .contains(sf::Mouse::getPosition(
                play))) {  // ���� ���� �������� �� ������ ��
      back.setFillColor(color);  // �� ������� ���� �������
      buttonNum = 1;             // ����� ���� ������� �� 1
    }

    if (sf::IntRect(574, 450, 182, 68)
            .contains(sf::Mouse::getPosition(
                play))) {  // ���� ���� �������� �� ������ ���
      next.setFillColor(color);  // �� ������� ���� �������
      buttonNum = 2;             // ����� ���� ������� �� 2
    }

    if (sf::Mouse::isButtonPressed(
            sf::Mouse::Left)) {  // ���� ����� ������ ���� ������, ��
      switch (buttonNum) {
        case 1:          // ��� ���� � ������� 1
          return false;  // ������ ����
          break;
        case 2:         // ��� ���� � ������� 2
          return true;  // ������ ������
          break;
      }
    }
    // ��������
    won.setFillColor(color);   // ������� 1
    info.setFillColor(color);  // ������� 2

    time += 0.05;  // �������� ������� ������ �����

    play.clear();  // ������� �����
    // ��������
    play.draw(sBackground);  // ���

    for (int i = 0; i < n; i++) play.draw(block[i].block);  // �����

    play.draw(life1);    // ����� 1
    play.draw(life2);    // ����� 2
    play.draw(life3);    // ����� 3
    play.draw(sBack);    // ��� ����
    play.draw(sPaddle);  // �������
    play.draw(won);      // ������� 1
    play.draw(info);     // ������� 2
    play.draw(back);     // ������� 3
    play.draw(next);     // ������� 4
    play.draw(lines);    // ����� �������

    play.display();  // ������� �� ������
  }
}

bool gameExit(sf::RenderWindow& play) {
  play.setFramerateLimit(60);

  sf::Font font;
  font.loadFromFile("fonts/Arkanoid.ttf");  // �������� �����

  sf::Text yes("YES", font), no("NO", font),
      info("DO YOU WANT", font),  // �������� �������
      info1("TO EXIT?", font);
  // ������� ��:
  yes.setCharacterSize(45);  // ������
  no.setCharacterSize(45);
  info.setCharacterSize(45);
  info1.setCharacterSize(45);

  yes.setPosition(310, 460);  // ����������
  no.setPosition(625, 460);
  info.setPosition(335, 250);
  info1.setPosition(380, 310);

  sf::Texture backgroundTexture;  // ������� �������� ����

  backgroundTexture.loadFromFile("images/back_exit.png");  // �������� �

  sf::Sprite sBack(backgroundTexture);  // �������� ������ ����

  sBack.setPosition(256, 200);  // �������� ��� ����������

  sf::VertexArray lines(sf::Lines, 8);  // ������� ������ ����� ������� ����
  // �������� �� ����������
  lines[0].position = sf::Vector2f(256, 201);
  lines[1].position = sf::Vector2f(768, 201);
  lines[2].position = sf::Vector2f(256, 541);
  lines[3].position = sf::Vector2f(768, 541);

  lines[4].position = sf::Vector2f(256, 201);
  lines[5].position = sf::Vector2f(256, 541);

  lines[6].position = sf::Vector2f(768, 201);
  lines[7].position = sf::Vector2f(768, 541);

  int buttonNum = 0;  // ����� ������
  double time = 0;    // �������

  while (play.isOpen()) {  // ���� ���� �������
    // ������� ������� � ����� ����
    yes.setFillColor(sf::Color::White);
    no.setFillColor(sf::Color::White);
    // �������� �� �������� ����
    sf::Event event;
    while (play.pollEvent(event)) {
      if (event.type == sf::Event::Closed) play.close();
    }

    sf::Color color(
        sin(time) * 127 + 128,
        sin(time + 2) * 127 + 128,  // ������� �� ������� ����� �����
        sin(time + 4) * 127 + 128);

    // ������ ���� ������
    lines[0].color = color;
    lines[1].color = color;
    lines[2].color = color;
    lines[3].color = color;
    lines[4].color = color;
    lines[5].color = color;
    lines[6].color = color;
    lines[7].color = color;

    if (sf::IntRect(270, 450, 182, 68)
            .contains(sf::Mouse::getPosition(
                play))) {  // ���� ���� �������� �� ������ ��
      yes.setFillColor(color);  // �� ������� ���� �������
      buttonNum = 1;            // ����� ���� ������� �� 1
    }

    if (sf::IntRect(574, 450, 182, 68)
            .contains(sf::Mouse::getPosition(
                play))) {  // ���� ���� �������� �� ������ ���
      no.setFillColor(color);  // �� ������� ���� �������
      buttonNum = 2;           // ����� ���� ������� �� 2
    }

    if (sf::Mouse::isButtonPressed(
            sf::Mouse::Left)) {  // ���� ����� ������ ���� ������, ��
      switch (buttonNum) {
        case 1:         // ��� ���� � ������� 1
          return true;  // ������ ������
          break;
        case 2:          // ��� ���� � ������� 2
          return false;  // ����� ����
          break;
      }
    }
    // ������� �������� 1 � 2 ����
    info.setFillColor(color);
    info1.setFillColor(color);

    time += 0.05;  // �������� �������
    // ��������
    play.draw(sBack);  // ���
    play.draw(info);   // ������� 1
    play.draw(info1);  // ������� 2
    play.draw(lines);  // ����� �������
    play.draw(yes);    // ������� YES
    play.draw(no);     // ������� NO

    play.display();  // ������� �� ������
  }
}

bool gameWon(sf::RenderWindow& play, sf::Sprite sBackground, sf::Sprite life1,
             sf::Sprite life2, sf::Sprite life3, std::vector<Blocks> block,
             sf::Sprite sPaddle, int n) {
  play.setFramerateLimit(60);

  sf::Font font;
  font.loadFromFile("fonts/Arkanoid.ttf");  // �������� �����

  sf::Text yes("YES", font), no("NO", font),
      info1("YOU ARE WINNER!", font),  // �������� �������
      info("PLAY AGAIN?", font);
  // ������� ��:
  yes.setCharacterSize(45);  // ������
  no.setCharacterSize(45);
  info1.setCharacterSize(45);
  info.setCharacterSize(45);

  yes.setPosition(310, 460);  // ����������
  no.setPosition(625, 460);
  info1.setPosition(290, 250);
  info.setPosition(350, 310);

  sf::Texture backgroundTexture;  // ������� �������� ����

  backgroundTexture.loadFromFile("images/back_exit.png");  // �������� �

  sf::Sprite sBack(backgroundTexture);  // �������� ������ ����

  sBack.setPosition(256, 200);  // ��������� ��� ����������

  sf::VertexArray lines(sf::Lines, 8);  // ������� ������ ����� ������� ����
                                        // �������� �� ����������
  lines[0].position = sf::Vector2f(256, 201);
  lines[1].position = sf::Vector2f(768, 201);
  lines[2].position = sf::Vector2f(256, 541);
  lines[3].position = sf::Vector2f(768, 541);

  lines[4].position = sf::Vector2f(256, 201);
  lines[5].position = sf::Vector2f(256, 541);

  lines[6].position = sf::Vector2f(768, 201);
  lines[7].position = sf::Vector2f(768, 541);

  int buttonNum = 0;  // ����� ������
  double time = 0;    // �������

  while (play.isOpen()) {
    // ������� ������� � ����� ����
    yes.setFillColor(sf::Color::White);
    no.setFillColor(sf::Color::White);
    // �������� �� �������� ����
    sf::Event event;
    while (play.pollEvent(event)) {
      if (event.type == sf::Event::Closed) play.close();
    }

    sf::Color color(
        sin(time) * 127 + 128,
        sin(time + 2) * 127 + 128,  // ������� �� ������� ����� �����
        sin(time + 4) * 127 + 128);

    // ������ ���� ������
    lines[0].color = color;
    lines[1].color = color;
    lines[2].color = color;
    lines[3].color = color;
    lines[4].color = color;
    lines[5].color = color;
    lines[6].color = color;
    lines[7].color = color;

    if (sf::IntRect(270, 450, 182, 68)
            .contains(sf::Mouse::getPosition(
                play))) {  // ���� ���� �������� �� ������ ��
      yes.setFillColor(color);  // �� ������� ���� �������
      buttonNum = 1;            // ����� ���� ������� �� 1
    }

    if (sf::IntRect(574, 450, 182, 68)
            .contains(sf::Mouse::getPosition(
                play))) {  // ���� ���� �������� �� ������ ���
      no.setFillColor(color);  // �� ������� ���� �������
      buttonNum = 2;           // ����� ���� ������� �� 2
    }

    if (sf::Mouse::isButtonPressed(
            sf::Mouse::Left)) {  // ���� ����� ������ ���� ������, ��
      switch (buttonNum) {
        case 1:          // ��� ���� � ������� 1
          return false;  // ������ ����
          break;
        case 2:         // ��� ���� � ������� 2
          return true;  // ����� ������
          break;
      }
    }
    // ������� �������� 1 � 2 ����
    info.setFillColor(color);
    info1.setFillColor(color);

    time += 0.05;  // �������� �������

    play.clear();  // ������� �����
    // ��������:
    play.draw(sBackground);  // ���

    for (int i = 0; i < n; i++) play.draw(block[i].block);  // �����

    play.draw(life3);    // �����
    play.draw(sBack);    // ��� ����
    play.draw(sPaddle);  // �������
    play.draw(info1);    // ������� 2
    play.draw(info);     // ������� 1
    play.draw(yes);      // YES
    play.draw(no);       // NO
    play.draw(lines);    // ����� �������
    play.display();      // ������� �� ������
  }
}