#include <stdio.h>
#include <stdlib.h>

// Структура узла дерева
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Создание нового узла
Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Добавление узла в упорядоченное двоичное дерево
Node *insertNode(Node *root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// Визуализация дерева
void printTree(Node *root, int depth) {
    if (root == NULL) {
        return;

        printTree(root->right, depth + 1);
        for (int i = 0; i < depth; i++) {
            printf("   ");
        }
        printf("%d\n", root->data);
        printTree(root->left, depth + 1);
    }

    // Удаление узла и его поддерева
    Node *deleteNode(Node * root, int data) {
        if (root == NULL) {
            return root;
        }
        if (data < root->data) {
            root->left = deleteNode(root->left, data);
        } else if (data > root->data) {
            root->right = deleteNode(root->right, data);
        } else {
            if (root->left == NULL) {
                Node *temp = root->right;
                free(root);
                return temp;
            } else if (root->right == NULL) {
                Node *temp = root->left;
                free(root);
                return temp;
            }
            Node *temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    // Вычисление степени узла (количество дочерних узлов)
    int getDegree(Node * node) {
        int degree = 0;
        if (node->left != NULL)
            degree++;
        if (node->right != NULL)
            degree++;
        return degree;
    }

    // Подсчет числа вершин, степень которых совпадает со значением элемента
    int countNodesWithDegreeEqualsValue(Node * root) {
        if (root == NULL) {
            return 0;
        }
        int count = 0;
        if (getDegree(root) == root->data) {
            count++;
        }
        count += countNodesWithDegreeEqualsValue(root->left);
        count += countNodesWithDegreeEqualsValue(root->right);
        return count;
    }

    // Освобождение памяти дерева
    void freeTree(Node * root) {
        if (root == NULL) {
            return;
        }
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }

    // Текстовое меню
    void menu() {
        Node *root = NULL;
        int choice, value;

        while (1) {
            printf("\nМеню:\n");
            printf("1. Добавить узел\n");
            printf("2. Визуализировать дерево\n");
            printf("3. Удалить узел\n");
            printf("4. Вычислить число вершин, степень которых совпадает со "
                   "значением элемента\n");
            printf("5. Выход\n");
            printf("Выберите действие: ");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("Введите значение узла: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("Дерево:\n");
                printTree(root, 0);
                break;
            case 3:
                printf("Введите значение узла для удаления: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 4:
                printf("Число вершин, степень которых совпадает со значением "
                       "элемента: %d\n",
                       countNodesWithDegreeEqualsValue(root));
                break;
            case 5:
                freeTree(root);
                exit(0);
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
            }
        }
    }

    int main() {
        menu();
        return 0;
    }
