#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
/**
 * струдкура организма
 * координати х у
 * скорость
 * маса
 * живой или нет
 * направление движения дх ду
 */
struct organism {
    float x;
    float y;
    int speed;
    int masa;
    bool alive;
    float dx;
    float dy;
};

struct eat {
    float x;
    float y;
    int value;
    bool alive;
};

Camera2D camera;

int main(void)
{

    srand(time(NULL));

    float dt;
    float L;

    float vectx;
    float vecty;

    struct organism org1 = {400, 400, 50, 10, true, 1, 1 };

    // Создаём окно размером 1000 на 700 пикселей
    InitWindow(1000, 700, "2D Evolution Simulator");

    // Ограничиваем частоту обновления до 60 кадров в секунду
    SetTargetFPS(60);
    struct eat food1 = {600, 300, 10, false,};
    // Главный цикл программы
    while (!WindowShouldClose())
    {
        dt = GetFrameTime();
        //спавн еди
        if (food1.alive == false) {
            food1.alive = true;
            food1.x = rand() % (900 - 100) + 100;
            food1.y = rand() % (600 - 100) + 100;
        }

        //направление к еде
        vectx = food1.x - org1.x;
        vecty = food1.y - org1.y;

        L = sqrtf(vectx * vectx + vecty * vecty);

        if (L > 0) {
            org1.dx = vectx / L;
            org1.dy = vecty / L;
        }

        float deltaX = org1.dx * org1.speed * dt;
        float deltaY = org1.dy * org1.speed * dt;

        //двигаемся к еде
        org1.x += deltaX;
        org1.y += deltaY;

        //кушанье еди
        if (fabsf(vectx) <= (org1.masa + food1.value) && fabsf(vecty) <= (org1.masa + food1.value) )
        {
            food1.alive = false;
        }

        // Начинаем отрисовку кадра
        BeginDrawing();

        // Очищаем экран тёмным цветом
        ClearBackground((Color){20, 24, 35, 255});

        // Рисуем организм: центр X, центр Y, радиус, цвет
        DrawCircle(org1.x, org1.y ,org1.masa , GREEN);


        //рисуем еду
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
