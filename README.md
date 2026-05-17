# GEMS

## Описание проекта

Игра GEMS — реализация механики match-3 на C++ с использованием SFML.

Игровое поле состоит из цветных квадратов.

Игрок может менять местами две соседние клетки.

Если после обмена образуется группа из 3 или более соседних клеток одного цвета, клетки уничтожаются.

После удаления:

- оставшиеся клетки падают вниз
- выполняется повторная проверка поля
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

- 5 случайных клеток поля
- включая клетку с бонусом

---

# Структура проекта

## Game.h / Game.cpp

Главный игровой класс.

Отвечает за:

- создание окна
- игровой цикл
- обработку ввода

## Board.h / Board.cpp

Класс игрового поля.

Содержит:

- клетки
- бонусы
- размеры поля

Реализует:

- swap клеток
- get/set операции
- проверку пустых клеток

## BoardInitializer.h / BoardInitializer.cpp

Начальная генерация поля.

Отвечает за:

- случайную генерацию
- отсутствие стартовых комбинаций

## BoardMatchFinder.h / BoardMatchFinder.cpp

Поиск комбинаций.

Реализует:

- DFS обход
- поиск компонент
- определение групп 3+

## BoardGravity.h / BoardGravity.cpp

Механика падения клеток.

Отвечает за:

- сдвиг клеток вниз
- перенос бонусов
- очистку пустых ячеек

## BoardResolver.h / BoardResolver.cpp

Обработка поля.

Реализует:

- поиск совпадений
- удаление групп
- создание бонусов
- каскады

## Bonus.h

Описание бонусов.

## BonusManager.h / BonusManager.cpp

Логика бонусов.

Реализует:

- создание бонусов
- активацию
- обработку эффектов

## Utils.h / Utils.cpp

Вспомогательные функции.

Содержит:

- random
- проверки границ
- Manhattan distance
- цвета клеток

---

# Используемые технологии

- C++
- SFML 3.1
- STL
- DFS
- random / shuffle

---

# Как запустить проект

## 1. Скачать SFML

Сайт:

https://www.sfml-dev.org/download/sfml/3.0.0/

Версия:

- Visual C++ 17 (2022)
- 64-bit

Распаковать например в:

```txt
C:\SFML
```

---

# Настройка Visual Studio

## Включить C++20

```txt
Project
Properties
C/C++
Language
C++ Language Standard
```

Выбрать:

```txt
ISO C++20 Standard
```

## Include директории

```txt
Project
Properties
C/C++
General
Additional Include Directories
```

Добавить:

```txt
C:\SFML\include
```

## Library директории

```txt
Project
Properties
Linker
General
Additional Library Directories
```

Добавить:

```txt
C:\SFML\lib
```

## Подключение библиотек

```txt
Project
Properties
Linker
Input
Additional Dependencies
```

Для Debug:

```txt
sfml-graphics-d.lib
sfml-window-d.lib
sfml-system-d.lib
```

## DLL файлы

Из:

```txt
C:\SFML\bin
```

скопировать рядом с `.exe`.

Для Debug:

```txt
sfml-graphics-d-3.dll
sfml-window-d-3.dll
sfml-system-d-3.dll
```

---

# Управление

ЛКМ:

1. выбрать клетку
2. выбрать соседнюю клетку

Если swap создаёт группу:

- клетки уничтожаются
- запускается каскад
- могут появляться бонусы