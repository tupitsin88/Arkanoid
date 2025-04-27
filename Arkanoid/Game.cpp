#define _CRT_SECURE_NO_WARNINGS ;
#include "Game.h"

#include "Levels.h"

#define width_ball 18
#define height_ball 18

void gameMenu(sf::RenderWindow& window) {
  window.setFramerateLimit(60);
  // загрузка
  sf::Texture menuTexture1, nameTexture, menuBackground;  // текстур:
  menuTexture1.loadFromFile("images/button_menu.png");    // кнопки
  nameTexture.loadFromFile("images/arkanoid.png");        // логотипа
  menuBackground.loadFromFile("images/background.png");   // фона

  sf::Font font;
  font.loadFromFile("fonts/Arkanoid.ttf");  // шрифта

  sf::Text start("START", font), exit("EXIT", font);  // создание надписей
  // размер надписей
  start.setCharacterSize(45);  // START
  exit.setCharacterSize(45);   // EXIT
  // координаты надписей
  start.setPosition(441, 457);  // START
  exit.setPosition(456, 560);   // EXIT

  sf::Sprite menu1(menuTexture1), menu2(menuTexture1),
      name(nameTexture),  // создание спрайтов текстур
      menuBg(menuBackground);
  // координаты спрайтов
  menu1.setPosition(421, 450);  // для START
  menu2.setPosition(421, 552);  // для EXIR
  name.setPosition(162, 150);   // логотип
  menuBg.setPosition(0, 0);     // фон

  bool isMenu = 1;
  int menuNum = 0;  // счётчик для кнопок
  double time = 0;  // счётчик

  while (window.isOpen()) {  // пока окно открыто
    // зададим надписям белый цвет
    start.setFillColor(sf::Color::White);
    exit.setFillColor(sf::Color::White);
    menuNum = 0;  // обнулим номер нажатой кнопки

    sf::Event event;
    while (window.pollEvent(event)) {  // проверка закрытия окна
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Color color(
        sin(time) * 127 + 128,
        sin(time + 2) * 127 + 128,  // считаем номер цвета по формуле
        sin(time + 4) * 127 + 128);

    if (sf::IntRect(421, 450, 182, 68)  // если мышь наведена на кнопку старт
            .contains(sf::Mouse::getPosition(window))) {
      start.setFillColor(color);  // то изменим цвет надписи
      menuNum = 1;                // номер меню изменим на 1
    }

    if (sf::IntRect(421, 552, 182, 68)  // если мышь наведена на кнопку старт
            .contains(sf::Mouse::getPosition(window))) {
      exit.setFillColor(color);  // то изменим цвет надписи
      menuNum = 2;               // номер меню изменим на 2
    }

    if (sf::Mouse::isButtonPressed(
            sf::Mouse::Left)) {  // если левая кнопка мыши нажата, то
      switch (menuNum) {
        case 1:              // для меню с номером 1
          gamePlay(window);  // запустим игру
          break;
        case 2:            // для меню с номером 2
          window.close();  // закроем окно
          break;
      }
    }

    time += 0.05;  // изменим интенсивность изменения цвета надписей

    window.clear();  // очистим экран
    // отрисуем:
    window.draw(menuBg);  // фон
    window.draw(name);    // логотип
    window.draw(menu1);   // кнопку 1
    window.draw(start);   // надпись START
    window.draw(menu2);   // кнопку 2
    window.draw(exit);    // надпись EXIT

    window.display();  // покажем на экране
  }
}

void gamePlay(sf::RenderWindow& play) {
  srand(time(NULL));

  play.clear();                // очистим экран
  play.setFramerateLimit(60);  // ограничим частоту кадров в 60
  // загрузим шрифты
  sf::Font font, font1;
  font.loadFromFile("fonts/Arkanoid.ttf");
  font1.loadFromFile("fonts/TimesNewRomanRegular.ttf");
  // создадим надпись SCORE
  sf::Text score("SCORE", font1);
  // изменим параметры надписи
  score.setCharacterSize(35);  // размер символов
  score.setPosition(10, 0);    // позицию
  // создадим пустую надпись для вывода счёта
  sf::Text text("", font1, 35);
  // сохраним позицию
  text.setPosition(150, 0);
  // загрузим тектуры блоков
  sf::Texture blockTexture1, blockTexture2, blockTexture3, blockTexture4,
      blockTexture5;
  blockTexture1.loadFromFile("images/block01.png");  // зелёный
  blockTexture2.loadFromFile("images/block02.png");  // красный
  blockTexture3.loadFromFile("images/block03.png");  // голубой
  blockTexture4.loadFromFile("images/block04.png");  // серый
  blockTexture5.loadFromFile("images/block05.png");  // синий
  // загрузим тектуры
  sf::Texture backgroundTexture, ballTexture, paddleTexture, lifeTexture;
  backgroundTexture.loadFromFile("images/background2.png");  // фона
  ballTexture.loadFromFile("images/ball1.png");              // шарика
  paddleTexture.loadFromFile("images/paddle.png");           // ракетки
  lifeTexture.loadFromFile("images/life.png");               // жизни
  // создадим спрайты к текстурам
  sf::Sprite sBackground(backgroundTexture), sBall(ballTexture),
      sPaddle(paddleTexture), life1(lifeTexture), life2(lifeTexture),
      life3(lifeTexture);
  // назначим координаты
  life1.setPosition(832, 704);  // жизням
  life2.setPosition(896, 704);
  life3.setPosition(960, 704);

  sBackground.setPosition(0, 0);  // фону
  // зададим переменные, которые нужны для игры
  int n = 0;  // количество блоков, которые нужно уничтожить

  std::vector<Blocks> arr(100000);  // вектор блоков

  double dx = -6;  // смещение по оси Х
  double dy = -5;  // смещение по оси Y

  int Score = 0;  // счёт

  double time = 0;  // счётчик

  double x_ball = 475, y_ball = 720;      // координаты шарика
  double x_paddle = 422, y_paddle = 738;  // координаты ракетки

  bool ballLaunched = false;  // флаг для запуска шарика

  int lifes = 3;  // жизни

  int current_level = 1;  // текущий уровень
  int destroyed_blocks = 0;  // количество уничтоженных блоков
  // загрузка уровня 1
  level1(arr, n, blockTexture1, blockTexture2, blockTexture3, blockTexture4,
         blockTexture5);

  while (play.isOpen()) {  // пока окно открыто
    sf::Event event;
    while (play.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        play.close();

      else if (event.type == sf::Event::KeyPressed) {  // если нажата клавиша
        if (event.key.code == sf::Keyboard::Escape) {  // Esc, то
          if (gameExit(play))  // если нажата YES, то
            gameMenu(play);    // запускаем меню
        }
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {  // если нажат пробел
      ballLaunched = true;  // то запускаем шар
    }

    if (!ballLaunched) {  // если шар не запущен, то
      if (sf::Keyboard::isKeyPressed(
              sf::Keyboard::Right) ||  // если нажата клавиша
          sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {  // D
        x_paddle += 15;  // увеличиваем координаты ракетки по Х
        x_ball += 15;  // увеличиваем координаты шарика по Х
      }
      if (sf::Keyboard::isKeyPressed(
              sf::Keyboard::Left) ||  // если нажата клавиша
          sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {  // A
        x_paddle -= 15;  // уменьшаем координаты шарика по Х
        x_ball -= 15;  // уменьшаем координаты шарика по Х
      }
      // проверяем выход шарика за границы поля
      if (x_ball <= 53) x_ball = 53;    // левая граница
      if (x_ball >= 947) x_ball = 947;  // правая граница

    } else {
      // x_paddle = x_ball - 65 + 9; // CHEAT

      x_ball += dx;  // меняем координаты шарика по Х
      // циклом проходимся по всем блокам
      for (int i = 0; i < n; i++)  // проверяем
        if (sf::FloatRect(x_ball, y_ball, width_ball / 2,
                          height_ball / 2)  // попал ли шар в i-ый блок
                .intersects(arr[i].block.getGlobalBounds())) {  // если да, то
          dx = -dx;  // меняем смещение по оси Х на противоположное
          Score += arr[i].life;  // увеличиваем счёт на количество очков блока
          arr[i].block.setPosition(-100,
                                   0);  // отрисовываем блок за границами поля
          destroyed_blocks++;  // увеличиваем счётчик уничтоженных блоков
          break;  // выходим из цикла
        }

      y_ball += dy;  // меняем координаты шарика по Х
      for (int i = 0; i < n; i++)  // проверяем
        if (sf::FloatRect(x_ball, y_ball, width_ball / 2,
                          height_ball / 2)  // попал ли шар в i-ый блок
                .intersects(arr[i].block.getGlobalBounds())) {  // если да, то
          dy = -dy;  // меняем смещение по оси Y на противоположное
          Score += arr[i].life;  // увеличиваем счёт на количество очков блока
          arr[i].block.setPosition(-100,
                                   0);  // отрисовываем блок за границами поля
          destroyed_blocks++;  // увеличиваем счётчик уничтоженных блоков
          break;  // выходим из цикла
        }

      if (sf::FloatRect(x_ball, y_ball, width_ball, height_ball)  // проверяем
              .intersects(
                  sPaddle.getGlobalBounds()))  // попал ли шарик в ракетку
        dy = -(rand() % 5 + 4);  // задаем рандомное смещение во оси Y

      if (sf::Keyboard::isKeyPressed(
              sf::Keyboard::Right) ||  // если нажата стрелка вправо -> или
          sf::Keyboard::isKeyPressed(sf::Keyboard::D))  // клавиша D, то
        x_paddle += 15;  // увеличиваем координаты ракетки по оси X
      if (sf::Keyboard::isKeyPressed(
              sf::Keyboard::Left) ||  // если нажата стрелка влево <- или
          sf::Keyboard::isKeyPressed(sf::Keyboard::A))  // клавиша А, то
        x_paddle -= 15;  // уменьшаем координаты ракетки по оси X

      // проверка на отскок шарика от стен
      if (x_ball <= 0 || x_ball >= 1000) dx = -dx;  // левая и правая
      if (y_ball <= 0) dy = -dy;                    // верхняя

      if (destroyed_blocks == n) {  // если количество уничтоженных блоков равно
                                    // количеству блоков в уровне, то
        if (current_level == 3) {  // если текущий уровень 3, то
          if (gameWon(play, sBackground, life1, life2, life3, arr,
                      sPaddle,  // если игрок выходит, то
                      n)) {
            gameMenu(play);     // запускаем меню
          } else {              // иначе начинаем заново
            current_level = 1;  // текущий уровень 1
            destroyed_blocks = 0;  // количество уничтоженных блоков 0
            // позиции жизней
            life1.setPosition(832, 704);
            life2.setPosition(896, 704);
            life3.setPosition(960, 704);

            Score = 0;                   // счёт 0
            lifes = 3;                   // количество жизней 3
            x_ball = 475, y_ball = 720;  // начальные координаты шарика
            x_paddle = 422, y_paddle = 738;  // начальные координаты ракетки
            ballLaunched = false;  // флаг false, так как шар не запущен
            loadLevel(current_level, arr, n, blockTexture1,
                      blockTexture2,  // загрузка уровня
                      blockTexture3, blockTexture4, blockTexture5);
          }
        } else {  // иначе если уровенб ниже
          if (levelWon(play, sBackground, life1, life2, life3, arr,
                       sPaddle,  // то уровень пройден и продолжаем
                       n)) {
            current_level++;  // текущий уровень увеличиваем на 1
            destroyed_blocks = 0;  // количество уничтоженных блоков 0
            loadLevel(current_level, arr, n, blockTexture1,
                      blockTexture2,  // загрузка следующего уровня
                      blockTexture3, blockTexture4, blockTexture5);
            ballLaunched = false;  // флаг false, так как шар не запущен
            // начальные координаты шарика
            x_ball = 475;
            y_ball = 716;
            // начальные координаты ракетки
            x_paddle = 422;
            y_paddle = 738;

          } else {           // иначе выходим в меню
            gameMenu(play);  //
          }
        }
      }
      // проверка на потерю шарика
      if (y_ball > 756) {  // если шар упал вниз,то
        --lifes;  // уменьшаем количество жизней на 1
        Score -= 30;       // уменьшаем счёт на 30 очков
        if (lifes == 2) {  // если осталось жизней 2, то
          life1.setPosition(-111, 0);  // уничтоженную отрисовываем за экраном
          ballLaunched = false;  // флаг false, так как шар не запущен
          // начальные координаты шарика
          x_ball = 475;
          y_ball = 716;
          // начальные координаты ракетки
          x_paddle = 422;
          y_paddle = 738;
        }

        if (lifes == 1) {  // если осталось жизней 1, то
          life2.setPosition(-111, 0);  // уничтоженную отрисовываем за экраном
          ballLaunched = false;  // флаг false, так как шар не запущен
          // начальные координаты шарика
          x_ball = 475;
          y_ball = 716;
          // начальные координаты ракетки
          x_paddle = 422;
          y_paddle = 738;
        }

        if (lifes == 0) {  // если осталось жизней 1, то
          life3.setPosition(-111, 0);  // уничтоженную отрисовываем за экраном
          // запускаем процедуру проигрыша уровня
          if (levelLose(play, sBackground, life3, arr, sPaddle,
                        n)) {  // если продолжаем, то
            gamePlay(play);    // заново
          } else {             // иначе
            gameMenu(play);    // меню
          }
        }
      }
    }
    // проверка на выход ракетки за пределы экрана
    if (x_paddle <= 0) x_paddle = 0;
    if (x_paddle >= 894) x_paddle = 894;

    // закрепляем координаты
    sBall.setPosition(x_ball, y_ball);        // шарика
    sPaddle.setPosition(x_paddle, y_paddle);  // ракетки

    // вывод счёта на экран
    std::ostringstream playerScoreString;
    playerScoreString << Score;
    text.setString(playerScoreString.str());

    sf::Color color(sin(time) * 127 + 128,
                    sin(time + 2) * 127 + 128,  // меняем цвет надписей
                    sin(time + 4) * 127 + 128);
    time += 0.05;  // изменим интенсивность изменения цвета надписей
    // зададим цвет надписям
    score.setFillColor(color);
    text.setFillColor(color);

    play.clear();  // очистим экран
    // отрисуем
    play.draw(sBackground);  // фон
    play.draw(life1);        // жизнь 1
    play.draw(life2);        // жизнь 2
    play.draw(life3);        // жизнь 3
    play.draw(sBall);        // шар
    play.draw(sPaddle);      // ракетку
    play.draw(score);        // надпись SCORE
    play.draw(text);         // счёт

    for (int i = 0; i < n; i++) {  // отрисовка блоков
      play.draw(arr[i].block);
    }

    play.display();  // покажем на экране
  }
}

bool levelLose(sf::RenderWindow& play, sf::Sprite sBackground, sf::Sprite life3,
               std::vector<Blocks> block, sf::Sprite sPaddle, int n) {
  play.setFramerateLimit(60);

  sf::Font font;
  font.loadFromFile("fonts/Arkanoid.ttf");  // загрузим шрифт

  sf::Text yes("YES", font), no("NO", font),
      lose("YOU LOSE", font),  // создадим надписи
      info("TRY AGAIN?", font);
  // зададим им:
  yes.setCharacterSize(45);  // размер
  no.setCharacterSize(45);
  lose.setCharacterSize(45);
  info.setCharacterSize(45);

  yes.setPosition(310, 460);  // позицию
  no.setPosition(625, 460);
  lose.setPosition(390, 250);
  info.setPosition(345, 310);

  sf::Texture backgroundTexture;  // заведем текстуру фона

  backgroundTexture.loadFromFile("images/back_exit.png");  // загрузим её

  sf::Sprite sBack(backgroundTexture);  // создадим спрайт фона

  sBack.setPosition(256, 200);  // назначим ему координаты

  sf::VertexArray lines(sf::Lines, 8);  // заведем массив линий контура окна
  // назначим им координаты
  lines[0].position = sf::Vector2f(256, 201);
  lines[1].position = sf::Vector2f(768, 201);
  lines[2].position = sf::Vector2f(256, 541);
  lines[3].position = sf::Vector2f(768, 541);

  lines[4].position = sf::Vector2f(256, 201);
  lines[5].position = sf::Vector2f(256, 541);

  lines[6].position = sf::Vector2f(768, 201);
  lines[7].position = sf::Vector2f(768, 541);

  int buttonNum = 0;  // номер кнопки
  double time = 0;    // счетчик

  while (play.isOpen()) {  // пока окно открыто
    // окрасим надписи в белый цвет
    yes.setFillColor(sf::Color::White);
    no.setFillColor(sf::Color::White);
    // проверка на закрытие окна
    sf::Event event;
    while (play.pollEvent(event)) {
      if (event.type == sf::Event::Closed) play.close();
    }

    sf::Color color(
        sin(time) * 127 + 128,
        sin(time + 2) * 127 + 128,  // считаем по формуле номер цвета
        sin(time + 4) * 127 + 128);
    // задаем цвет линиям
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
                play))) {  // если мышь наведена на кнопку ДА
      yes.setFillColor(color);  // то изменим цвет надписи
      buttonNum = 1;            // номер меню изменим на 1
    }

    if (sf::IntRect(574, 450, 182, 68)
            .contains(sf::Mouse::getPosition(
                play))) {  // если мышь наведена на кнопку НЕТ
      no.setFillColor(color);  // то изменим цвет надписи
      buttonNum = 2;           // номер меню изменим на 2
    }

    if (sf::Mouse::isButtonPressed(
            sf::Mouse::Left)) {  // если левая кнопка мыши нажата, то
      switch (buttonNum) {
        case 1:         // для меню с номером 1
          return true;  // вернем истину
          break;
        case 2:          // для меню с номером 2
          return false;  // вернем ложь
          break;
      }
    }
    // зададим надписям 1 и 2 цвет
    info.setFillColor(color);
    lose.setFillColor(color);

    time += 0.05;  // увеличим счетчик

    play.clear();  // очистим экран
    // отрисуем
    play.draw(sBackground);  // фон

    for (int i = 0; i < n; i++) play.draw(block[i].block);  // блоки

    play.draw(life3);    // жизнь 3
    play.draw(sBack);    // фон окна
    play.draw(sPaddle);  // ракетку
    play.draw(lose);     // надпись 1
    play.draw(info);     // надпись 2
    play.draw(yes);      // надпись 3
    play.draw(no);       // надпись 4
    play.draw(lines);    // линии контура

    play.display();  // покажем на  экране
  }
}

bool levelWon(sf::RenderWindow& play, sf::Sprite sBackground, sf::Sprite life1,
              sf::Sprite life2, sf::Sprite life3, std::vector<Blocks> block,
              sf::Sprite sPaddle, int n) {
  play.setFramerateLimit(60);
  // загрузим шрифт
  sf::Font font;
  font.loadFromFile("fonts/Arkanoid.ttf");

  sf::Text back("MENU", font), next("NEXT", font),
      won("YOU WON", font),  // создадим надписи
      info("NEXT LEVEL?", font);
  // зададим им:
  back.setCharacterSize(45);  // размер
  next.setCharacterSize(45);
  won.setCharacterSize(45);
  info.setCharacterSize(45);

  back.setPosition(298, 460);  // позиции
  next.setPosition(602, 460);
  won.setPosition(390, 250);
  info.setPosition(345, 310);

  sf::Texture backgroundTexture;  // создадим текстуру фона окна

  backgroundTexture.loadFromFile("images/back_exit.png");  // загрузим её

  sf::Sprite sBack(backgroundTexture);  // создадим спрайт фона окна

  sBack.setPosition(256, 200);  // зададим позицию

  sf::VertexArray lines(sf::Lines, 8);  // заведем массив линий контура
  // каждой линии присвоим координаты
  lines[0].position = sf::Vector2f(256, 201);
  lines[1].position = sf::Vector2f(768, 201);
  lines[2].position = sf::Vector2f(256, 541);
  lines[3].position = sf::Vector2f(768, 541);

  lines[4].position = sf::Vector2f(256, 201);
  lines[5].position = sf::Vector2f(256, 541);

  lines[6].position = sf::Vector2f(768, 201);
  lines[7].position = sf::Vector2f(768, 541);

  int buttonNum = 0;  // номер кнопки
  double time = 0;    // счетчик

  while (play.isOpen()) {  // пока окно открыто
    // перекрасим надписи в белый цвет
    back.setFillColor(sf::Color::White);
    next.setFillColor(sf::Color::White);
    // проверка на закрытие окна
    sf::Event event;
    while (play.pollEvent(event)) {
      if (event.type == sf::Event::Closed) play.close();
    }
    // посчитаем номер цвета по формуле
    sf::Color color(sin(time) * 127 + 128, sin(time + 2) * 127 + 128,
                    sin(time + 4) * 127 + 128);
    // окрасим линии контура
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
                play))) {  // если мышь наведена на кнопку ДА
      back.setFillColor(color);  // то изменим цвет надписи
      buttonNum = 1;             // номер меню изменим на 1
    }

    if (sf::IntRect(574, 450, 182, 68)
            .contains(sf::Mouse::getPosition(
                play))) {  // если мышь наведена на кнопку НЕТ
      next.setFillColor(color);  // то изменим цвет надписи
      buttonNum = 2;             // номер меню изменим на 2
    }

    if (sf::Mouse::isButtonPressed(
            sf::Mouse::Left)) {  // если левая кнопка мыши нажата, то
      switch (buttonNum) {
        case 1:          // для меню с номером 1
          return false;  // вернем ложь
          break;
        case 2:         // для меню с номером 2
          return true;  // вернем истину
          break;
      }
    }
    // покрасим
    won.setFillColor(color);   // надпись 1
    info.setFillColor(color);  // надпись 2

    time += 0.05;  // увеличим счетчик номера цвета

    play.clear();  // очистим экран
    // отрисуем
    play.draw(sBackground);  // фон

    for (int i = 0; i < n; i++) play.draw(block[i].block);  // блоки

    play.draw(life1);    // жизнь 1
    play.draw(life2);    // жизнь 2
    play.draw(life3);    // жизнь 3
    play.draw(sBack);    // фон окна
    play.draw(sPaddle);  // ракетку
    play.draw(won);      // надпись 1
    play.draw(info);     // надпись 2
    play.draw(back);     // надпись 3
    play.draw(next);     // надпись 4
    play.draw(lines);    // линии контура

    play.display();  // покажем на экране
  }
}

bool gameExit(sf::RenderWindow& play) {
  play.setFramerateLimit(60);

  sf::Font font;
  font.loadFromFile("fonts/Arkanoid.ttf");  // загрузим шрифт

  sf::Text yes("YES", font), no("NO", font),
      info("DO YOU WANT", font),  // создадим надписи
      info1("TO EXIT?", font);
  // зададим им:
  yes.setCharacterSize(45);  // размер
  no.setCharacterSize(45);
  info.setCharacterSize(45);
  info1.setCharacterSize(45);

  yes.setPosition(310, 460);  // координаты
  no.setPosition(625, 460);
  info.setPosition(335, 250);
  info1.setPosition(380, 310);

  sf::Texture backgroundTexture;  // заведем текстуру фона

  backgroundTexture.loadFromFile("images/back_exit.png");  // загрузим её

  sf::Sprite sBack(backgroundTexture);  // создадим спрайт фона

  sBack.setPosition(256, 200);  // назначим ему координаты

  sf::VertexArray lines(sf::Lines, 8);  // заведем массив линий контура окна
  // назначим им координаты
  lines[0].position = sf::Vector2f(256, 201);
  lines[1].position = sf::Vector2f(768, 201);
  lines[2].position = sf::Vector2f(256, 541);
  lines[3].position = sf::Vector2f(768, 541);

  lines[4].position = sf::Vector2f(256, 201);
  lines[5].position = sf::Vector2f(256, 541);

  lines[6].position = sf::Vector2f(768, 201);
  lines[7].position = sf::Vector2f(768, 541);

  int buttonNum = 0;  // номер кнопки
  double time = 0;    // счётчик

  while (play.isOpen()) {  // пока окно открыто
    // окрасим надписи в белый цвет
    yes.setFillColor(sf::Color::White);
    no.setFillColor(sf::Color::White);
    // проверка на закрытие окна
    sf::Event event;
    while (play.pollEvent(event)) {
      if (event.type == sf::Event::Closed) play.close();
    }

    sf::Color color(
        sin(time) * 127 + 128,
        sin(time + 2) * 127 + 128,  // считаем по формуле номер цвета
        sin(time + 4) * 127 + 128);

    // задаем цвет линиям
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
                play))) {  // если мышь наведена на кнопку ДА
      yes.setFillColor(color);  // то изменим цвет надписи
      buttonNum = 1;            // номер меню изменим на 1
    }

    if (sf::IntRect(574, 450, 182, 68)
            .contains(sf::Mouse::getPosition(
                play))) {  // если мышь наведена на кнопку НЕТ
      no.setFillColor(color);  // то изменим цвет надписи
      buttonNum = 2;           // номер меню изменим на 2
    }

    if (sf::Mouse::isButtonPressed(
            sf::Mouse::Left)) {  // если левая кнопка мыши нажата, то
      switch (buttonNum) {
        case 1:         // для меню с номером 1
          return true;  // вернем истину
          break;
        case 2:          // для меню с номером 2
          return false;  // вернём ложь
          break;
      }
    }
    // зададим надписям 1 и 2 цвет
    info.setFillColor(color);
    info1.setFillColor(color);

    time += 0.05;  // увеличим счетчик
    // отрисуем
    play.draw(sBack);  // фон
    play.draw(info);   // надпись 1
    play.draw(info1);  // надпись 2
    play.draw(lines);  // линии контура
    play.draw(yes);    // надпись YES
    play.draw(no);     // надпись NO

    play.display();  // покажем на экране
  }
}

bool gameWon(sf::RenderWindow& play, sf::Sprite sBackground, sf::Sprite life1,
             sf::Sprite life2, sf::Sprite life3, std::vector<Blocks> block,
             sf::Sprite sPaddle, int n) {
  play.setFramerateLimit(60);

  sf::Font font;
  font.loadFromFile("fonts/Arkanoid.ttf");  // загрузим шрифт

  sf::Text yes("YES", font), no("NO", font),
      info1("YOU ARE WINNER!", font),  // создадим надписи
      info("PLAY AGAIN?", font);
  // зададим им:
  yes.setCharacterSize(45);  // размер
  no.setCharacterSize(45);
  info1.setCharacterSize(45);
  info.setCharacterSize(45);

  yes.setPosition(310, 460);  // координаты
  no.setPosition(625, 460);
  info1.setPosition(290, 250);
  info.setPosition(350, 310);

  sf::Texture backgroundTexture;  // заведем текстуру фона

  backgroundTexture.loadFromFile("images/back_exit.png");  // загрузим её

  sf::Sprite sBack(backgroundTexture);  // создадим спрайт фона

  sBack.setPosition(256, 200);  // назнаичим ему координаты

  sf::VertexArray lines(sf::Lines, 8);  // заведем массив линий контура окна
                                        // назначим им координаты
  lines[0].position = sf::Vector2f(256, 201);
  lines[1].position = sf::Vector2f(768, 201);
  lines[2].position = sf::Vector2f(256, 541);
  lines[3].position = sf::Vector2f(768, 541);

  lines[4].position = sf::Vector2f(256, 201);
  lines[5].position = sf::Vector2f(256, 541);

  lines[6].position = sf::Vector2f(768, 201);
  lines[7].position = sf::Vector2f(768, 541);

  int buttonNum = 0;  // номер кнопки
  double time = 0;    // счётчик

  while (play.isOpen()) {
    // окрасим надписи в белый цвет
    yes.setFillColor(sf::Color::White);
    no.setFillColor(sf::Color::White);
    // проверка на закрытие окна
    sf::Event event;
    while (play.pollEvent(event)) {
      if (event.type == sf::Event::Closed) play.close();
    }

    sf::Color color(
        sin(time) * 127 + 128,
        sin(time + 2) * 127 + 128,  // считаем по формуле номер цвета
        sin(time + 4) * 127 + 128);

    // задаем цвет линиям
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
                play))) {  // если мышь наведена на кнопку ДА
      yes.setFillColor(color);  // то изменим цвет надписи
      buttonNum = 1;            // номер меню изменим на 1
    }

    if (sf::IntRect(574, 450, 182, 68)
            .contains(sf::Mouse::getPosition(
                play))) {  // если мышь наведена на кнопку НЕТ
      no.setFillColor(color);  // то изменим цвет надписи
      buttonNum = 2;           // номер меню изменим на 2
    }

    if (sf::Mouse::isButtonPressed(
            sf::Mouse::Left)) {  // если левая кнопка мыши нажата, то
      switch (buttonNum) {
        case 1:          // для меню с номером 1
          return false;  // вернем ложь
          break;
        case 2:         // для меню с номером 2
          return true;  // вернём истину
          break;
      }
    }
    // зададим надписям 1 и 2 цвет
    info.setFillColor(color);
    info1.setFillColor(color);

    time += 0.05;  // увеличим счетчик

    play.clear();  // очистим экран
    // отрисуем:
    play.draw(sBackground);  // фон

    for (int i = 0; i < n; i++) play.draw(block[i].block);  // блоки

    play.draw(life3);    // жизнь
    play.draw(sBack);    // фон окна
    play.draw(sPaddle);  // ракетку
    play.draw(info1);    // надпись 2
    play.draw(info);     // надпись 1
    play.draw(yes);      // YES
    play.draw(no);       // NO
    play.draw(lines);    // линии контура
    play.display();      // покажем на экране
  }
}