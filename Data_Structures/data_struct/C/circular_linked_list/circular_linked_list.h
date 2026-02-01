#ifndef CIRCULAR_LINKED_LIST
#define CIRCULAR_LINKED_LIST


#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;


typedef struct {
    Node* head; // Первый элемент (может быть NULL, если список пуст)
    int size;   // Количество элементов
} CircularDoublyLinkedList;



void init_List(CircularDoublyLinkedList* list);         // Инициализация списка

Node* create_Node(int data);                            // Создание нового узла

void add_To_Empty(CircularDoublyLinkedList* list, int data);            // Добавление элементов В пустой список
void add_First(CircularDoublyLinkedList* list, int data);               // Добавление элементов В начало списка
void add_Last(CircularDoublyLinkedList* list, int data);                // Добавление элементов В конец списка
void add_At_Index(CircularDoublyLinkedList* list, int data, int index); // Добавление элементов По индексу 

void delete_First(CircularDoublyLinkedList* list);                      // Удаление первого элемента
void delete_Only_Node(CircularDoublyLinkedList* list);                  // Удаление единственного элемента
void delete_Last(CircularDoublyLinkedList* list);                       // Удаление последнего элемента
void delete_At_Index(CircularDoublyLinkedList* list, int index);        // Удаление по индексу

int get_At_Index(CircularDoublyLinkedList* list, int index);            // Получение элемента по индексу (O(n), но можно оптимизировать)

void print_List(CircularDoublyLinkedList* list);                        //  Печать списка

#endif
