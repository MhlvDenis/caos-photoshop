# caos-photoshop

Небольшой проект по обработке изображений с помощью фильтров и обрезки. В качестве средств обработки изображений доступны как простейшие эффекты, так и более сложные фильтры. Код проекта написан на языке C, использована библиотека OpenGL (GLUT).

## Установка и сборка
Под системой Linux достаточно установить пакеты `mesa-utils` и `freeglut3-dev` из консоли:
- `sudo apt-get install mesa-utils`
- `sudo apt-get install freeglut3-dev`

После этого необходимо скомпилировать проект с помощью `cmake`, используя файл `CMakeLists.txt`, или собрать и запустить проект в `CLion`.

Под системой Windows потребуется `MinGW`. В консоли `MSYS2` необходимо исполнить следующие команды:
- `pacman -S mingw-w64-x86_64-freeglut`
- `pacman -S mingw-w64-x86_64-glew`

После этого действия аналогичны сборке на Linux.

## Подробное описание функциональности

В настоящий момент проект находится в состоянии разработки. Уже реализованные части проекта помечены `✅`, а функциональности, находящиеся на стадии разработки, помечены `❌`.

### Предоставляемые возможности
✅ Десктопное приложение, интерфейс из простых меню, взаимодействие с ним с помощью мыши и клавиатуры.

✅ Последовательное применение эффектов и фильтров к изображению.

✅ Сохранение промежуточных результатов в выходной файл.

❌ Возможность откатить применение фильтров на один и более шагов назад.

❌ Возможность обрезать изображение

### Поддерживаемые форматы изображений
✅ Основной формат изображений G24

❌ Дополнительный формат jpg

❌ Дополнительный формат png

### Доступные фильтры и эффекты
✅ Негатив

✅ Контрастность

✅ Яркость

✅ Упрощённые γ-фильтры

❌ Блюр

❌ High Pass

❌ Embossed 

❌ Фильтр Робертса

❌ Фильтр Собеля

❌ Медианный фильтр

❌ Фильтр Кувахара

## Использованные материалы:
- https://www.opengl.org/
- https://www.opengl.org/resources/libraries/glut/
- https://www.khronos.org/opengl/wiki/Getting_Started#Downloading_OpenGL
