#include <stdio.h>

// Функция максимума
int Max(int x, int y) {
    if (x > y){
        return x;
    } else {
        return y;
    }
}

// Функция минимума
int Min(int x, int y) {
    if (x < y) {
        return x;
    } else {
        return y;
    }
}

// Функция вычисления остатка от деления
int Mod(int x, int y) {
    if (y != 0) {
        return x % y;
    } else {
        return 0;
    }
}

// Функция определения знака числа
int Sign(int x) {
    if (x < 0) {
        return -1;
    } else if (x > 0) {
        return 1;
    } else {
        return 0;
    }
}

// Модуль числа
int Abs(int x) {
    if (x >= 0) {
        return x;
    } else {
        return -x;
    }
}

const int I_0 = -11;
const int J_0 = -6;
const int L_0 = -5;

// Объявляем структуру данных
typedef struct {
    /* Данные структуры */
    int x;
    int y;
} PointZone;

// Находимся в зоне или нет
int IsMeInZone(PointZone point) {
    // Координаты центра квадрата
    int centerX = 10;
    int centerY = -10;
    // Длина стороны квадрата
    int sideLength = 10;

    // Вычисление границ квадрата
    int halfSide = sideLength / 2;
    int xMin = centerX - halfSide;
    int xMax = centerX + halfSide;
    int yMin = centerY - halfSide;
    int yMax = centerY + halfSide;

    // Переменные для координат точки
    int tmp_x = point.x;
    int tmp_y = point.y;

    // Проверка, находится ли точка внутри квадрата
    if (tmp_x >= xMin && tmp_x <= xMax && tmp_y >= yMin && tmp_y <= yMax) {
        return 1;
    } else {
        return 0;
    }
}


int main() {
    int i = I_0;
    int j = J_0;
    int l = L_0;
    PointZone point;
    point.x = i;
    point.y = j;

    int counter = 0; // Кол-во точек, удв-их условию

    for (int k = 1; k <= 50; k++) {
        i = Mod(((point.x + point.y + l) * (k + 1)), 25) - Mod((point.x * point.y * l * (k + 2)), 10) + 10;
        j = Min(Mod(((point.x + point.y + l) * (k + 3)), 25), Mod((point.x * point.y * l * (k + 4)), 25)) + 10;
        l = 2 * Sign(l) * Abs(Mod(((point.x + point.y + l) * (k + 5)), 10) - Mod((point.x * point.y * l * (k + 6)), 25));
    
        point.x = i;
        point.y = j;
        printf("k = %d, x = %d, y = %d, l = %d попала = %d \n", k, point.x, point.y, l, IsMeInZone(point));

        if (IsMeInZone(point) == 1) {
            counter++;
        }
    }
    if (counter == 0) {
        printf("Ни одна из точек не попала в заданную область за 50 итераций\n");
    } else {
        printf("Количество точек, попавших в зону: %d\n", counter);
    }
    return 0;
}