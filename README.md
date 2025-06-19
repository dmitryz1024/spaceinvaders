# Space Invaders (C++/PDCurses)

Классическая аркада Space Invaders, реализованная на C++ с использованием библиотеки PDCurses для текстового интерфейса.

## Особенности

- Управление игроком с помощью стрелок (`←`/`→`) или клавиш `A`/`D`
- Стрельба — пробел
- Несколько волн врагов, сложность увеличивается с каждой волной
- Хаотичное движение врагов и их стрельба
- Красочная анимация взрывов
- Поддержка рестарта (`r`) и выхода (`q`) после окончания игры

## Сборка и запуск

### Требования

- Компилятор C++ (при разработке использовался MinGW-w64 для Windows)
- Уже собранная (через MinGW-w64) библиотека PDCurses:
  - `include/curses.h` (и другие заголовки) лежат в папке `include`
  - `lib/libpdcurses.a` лежит в папке `lib`

---

## Вариант 1: Сборка через g++

```sh
g++ -std=c++17 -Iinclude -Llib src/*.cpp -lpdcurses -o spaceinvaders.exe
```

- `-Iinclude` — путь к заголовочным файлам PDCurses
- `-Llib` — путь к собранной библиотеке PDCurses
- `-lpdcurses` — подключение библиотеки
- `src/*.cpp` — все исходники проекта

---

## Вариант 2: Сборка через CMake

1. Убедитесь, что в корне проекта есть файл `CMakeLists.txt` с примерно таким содержимым:

    ```cmake
    cmake_minimum_required(VERSION 3.10)
    project(SpaceInvaders)
    
    set(CMAKE_C_COMPILER gcc)
    set(CMAKE_CXX_COMPILER g++)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    include_directories("./include") 
    link_directories("./lib")
    
    add_executable(SpaceInvaders
        src/main.cpp
        src/Entity.cpp
        src/Player.cpp
        src/Enemy.cpp
        src/Bullet.cpp
        src/Explosion.cpp
        src/Game.cpp
    )
    
    target_link_libraries(SpaceInvaders pdcurses)
    ```

2. Выполните команды в терминале:

    ```sh
    mkdir build
    cmake -S . -B build
    cmake --build build
    ```

- Исполняемый файл появится в папке `build` (`SpaceInvaders.exe`).

---

**Рекомендуется запускать игру в Windows Terminal или cmd.exe, чтобы корректно работали стрелки и скрытие курсора.**

## Управление

- `←` / `→` или `A` / `D` — движение игрока
- `Пробел` — выстрел
- `Q` — выход из игры (на экране окончания)
- `R` — рестарт игры (на экране окончания)

## Структура проекта

- `src/` — исходные коды
- `include/` — заголовочные файлы (включая PDCurses)
- `lib/` — собранная библиотека PDCurses (`libpdcurses.a`)
- `README.md` — этот файл

## Известные проблемы

- Встроенный терминал VS Code и PowerShell могут некорректно обрабатывать стрелки и скрытие курсора. Используйте Windows Terminal или cmd.exe.
- Игра работает только в текстовом режиме.

## Лицензия

MIT License. Используйте и модифицируйте свободно.

---

**Приятной игры!**
