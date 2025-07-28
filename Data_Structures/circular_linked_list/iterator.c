/*
Плюсы итератора:

Инкапсуляция: не нужно знать внутреннее устройство списка.
Гибкость: можно реализовать разные стратегии обхода (вперёд, назад, с шагом).
Безопасность: контроль за границами списка.

Минусы:

Дополнительная память под структуру итератора.
Сложнее, чем прямой перебор через head и next.

Где применяется?

Стандартные библиотеки (например, iterator в C++).
Обход сложных структур (деревья, графы).
Ленивые вычисления (элементы вычисляются по мере перебора).
*/



#include <stdio.h>
#include <stdlib.h>
#include "circular_linked_list.h"




typedef struct {
    Node* current;  // Текущий узел
    Node* start;    // Начальный узел (для отслеживания полного прохода)
    int is_first;   // Флаг первого элемента
} ListIterator;



ListIterator init_Iterator(CircularDoublyLinkedList* list);             // Инициализация итератора

int has_Next(ListIterator* it);                                         // Проверка наличия следующего элемента
int Next(ListIterator* it);                                             // Получение следующего элемента
int Prev(ListIterator* it);                                             // Получение предыдущего элемента (для двусвязного списка)

int get_Current(const ListIterator* it);                                // Итератор только для чтения (Не позволяет изменять элементы)
void set_Current(ListIterator* it, int new_data);                       // Итератор с изменением данных
void delete_Current(CircularDoublyLinkedList* list, ListIterator* it);  // Итератор с удалением текущего элемента



int main() {
    CircularDoublyLinkedList list;
    init_List(&list);

    add_Last(&list, 10);
    add_Last(&list, 20);
    add_Last(&list, 30);  // Список: 10 -> 20 -> 30 -> (head)

    // Инициализация итератора
    ListIterator it = init_Iterator(&list);

    // Перебор в прямом порядке
    printf("Direct bypass:\n");
    while (has_Next(&it)) {
        printf("%d\n", Next(&it));  // 10, 20, 30
    }

    // Перебор в обратном порядке (если нужно)
    it = init_Iterator(&list);
    it.current = it.start->prev;  // Начинаем с хвоста

    printf("Reverse detour:\n");
    for (int i = 0; i < list.size; i++) {
        printf("%d\n", Prev(&it));  // 30, 20, 10
    }

    return 0;
}







ListIterator init_Iterator(CircularDoublyLinkedList* list) {
    ListIterator it;
    it.current = list->head;
    it.start = list->head;
    it.is_first = 1;  // Первый элемент ещё не взят
    return it;
}



int has_Next(ListIterator* it) {
    if (it->current == NULL) {
        return 0;  // Список пуст
    }
    return (it->is_first) || (it->current != it->start);
}

int Next(ListIterator* it) {
    if (!has_Next(it)) {
        fprintf(stderr, "The end of the list has been reached\n");
        exit(1);
    }
    
    int data = it->current->data;
    it->current = it->current->next;
    it->is_first = 0;  // Следующие элементы уже не первые
    
    return data;
}

int Prev(ListIterator* it) {
    if (it->current == NULL || (it->current == it->start && !it->is_first)) {
        fprintf(stderr, "The beginning of the list has been reached\n");
        exit(1);
    }
    
    it->current = it->current->prev;
    int data = it->current->data;
    it->is_first = 0;
    
    return data;
}



int get_Current(const ListIterator* it) {
    return it->current->data;
}

void set_Current(ListIterator* it, int new_data) {
    it->current->data = new_data;
    return;
}

void delete_Current(CircularDoublyLinkedList* list, ListIterator* it) {
    if (it->current == NULL) return;

    Node* to_delete = it->current;
    it->current = it->current->next;

    if (to_delete == list->head)
        delete_First(list);
    else {
        to_delete->prev->next = to_delete->next;
        to_delete->next->prev = to_delete->prev;
        free(to_delete);
        list->size--;
    }
    return;
}