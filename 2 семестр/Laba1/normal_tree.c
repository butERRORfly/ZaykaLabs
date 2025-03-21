#include <stdio.h>
#include <stdlib.h>

// Структура узла дерева
typedef struct Node {
    int data;                 // Данные узла
    struct Node *firstChild;  // Указатель на первого
    struct Node *nextSibling; // Указатель на следующего
} Node;

// Функция для создания нового узла
Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->data = data;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Функция для добавления потомка к узлу
void addChild(Node *parent, int data) {
    Node *newNode = createNode(data);
    if (parent->firstChild == NULL) {
        // Если у узла нет потомков, добавляем первого потомка
        parent->firstChild = newNode;
    } else {
        // Иначе идем к последнему брату и добавляем нового
        Node *temp = parent->firstChild;
        while (temp->nextSibling != NULL) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = newNode;
    }
}

// Функция для поиска узла по значению
Node *findNode(Node *root, int data) {
    if (root == NULL)
        return NULL;
    if (root->data == data)
        return root;

    Node *foundNode = findNode(root->firstChild, data);
    if (foundNode != NULL)
        return foundNode;

    return findNode(root->nextSibling, data);
}

// Функция для поиска родителя узла
Node *findParent(Node *root, Node *target) {
    if (root == NULL || root == target)
        return NULL;

    Node *child = root->firstChild;
    while (child != NULL) {
        if (child == target) {
            return root;
        }
        Node *sibling = child->nextSibling;
        while (sibling != NULL) {
            if (sibling == target) {
                return root;
            }
            sibling = sibling->nextSibling;
        }
        Node *parent = findParent(child, target);
        if (parent != NULL) {
            return parent;
        }
        child = child->nextSibling;
    }
    return NULL;
}

// Функция для удаления поддерева
void deleteSubtree(Node *root) {
    if (root == NULL)
        return;

    // Рекурсивно удаляем всех потомков
    deleteSubtree(root->firstChild);

    // Рекурсивно удаляем всех братьев
    deleteSubtree(root->nextSibling);

    // Освобождаем текущий узел
    free(root);
}

// Функция для удаления узла и его поддерева
void deleteNode(Node **root, int data) {
    if (*root == NULL)
        return;

    Node *nodeToDelete = findNode(*root, data);
    if (nodeToDelete == NULL) {
        printf("Узел не найден.\n");
        return;
    }

    // Если удаляемый узел — корень дерева
    if (nodeToDelete == *root) {
        deleteSubtree(*root);
        *root = NULL;
        printf("Корень дерева удален.\n");
        return;
    }

    // Находим родителя удаляемого узла
    Node *parent = findParent(*root, nodeToDelete);
    if (parent == NULL) {
        printf("Родительский узел не найден.\n");
        return;
    }

    // Удаляем узел из списка потомков или братьев родителя
    if (parent->firstChild == nodeToDelete) {
        parent->firstChild = nodeToDelete->nextSibling;
    } else {
        Node *temp = parent->firstChild;
        while (temp->nextSibling != nodeToDelete) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = nodeToDelete->nextSibling;
    }

    // Обнуляем указатели удаляемого узла
    nodeToDelete->firstChild = NULL;
    nodeToDelete->nextSibling = NULL;

    // Удаляем поддерево
    deleteSubtree(nodeToDelete);
    printf("Узел и его поддерево удалены.\n");
}

// Функция для печати дерева (в глубину)
void printTree(Node *root, int level) {
    if (root == NULL)
        return;

    // Печатаем текущий узел
    for (int i = 0; i < level; i++) {
        printf("  "); // Отступ для визуализации уровня
    }
    printf("%d\n", root->data);

    // Рекурсивно печатаем всех потомков
    printTree(root->firstChild, level + 1);

    // Рекурсивно печатаем всех братьев
    printTree(root->nextSibling, level);
}

// Функция для вычисления степени узла (количество потомков)
int getDegree(Node *node) {
    if (node == NULL)
        return 0;
    int degree = 0;
    Node *child = node->firstChild;
    while (child != NULL) {
        degree++;
        child = child->nextSibling;
    }
    return degree;
}

// Функция для подсчета числа вершин, степень которых совпадает со значением
// элемента
int countNodesWithDegreeEqualsValue(Node *root) {
    if (root == NULL)
        return 0;

    int count = 0;
    if (getDegree(root) == root->data) {
        count++;
    }

    // Рекурсивно проверяем всех потомков и братьев
    count += countNodesWithDegreeEqualsValue(root->firstChild);
    count += countNodesWithDegreeEqualsValue(root->nextSibling);

    return count;
}

// Функция для освобождения памяти дерева
void freeTree(Node *root) {
    if (root == NULL)
        return;

    // Рекурсивно освобождаем всех потомков
    freeTree(root->firstChild);

    // Рекурсивно освобождаем всех братьев
    freeTree(root->nextSibling);

    // Освобождаем текущий узел
    free(root);
}

// Текстовое меню
void menu(Node **root) {
    int choice, data, parentData;
    Node *parentNode;

    while (1) {
        printf("\nМеню:\n");
        printf("1. Добавить узел\n");
        printf("2. Визуализировать дерево\n");
        printf("3. Удалить узел\n");
        printf("4. Подсчитать вершины, степень которых равна значению\n");
        printf("5. Выйти\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Введите значение нового узла: ");
            scanf("%d", &data);
            printf("Введите значение родительского узла: ");
            scanf("%d", &parentData);
            parentNode = findNode(*root, parentData);
            if (parentNode == NULL) {
                printf("Родительский узел не найден.\n");
            } else {
                addChild(parentNode, data);
                printf("Узел добавлен.\n");
            }
            break;

        case 2:
            printf("Дерево:\n");
            printTree(*root, 0);
            break;

        case 3:
            printf("Введите значение узла для удаления: ");
            scanf("%d", &data);
            deleteNode(root, data);
            break;

        case 4:
            printf("Число вершин, степень которых равна значению: %d\n",
                   countNodesWithDegreeEqualsValue(*root));
            break;

        case 5:
            freeTree(*root);
            printf("Программа завершена.\n");
            return;

        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
}

int main() {
    Node *root = createNode(1);

    menu(&root);

    return 0;
}
