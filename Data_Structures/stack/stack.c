/*
Фиксированный (ограничен SIZE_STACK)
Быстрее (нет malloc/free)
Подходит, если известен максимальный размер
*/


#include <stdio.h>
#include <stdlib.h>


#define SIZE_STACK 100      // Максимальный размер стека

typedef struct {
    int data[SIZE_STACK];
    int top;        // Индекс вершины стека
} ArrayStack;


void init_Stack(ArrayStack* s);                 //  Инициализация стека
unsigned char isEmpty(ArrayStack* s);           //  Проверка на пустоту
unsigned char isFull(ArrayStack* s);            // Проверка на переполнение

void Push(ArrayStack* s, int x);                // Добавление элемента
int Pop(ArrayStack* s);                         // Удаление и возврат верхнего элемента
int Peek(ArrayStack* s);                        // Просмотр верхнего элемента без удаления


// Пример: Проверка сбалансированности скобок
unsigned char isBalanced(const char* str);


int main() {
    ArrayStack s;
    init_Stack(&s);

    Push(&s, 10);
    Push(&s, 20);
    Push(&s, 30);

    printf("Upper element: %d\n", Peek(&s));  // 30
    printf("Deleted: %d\n", Pop(&s));           // 30
    printf("New top: %d\n", Peek(&s));   // 20



    printf("%d\n", isBalanced("(()[])"));  // 1 (true)
    printf("%d\n", isBalanced("([)]"));    // 0 (false)
    
    return 0;
}




void init_Stack(ArrayStack* s) {
    s->top = -1;    // Стек пуст
    return;
}

unsigned char isEmpty(ArrayStack* s) {
    return s->top == -1;
}

unsigned char isFull(ArrayStack* s) {
    return s->top == SIZE_STACK - 1;
}



void Push(ArrayStack* s, int x) {
    if (isFull(s)){
        printf("The stack is overflowing!\n");
        return;
    }
    s->data[++s->top] = x;      // Увеличиваем top и добавляем элемент
}

int Pop(ArrayStack* s) {
    if (isEmpty(s)){
        printf("The stack is empty!\n");
        exit(1);
    }
    return s->data[s->top--];   // Возвращаем элемент и уменьшаем top
}   

int Peek(ArrayStack* s) {
    if (isEmpty(s)){
        printf("The stack is empty!\n");
        exit(1);
    }
    return s->data[s->top]; 
} 





// Пример: Проверка сбалансированности скобок
unsigned char isBalanced(const char* str){
    ArrayStack s;
    init_Stack(&s);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{') 
            Push(&s, str[i]);
        else{
            if (isEmpty(&s)) return 0;
            char top = Pop(&s);
            if ((top == '(' && str[i] != ')') ||
                (top == '[' && str[i] != ']') ||
                (top == '{' && str[i] != '}'))
                return 0;
        }
    }
    return isEmpty(&s);     // Если стек пуст, скобки сбалансированы
}
