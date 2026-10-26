#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
/**
 * струдкура организма
 * координати х у
 * скорость
 * маса
 * живой или нет
 * направление движения дх ду
 */
struct organism {
    int x;
    int y;
    int speed;
    int masa;
    bool alive;
    int dx;
    int dy;
};

struct eat {
    int x;
    int y;
    int value;
    bool alive;
};

Camera2D camera;

int main(void)
{
     int vectx;
     int vecty;

    struct eat food1 = {600, 300, 10, true};
    struct organism org1 = {400, 400, 5, 10, true, 1, 1 };

    // Создаём окно размером 1000 на 700 пикселей
    InitWindow(1000, 700, "2D Evolution Simulator");

    // Ограничиваем частоту обновления до 60 кадров в секунду
    SetTargetFPS(60);

    // Главный цикл программы
    while (!WindowShouldClose())
    {
        if ((vectx = food1.x - org1.x) < 0) {
            org1.dx = -1;
        }
        else if ((vectx = food1.x - org1.x) > 0) {
            org1.dx = 1;
        }

        if ((vecty = food1.y - org1.y) < 0) {
            org1.dy = -1;
        }
        else if ((vecty = food1.y - org1.y) > 0) {
            org1.dy = 1;
        }

        org1.x += org1.speed * org1.dx;
        org1.y += org1.speed * org1.dy;

        if (vectx <= (org1.masa + food1.value) && vecty <= (org1.masa + food1.value) )
        {
            food1.alive = false;
        }

        // Начинаем отрисовку кадра
        BeginDrawing();

        // Очищаем экран тёмным цветом
        ClearBackground((Color){20, 24, 35, 255});

        // Рисуем организм: центр X, центр Y, радиус, цвет
        DrawCircle(org1.x, org1.y ,org1.masa , GREEN);

        if (food1.alive == true)
        {
            DrawCircle(food1.x, food1.y, food1.value , RED);
        }

        // Завершаем отрисовку кадра
        EndDrawing();
    }

    // Закрываем окно и освобождаем ресурсы
    CloseWindow();

    return 0;
}
