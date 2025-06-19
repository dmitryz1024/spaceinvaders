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

- Компилятор C++ (например, MinGW-w64 для Windows)
- Уже собранная библиотека PDCurses:
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

    set(CMAKE_CXX_STANDARD 17)

    include_directories(include)
    link_directories(lib)

    file(GLOB SOURCES "src/*.cpp")

    add_executable(spaceinvaders ${SOURCES})
    target_link_libraries(spaceinvaders pdcurses)
    ```

2. Выполните команды в терминале:

    ```sh
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

- Исполняемый файл появится в папке `build` (например, `spaceinvaders.exe`).

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
