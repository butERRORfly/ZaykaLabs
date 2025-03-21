#include <stdio.h>

const int ORDER_MATRIX = 65; // 8 * 8 + 1 = 65

// Замена элементов побочной диагонали суммами элементов, проходящих через них главной и других параллельных диагоналей.

// Узнаем порядок матрицы
int matrixOrder(const int n) {
  switch (n) {
  case 1:
    return 1;
  case 4:
    return 2;
  case 9:
    return 3;
  case 16:
    return 4;
  case 25:
    return 5;
  case 36:
    return 6;
  case 49:
    return 7;
  case 64:
    return 8;
  default:
    return 0;
  }
}

int calculateSumMainDiagonal (int matrix[ORDER_MATRIX][ORDER_MATRIX], int order) {
  int sum = 0;
  for (int i = 0; i < order; ++i) {
    for (int j = 0; j < order; ++j) {
      if (i == j) {
        sum += matrix[i][j];
      }
    }
  }
  return sum;
}

// Считываем матрицу из файла
int readMatrix(int matrix[ORDER_MATRIX][ORDER_MATRIX], const char *filename) {
  FILE *file;
  file = fopen(filename, "r");

  int counter = 0;
  int num = 0;

  // Сначала нужно подсчитать количество элементов
  while (fscanf(file, "%d", &num) != EOF) {
    ++counter;
  }

  // Получаем порядок матрицы
  int order = matrixOrder(counter);

  // Вернемся в начало файла
  rewind(file);

  // Теперь заполняем матрицу
  for (int i = 0; i < order; ++i) {
    for (int j = 0; j < order; ++j) {
      if (fscanf(file, "%d", &matrix[i][j]) == EOF) {
        break; // Если достигнут конец файла
      }
    }
  }

  // Выводим старую матрицу
  printf("%s\n", "Старая матрица:");
  for (int i = 0; i < order; ++i) {
    for (int j = 0; j < order; ++j) {
      printf("%2d ", matrix[i][j]);
    }
    printf("\n");
  }

  for (int i = 0; i < order; ++i) {
    for (int j = 0; j < order; ++j) {
      if (i + j == order - 1) {
        if ((order - i - 1) < (order / 2)) {
          for (int d = 1; d < order - i; ++d) {
            matrix[i][j] = matrix[i][j] + matrix[i - 1][j - 1] + matrix[i + 1][j + 1];
          }
        } else {
          for (int d = 0; d < i; ++d) {
            matrix[i][j] = matrix[i][j] + matrix[i - 1][j - 1] + matrix[i + 1][j + 1];
          }
        }
      }
    }
  }

  // Выводим новую матрицу
  printf("%s\n", "Новая матрица:");
  for (int i = 0; i < order; ++i) {
    for (int j = 0; j < order; ++j) {
      printf("%2d ", matrix[i][j]);
    }
    printf("\n");
  }

  return 0;
}


int main() {
  int matrix[ORDER_MATRIX][ORDER_MATRIX];
  char filename[20]; 
  scanf("%19s", filename);
  readMatrix(matrix, "in.txt");
}
