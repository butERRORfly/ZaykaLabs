#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Структура для узла дерева выражений
typedef struct Node {
    char type; // 'V' для переменной, 'C' для константы, 'O' для операции
    int value; // значение, если это константа
    char op; // операция, если это оператор
    char var; // переменная, если это переменная
    struct Node* left;
    struct Node* right;
} Node;

// Структура для стека
typedef struct Stack {
    void* data; // Может хранить Node* или char
    struct Stack* next;
} Stack;

// Функция для добавления элемента в стек
void push(Stack** top, void* data) {
    Stack* new_stack_node = (Stack*)malloc(sizeof(Stack));
    new_stack_node->data = data;
    new_stack_node->next = *top;
    *top = new_stack_node;
}

// Функция для извлечения элемента из стека
void* pop(Stack** top) {
    if (*top == NULL) return NULL;
    Stack* temp = *top;
    void* data = temp->data;
    *top = temp->next;
    free(temp);
    return data;
}

// Функция для создания нового узла
Node* create_node(char type, int value, char op, char var) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = type;
    node->value = value;
    node->op = op;
    node->var = var;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* reduce_expression(Node* root) {
    if (root == NULL) return NULL;

    // Если это операция возведения в степень
    if (root->op == '^') {
        // Проверяем, что левый операнд — переменная, а правый — константа
        if (root->left->type == 'V' && root->right->type == 'C') {
            int exponent = root->right->value;
            if (exponent < 0) {
                // Обработка отрицательной степени
                Node* result = create_node('O', 0, '/', 0);
                result->left = create_node('C', 1, 0, 0); // 1 в числителе

                // Создаем узел для x^n, где n — положительная степень
                Node* power_node = create_node('O', 0, '^', 0);
                power_node->left = create_node('V', 0, 0, root->left->var);
                power_node->right = create_node('C', -exponent, 0, 0); // -exponent, так как exponent отрицательный

                // Редуцируем power_node до конца
                power_node = reduce_expression(power_node);

                result->right = power_node;
                return result;
            } else {
                // Обработка положительной степени
                Node* result = create_node('O', 0, '*', 0);
                Node* current = create_node('V', 0, 0, root->left->var);
                result->left = current;

                for (int i = 1; i < exponent; i++) {
                    Node* new_node = create_node('O', 0, '*', 0);
                    new_node->left = create_node('V', 0, 0, root->left->var);
                    new_node->right = current;
                    current = new_node;
                }

                return current;
            }
        }
    }

    // Рекурсивно редуцируем левое и правое поддерево
    root->left = reduce_expression(root->left);
    root->right = reduce_expression(root->right);

    return root;
}

// Функция для печати дерева выражений
void print_expression(Node* root) {
    if (root == NULL) return;

    if (root->type == 'C') {
        printf("%d", root->value);
    } else if (root->type == 'V') {
        printf("%c", root->var);
    } else if (root->type == 'O') {
        printf("(");
        print_expression(root->left);
        printf(" %c ", root->op);
        print_expression(root->right);
        printf(")");
    }
}

// Функция для визуализации дерева (текстовый вывод)
void print_tree(Node* root, int depth) {
    if (root == NULL) return;

    // Отступ для визуализации уровня дерева
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    // Вывод текущего узла
    if (root->type == 'C') {
        printf("%d\n", root->value);
    } else if (root->type == 'V') {
        printf("%c\n", root->var);
    } else if (root->type == 'O') {
        printf("%c\n", root->op);
    }

    // Рекурсивный вывод левого и правого поддерева
    print_tree(root->left, depth + 1);
    print_tree(root->right, depth + 1);
}

// Функция для освобождения памяти, выделенной под дерево
void free_tree(Node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// Функция для определения приоритета оператора
int precedence(char op) {
    switch (op) {
        case '^': return 4;
        case '*':
        case '/': return 3;
        case '+':
        case '-': return 2;
        case '~': return 5; // Унарный минус имеет высший приоритет
        default: return 0;
    }
}

// Преобразование инфиксной записи в постфиксную (обратную польскую запись)
void infix_to_postfix(const char* input, char* output) {
    Stack* op_stack = NULL;
    int output_index = 0;
    int i = 0;
    char ch;

    while ((ch = input[i]) != '\0') {
        if (isdigit(ch) || (ch == '-' && (i == 0 || input[i-1] == '(' || precedence(input[i-1]) > 0))) {
            // Обработка чисел и унарного минуса
            if (ch == '-') {
                output[output_index++] = '~'; // Используем '~' для унарного минуса
                i++;
            } else {
                int num = 0;
                while (isdigit(input[i])) {
                    num = num * 10 + (input[i] - '0');
                    i++;
                }
                char num_str[12];
                sprintf(num_str, "%d", num);
                strcpy(&output[output_index], num_str);
                output_index += strlen(num_str);
                output[output_index++] = ' '; // Разделитель
            }
        } else if (isalpha(ch)) {
            // Обработка переменных
            output[output_index++] = ch;
            i++;
            output[output_index++] = ' '; // Разделитель
        } else if (ch == '(') {
            // Открывающая скобка
            push(&op_stack, (void*)(long)ch);
            i++;
        } else if (ch == ')') {
            // Закрывающая скобка
            while (op_stack != NULL && (char)(long)op_stack->data != '(') {
                output[output_index++] = (char)(long)pop(&op_stack);
                output[output_index++] = ' '; // Разделитель
            }
            pop(&op_stack); // Удаляем '(' из стека
            i++;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '~') {
            // Обработка операторов
            while (op_stack != NULL && precedence((char)(long)op_stack->data) >= precedence(ch)) {
                output[output_index++] = (char)(long)pop(&op_stack);
                output[output_index++] = ' '; // Разделитель
            }
            push(&op_stack, (void*)(long)ch);
            i++;
        } else if (ch == ' ' || ch == '\t') {
            // Пропуск пробелов
            i++;
        } else {
            printf("Ошибка: неожиданный символ '%c'\n", ch);
            exit(1);
        }
    }

    // Оставшиеся операторы в стеке
    while (op_stack != NULL) {
        output[output_index++] = (char)(long)pop(&op_stack);
        output[output_index++] = ' '; // Разделитель
    }

    output[output_index] = '\0'; // Завершаем строку
}

// Разбор постфиксной записи и построение дерева
Node* parse_postfix(const char* postfix) {
    Stack* stack = NULL;
    int i = 0;
    char ch;

    while ((ch = postfix[i]) != '\0') {
        if (isdigit(ch) || (ch == '~' && isdigit(postfix[i+1]))) {
            // Обработка чисел и унарного минуса
            int sign = 1;
            if (ch == '~') {
                sign = -1;
                i++;
            }
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            Node* node = create_node('C', sign * num, 0, 0);
            push(&stack, node);
        } else if (isalpha(ch)) {
            // Обработка переменных
            Node* node = create_node('V', 0, 0, ch);
            push(&stack, node);
            i++;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '~') {
            // Обработка операторов
            if (ch == '~') {
                // Унарный минус
                Node* node = create_node('O', 0, '~', 0);
                node->right = (Node*)pop(&stack);
                push(&stack, node);
            } else {
                // Бинарные операторы
                Node* node = create_node('O', 0, ch, 0);
                node->right = (Node*)pop(&stack);
                node->left = (Node*)pop(&stack);
                push(&stack, node);
            }
            i++;
        } else if (ch == ' ') {
            // Пропуск пробелов
            i++;
        } else {
            printf("Ошибка: неожиданный символ '%c'\n", ch);
            exit(1);
        }
    }

    return (Node*)pop(&stack);
}

// Основная функция
int main() {
    char input[100];
    printf("Введите выражение: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Удаление символа новой строки

    // Преобразование инфиксной записи в постфиксную
    char postfix[200];
    infix_to_postfix(input, postfix);

    // Разбор постфиксной записи и построение дерева
    Node* root = parse_postfix(postfix);

    printf("Исходное выражение: ");
    print_expression(root);
    printf("\n");

    Node* reduced = reduce_expression(root);

    printf("Редуцированное выражение: ");
    print_expression(reduced);
    printf("\n");

    printf("Дерево выражений:\n");
    print_tree(reduced, 0);

    free_tree(reduced);

    return 0;
}