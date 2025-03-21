#include <stdio.h>

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

// Находимся в зоне или нет
int IsMeInZone(int x, int y) {
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
  int tmp_x = x;
  int tmp_y = y;

  // Проверка, находится ли точка внутри квадрата
  if (x >= xMin && x <= xMax && y >= yMin && y <= yMax) {
    return 1;
  } else {
    return 0;
  }
}

int main() {
  int i = I_0;
  int j = J_0;
  int l = L_0;
  int x = i;
  int y = j;

  int counter = 0; // Кол-во точек, удв-их условию
  if (IsMeInZone(x, y) == 1) {
    counter++;
    printf("попала на шагу %d в координате (%d, %d) l = %d \n", 0, x, y, l);
  }

  for (int k = 1; k <= 50; k++) {
    i = Mod(((x + y + l) * (k + 1)), 25) - Mod((x * y * l * (k + 2)), 10) + 10;
    j = Min(Mod(((x + y + l) * (k + 3)), 25), Mod((x * y * l * (k + 4)), 25)) +
        10;
    l = 2 * Sign(l) *
        Abs(Mod(((x + y + l) * (k + 5)), 10) - Mod((x * y * l * (k + 6)), 25));

    x = i;
    y = j;
    if (IsMeInZone(x, y) == 1) {
      counter++;
      printf("попала на шагу %d в координате (%d, %d) l = %d \n", k, x, y, l);
    }
  }
  if (counter == 0) {
    printf("Ни одна из точек не попала в заданную область за 50 итераций\n");
  } else {
    printf("Количество точек, попавших в зону: %d\n", counter);
  }
  return 0;
}
