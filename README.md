# GEMS

## Описание

GEMS — игра жанра match-3 на C++ с использованием SFML.

Игрок может менять местами две соседние клетки.

Если после обмена образуется группа из 3 или более соседних клеток одного цвета, клетки уничтожаются.

После удаления:

- клетки падают вниз
- поле проверяется повторно
- возможны каскадные реакции

---

# Бонусы

## COLORIZE

Перекрашивает:

- клетку с бонусом
- две случайные НЕсоседние клетки

в радиусе 3 клеток в цвет исходной клетки.

## BOMB

Уничтожает:

- 5 случайных клеток
- включая клетку с бонусом

---

# Структура проекта

## Game.h / Game.cpp

Главный игровой класс.

Отвечает за:

- окно SFML
- игровой цикл
- обработку ввода

## Board.h / Board.cpp

Игровое поле.

Содержит:

- клетки
- бонусы
- размеры поля

Реализует:

- swap клеток
- доступ к клеткам
- проверку поля

## BoardInitializer.h / BoardInitializer.cpp

Начальная генерация поля.

Отвечает за:

- случайное заполнение
- отсутствие стартовых комбинаций

## BoardMatchFinder.h / BoardMatchFinder.cpp

Поиск комбинаций.

Реализует:

- DFS обход
- поиск групп одинаковых клеток

## BoardGravity.h / BoardGravity.cpp

Гравитация.

Отвечает за:

- падение клеток вниз
- перенос бонусов

## BoardResolver.h / BoardResolver.cpp

Обработка поля.

Реализует:

- удаление комбинаций
- создание бонусов
- каскады

## Bonus.h

Описание бонусов.

## BonusManager.h / BonusManager.cpp

Логика бонусов.

Реализует:

- создание бонусов
- активацию эффектов

## Utils.h / Utils.cpp

Вспомогательные функции.

Содержит:

- random
- проверки границ
- distance функции

---

# Используемые технологии

- C++
- SFML 3.0
- STL
- DFS
- random / shuffle

---

# Как запустить

## 1. Скачать SFML

Сайт:

https://www.sfml-dev.org/download/sfml/3.0.0/

Например распаковать в:

C:\SFML


---

# Настройка Visual Studio

## Включить C++20

Project
Properties
C/C++
Language
C++ Language Standard

Выбрать:


ISO C++20 Standard


## Include директории


Project
Properties
C/C++
General
Additional Include Directories


Добавить:

C:\SFML\include


## Library директории


Project
Properties
Linker
General
Additi   onal Library Directories

Добавить:

C:\SFML\lib

## Подключить библиотеки

Project
Properties
Linker
Input
Additional Dependencies


Для Debug:

sfml-graphics-d.lib
sfml-window-d.lib
sfml-system-d.lib

## DLL файлы

Из папки:


C:\SFML\bin

скопировать рядом с `.exe`

Для Debug нужны:


sfml-graphics-d-3.dll
sfml-window-d-3.dll
sfml-system-d-3.dll


---

# Управление

ЛКМ:

1. выбрать клетку
2. выбрать соседнюю клетку

Если создаётся комбинация:

- клетки удаляются
- запускается каскад
- могут появляться бонусы