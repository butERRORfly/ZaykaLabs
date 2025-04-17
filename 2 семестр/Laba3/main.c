#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node* pred;
}; 
typedef struct node node;

struct queue {
    node* header;
    node* tail;
    int size;
};
typedef struct queue queue;

void init_queue(queue* cur_queue) {
    cur_queue->header = NULL;
    cur_queue->tail = NULL;
    cur_queue->size = 0;
}

int empty(queue* cur_queue) {
    return cur_queue->size == 0;
}

void push(queue* cur_queue, int val) {
    node* new_tail = malloc(sizeof(node));
    new_tail->pred = NULL;
    new_tail->val = val;

    if (empty(cur_queue)) {
        cur_queue->header = new_tail;
        cur_queue->tail = new_tail;
    } else {
        cur_queue->tail->pred = new_tail;
    }

    cur_queue->tail = new_tail;
    cur_queue->size++;
}

void pop(queue* cur_queue) {
    if (empty(cur_queue)) {
        return;
    }

    node* new_header = cur_queue->header->pred;
    free(cur_queue->header);
    cur_queue->header = new_header;

    if (cur_queue->header == NULL) {
        cur_queue->tail = NULL;
    }

    cur_queue->size--;
}

int size(queue* cur_queue) {
    return cur_queue->size;
}

int front(queue* cur_queue) {
    return cur_queue->header->val;
}

int back(queue* cur_queue) {
    return cur_queue->tail->val;
}

void clear(queue* cur_queue) {
    while (!empty(cur_queue)) {
        pop(cur_queue);
    }
}

void print_queue(queue* q) {
    queue temp;
    init_queue(&temp);
    
    printf("Очередь: ");
    while (!empty(q)) {
        int val = front(q);
        printf("%d ", val);
        pop(q);
        push(&temp, val);
    }
    printf("\n");
    
    // Восстанавливаем исходную очередь
    while (!empty(&temp)) {
        push(q, front(&temp));
        pop(&temp);
    }
}

int procedure(queue* q) {
    if (size(q) < 2) return 0;

    queue temp;
    init_queue(&temp);
    int swapped = 0;
    int prev_val = front(q);
    pop(q);
    push(&temp, prev_val);

    while (!empty(q)) {
        int current_val = front(q);
        if (current_val < prev_val) {
            pop(q);
            queue temp2;
            init_queue(&temp2);

            while (!empty(&temp)) {
                int val = front(&temp);
                if (!swapped && current_val < val) {
                    push(&temp2, current_val);
                    swapped = 1;
                }
                push(&temp2, val);
                pop(&temp);
            }

            if (!swapped) {
                push(&temp2, current_val);
            }

            while (!empty(&temp2)) {
                push(&temp, front(&temp2));
                pop(&temp2);
            }

            while (!empty(q)) {
                push(&temp, front(q));
                pop(q);
            }

            while (!empty(&temp)) {
                push(q, front(&temp));
                pop(&temp);
            }

            return 1;
        } else {
            prev_val = current_val;
            push(&temp, prev_val);
            pop(q);
        }
    }

    while (!empty(&temp)) {
        push(q, front(&temp));
        pop(&temp);
    }

    return 0;
}



// Сортировка очереди
void sort(queue* q) {
    if (size(q) < 2) {
        return;
    }
    
    while (procedure(q)) {
        print_queue(q);
    }
}

int main() {
    queue our_queue;
    init_queue(&our_queue);

    printf("Меню:\n1 - добавить элемент\n2 - удалить элемент\n3 - вернуть верхний элемент\n4 - вернуть нижний элемент\n5 - узнать размер\n6 - отсортировать очередь\n7 - вывести очередь\n");

    int flag;
    while (scanf("%d", &flag) != EOF) {
        if (flag == 1) {
            int new_val;
            scanf("%d", &new_val);
            push(&our_queue, new_val);
        } else if (flag == 2) {
            pop(&our_queue);
        } else if (flag == 3) {
            if (empty(&our_queue)) {
                printf("Очередь пустая\n");
            } else {
                printf("Верхний элемент: %d\n", front(&our_queue));
            }
        } else if (flag == 4) {
            if (empty(&our_queue)) {
                printf("Очередь пустая\n");
            } else {
                printf("Нижний элемент: %d\n", back(&our_queue));
            }            
        } else if (flag == 5) {
            printf("Размер: %d\n", size(&our_queue));
        } else if (flag == 6) {
            sort(&our_queue);
            printf("Очередь отсортирована\n");
        } else if (flag == 7) {
            print_queue(&our_queue);
        } else {
            break;
        }
    }

    clear(&our_queue);
}