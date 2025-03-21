#include <stdio.h>
#include <stdlib.h>

// Структура узла дерева
typedef struct Node {
    int data;               // Данные узла
    struct Node* firstChild; // Указатель на первого потомка
    struct Node* nextSibling; // Указатель на следующего брата
} Node;

// Функция для создания нового узла
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Функция для добавления потомка к узлу
void addChild(Node* parent, int data) {
    Node* newNode = createNode(data);
    if (parent->firstChild == NULL) {
        // Если у узла нет потомков, добавляем первого потомка
        parent->firstChild = newNode;
    } else {
        // Иначе идем к последнему брату и добавляем нового
        Node* temp = parent->firstChild;
        while (temp->nextSibling != NULL) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = newNode;
    }
}

// Функция для поиска узла по значению
Node* findNode(Node* root, int data) {
    if (root == NULL) return NULL;
    if (root->data == data) return root;

    Node* foundNode = findNode(root->firstChild, data);
    if (foundNode != NULL) return foundNode;

    return findNode(root->nextSibling, data);
}

// Функция для удаления поддерева
void deleteSubtree(Node* root) {
    if (root == NULL) return;

    // Рекурсивно удаляем всех потомков
    deleteSubtree(root->firstChild);

    // Рекурсивно удаляем всех братьев
    deleteSubtree(root->nextSibling);

    // Освобождаем текущий узел
    free(root);
}

// Функция для печати дерева (в глубину)
void printTree(Node* root, int level) {
    if (root == NULL) return;

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

// Функция для вычисления высоты дерева
int height(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int maxHeight = 0;
    Node* child = root->firstChild;
    while (child != NULL) {
        int childHeight = height(child);
        if (childHeight > maxHeight) {
            maxHeight = childHeight;
        }
        child = child->nextSibling;
    }
    return maxHeight + 1;
}

// Функция для проверки, является ли дерево AVL-деревом
int isAVL(Node* root) {
    if (root == NULL) {
        return 1; // true
    }

    // Вычисляем высоту левого и правого поддеревьев
    Node* child = root->firstChild;
    int prevHeight = height(child);
    child = child->nextSibling;

    while (child != NULL) {
        int currentHeight = height(child);
        if (abs(prevHeight - currentHeight) > 1) {
            return 0; // false
        }
        prevHeight = currentHeight;
        child = child->nextSibling;
    }

    // Рекурсивно проверяем всех потомков
    child = root->firstChild;
    while (child != NULL) {
        if (!isAVL(child)) {
            return 0; // false
        }
        child = child->nextSibling;
    }

    return 1; // true
}

// Меню для взаимодействия с пользователем
void menu() {
    Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\nMenu:\n");
        printf("0 x - add x to the tree\n");
        printf("1 x - delete x from the tree\n");
        printf("2 - print the tree\n");
        printf("3 - check if the tree is an AVL-tree\n");
        printf("4 - exit\n");
        printf("Enter a command: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("Enter the value to add: ");
                scanf("%d", &value);
                if (root == NULL) {
                    root = createNode(value);
                    printf("%d - added as the root of the tree\n", value);
                } else {
                    printf("Enter the parent value: ");
                    int parentValue;
                    scanf("%d", &parentValue);
                    Node* parent = findNode(root, parentValue);
                    if (parent == NULL) {
                        printf("Parent not found\n");
                    } else {
                        addChild(parent, value);
                        printf("%d - added as a child of %d\n", value, parentValue);
                    }
                }
                break;
            case 1:
                printf("Enter the value to delete: ");
                scanf("%d", &value);
                Node* nodeToDelete = findNode(root, value);
                if (nodeToDelete == NULL) {
                    printf("%d - not found in the tree\n", value);
                } else {
                    deleteSubtree(nodeToDelete);
                    printf("%d - deleted from the tree\n", value);
                }
                break;
            case 2:
                printf("Tree:\n");
                printTree(root, 0);
                break;
            case 3:
                if (isAVL(root)) {
                    printf("The tree is an AVL-tree\n");
                } else {
                    printf("The tree is not an AVL-tree\n");
                }
                break;
            case 4:
                printf("Exiting...\n");
                deleteSubtree(root);
                exit(0);
            default:
                printf("Invalid command. Try again\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
