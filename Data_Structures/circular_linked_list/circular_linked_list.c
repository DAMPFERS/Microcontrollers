#include <stdio.h>
#include <stdlib.h>
#include "circular_linked_list.h"


// int main(void){
//     CircularDoublyLinkedList list;
//     init_List(&list);

//     add_First(&list, 10);    // 10 -> (head)
//     add_Last(&list, 20);     // 10 -> 20 -> (head)
//     add_At_Index(&list, 15, 1);  // 10 -> 15 -> 20 -> (head)

//     printf("List: ");
//     print_List(&list);  // 10 -> 15 -> 20 -> (head)

//     delete_First(&list);  // 15 -> 20 -> (head)
//     delete_Last(&list);   // 15 -> (head)

//     printf("After the deletions.: ");
//     print_List(&list);  // 15 -> (head)
    
//     return 0;
// }




void init_List(CircularDoublyLinkedList* list){
    list->head = NULL;
    list->size = 0;
}



Node* create_Node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;  // Временно
    new_node->prev = NULL;  // Временно
    return new_node;
}



void add_To_Empty(CircularDoublyLinkedList* list, int data) {
    Node* new_node = create_Node(data);
    new_node->next = new_node;  // Ссылка на себя
    new_node->prev = new_node;  // Ссылка на себя
    list->head = new_node;
    list->size++;
}

void add_First(CircularDoublyLinkedList* list, int data) {
    if (list->head == NULL) {
        add_To_Empty(list, data);
        return;
    }
    
    Node* new_node = create_Node(data);
    Node* tail = list->head->prev;  // Хвост = head->prev
    
    new_node->next = list->head;
    new_node->prev = tail;
    
    list->head->prev = new_node;
    tail->next = new_node;
    
    list->head = new_node;  // Обновляем голову
    list->size++;
}

void add_Last(CircularDoublyLinkedList* list, int data) {
    if (list->head == NULL) {
        add_To_Empty(list, data);
        return;
    }
    
    Node* new_node = create_Node(data);
    Node* tail = list->head->prev;  // Хвост = head->prev
    
    new_node->next = list->head;
    new_node->prev = tail;
    
    tail->next = new_node;
    list->head->prev = new_node;
    
    list->size++;
}

void add_At_Index(CircularDoublyLinkedList* list, int data, int index) {
    if (index < 0 || index > list->size) {
        fprintf(stderr, "Incorrect index\n");
        return;
    }
    
    if (index == 0) 
        add_First(list, data);
    else if (index == list->size)
        add_Last(list, data);
    else {
        Node* new_node = create_Node(data);
        Node* current = list->head;
        
        // Идём до узла перед нужным индексом
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        
        new_node->next = current->next;
        new_node->prev = current;
        
        current->next->prev = new_node;
        current->next = new_node;
        
        list->size++;
    }
}



void delete_Only_Node(CircularDoublyLinkedList* list) {
    free(list->head);
    list->head = NULL;
    list->size = 0;
}

void delete_First(CircularDoublyLinkedList* list){
    if (list->head == NULL) {
        fprintf(stderr, "The list is empty\n");
        return;
    }
    
    if (list->size == 1) {
        delete_Only_Node(list);
        return;
    }
    
    Node* temp = list->head;
    Node* tail = list->head->prev;
    
    list->head = list->head->next;  // Сдвигаем голову
    list->head->prev = tail;
    tail->next = list->head;
    
    free(temp);
    list->size--;
}

void delete_Last(CircularDoublyLinkedList* list) {
    if (list->head == NULL) {
        fprintf(stderr, "The list is empty\n");
        return;
    }
    
    if (list->size == 1) {
        delete_Only_Node(list);
        return;
    }
    
    Node* tail = list->head->prev;
    Node* new_tail = tail->prev;
    
    new_tail->next = list->head;
    list->head->prev = new_tail;
    
    free(tail);
    list->size--;
}

void delete_At_Index(CircularDoublyLinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Incorrect index\n");
        return;
    }
    
    if (index == 0)
        delete_First(list);
    else if (index == list->size - 1)
        delete_Last(list);
    else {
        Node* current = list->head;
        
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        
        current->prev->next = current->next;
        current->next->prev = current->prev;
        
        free(current);
        list->size--;
    }
}



int get_At_Index(CircularDoublyLinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Incorrect index\n");
        exit(1);
    }
    
    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    
    return current->data;
}



void print_List(CircularDoublyLinkedList* list) {
    if (list->head == NULL) {
        printf("NULL\n");
        return;
    }
    
    Node* current = list->head;
    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != list->head);  // Пока не вернёмся к голове
    
    printf("(head)\n");  // Обозначаем закольцованность
}