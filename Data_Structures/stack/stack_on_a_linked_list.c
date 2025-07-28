/*
Динамический (расширяется автоматически)
Медленнее (из-за работы с памятью)
Подходит для динамических данных
*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;  // Вершина стека
    int size;   // Количество элементов
} LinkedListStack;

// Создание нового узла
Node* create_node(int x) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    new_node->data = x;
    new_node->next = NULL;
    return new_node;
}

// Инициализация стека
void init_stack(LinkedListStack* s) {
    s->top = NULL;
    s->size = 0;
}

// Проверка на пустоту
bool isEmpty(LinkedListStack* s) {
    return s->top == NULL;
}

// Добавление элемента
void push(LinkedListStack* s, int x) {
    Node* new_node = create_node(x);
    new_node->next = s->top;  // Новый элемент указывает на старую вершину
    s->top = new_node;        // Обновляем вершину
    s->size++;
}

// Удаление и возврат верхнего элемента
int pop(LinkedListStack* s) {
    if (isEmpty(s)) {
        printf("Стек пуст!\n");
        exit(1);
    }
    Node* temp = s->top;
    int data = temp->data;
    s->top = s->top->next;  // Перемещаем вершину на следующий элемент
    free(temp);
    s->size--;
    return data;
}

// Просмотр верхнего элемента без удаления
int peek(LinkedListStack* s) {
    if (isEmpty(s)) {
        printf("Стек пуст!\n");
        exit(1);
    }
    return s->top->data;
}

// Пример использования
int main() {
    LinkedListStack s;
    init_stack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("Верхний элемент: %d\n", peek(&s));  // 30
    printf("Удалён: %d\n", pop(&s));           // 30
    printf("Новый верхний: %d\n", peek(&s));   // 20

    return 0;
}