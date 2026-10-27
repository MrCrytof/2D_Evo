#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

#define MAX_FOOD 20
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

    int cout = 10;

    struct eat *food = (struct eat *)malloc(MAX_FOOD * sizeof(struct eat));
    if (food == NULL) {
        printf("Memory allocation failed");
        return 1;
    }

    for (int i = 0; i < MAX_FOOD; i++) {
        food[i].x = rand() % (900 - 100) + 100;
        food[i].y = rand() % (600 - 100) + 100;
        food[i].value = 10;
        food[i].alive = true;
    }

    struct organism *organisms = (struct organism *)malloc(cout * sizeof(struct organism));
    if (organisms == NULL) {
        printf("Error allocating memory for organisms.\n");
        return 1;
    }

    for (int i = 0; i < cout; i++) {
        organisms[i].x = rand() % (900 - 100) + 100;
        organisms[i].y = rand() % (600 - 100) + 100;
        organisms[i].speed = rand() % (200 - 100) + 100;
        organisms[i].masa = rand() % (50 - 30) + 30;
        organisms[i].alive = true;
        organisms[i].dx = 0;
        organisms[i].dy = 0;
    }

    // Создаём окно размером 1000 на 700 пикселей
    InitWindow(1000, 700, "2D Evolution Simulator");

    // Ограничиваем частоту обновления до 60 кадров в секунду
    SetTargetFPS(60);
    // Главный цикл программы
    while (!WindowShouldClose())
    {
        // Начинаем отрисовку кадра
        BeginDrawing();

        // Очищаем экран тёмным цветом
        ClearBackground((Color){20, 24, 35, 255});
        dt = GetFrameTime();
        //спавн еди
        for (int j = 0; j < MAX_FOOD; j++) {
            if (food[j].alive == false) {
                food[j].alive = true;
                food[j].x = rand() % (900 - 100) + 100;
                food[j].y = rand() % (600 - 100) + 100;
            }
            for (int i = 0; i < cout; i++) {

                vectx = food[j].x - organisms[i].x;
                vecty = food[j].y - organisms[i].y;

                L = sqrtf((vectx * vectx) + (vecty * vecty));

                // Перевіряємо, що відстань не дорівнює нулю,
                // щоб уникнути ділення на нуль
                if (L > 0) {
                    organisms[i].dx = vectx / L;
                    organisms[i].dy = vecty / L;
                }

                if (L <= organisms[i].masa + food[j].value)
                {
                    food[j].alive = false;
                }

                float deltaX = organisms[i].dx * organisms[i].speed * dt;
                float deltaY = organisms[i].dy * organisms[i].speed * dt;

                organisms[i].x += deltaX;
                organisms[i].y += deltaY;

                // Рисуем организм: центр X, центр Y, радиус, цвет
                DrawCircle(organisms[i].x, organisms[i].y ,organisms[i].masa , GREEN);
            }

            //рисуем еду
            if (food[j].alive == true)
            {
                DrawCircle(food[j].x, food[j].y, food[j].value , RED);
            }

        }


        // Завершаем отрисовку кадра
        EndDrawing();

    }

    // Закрываем окно и освобождаем ресурсы
    CloseWindow();
    free(organisms);
    free(food);

    return 0;
}
