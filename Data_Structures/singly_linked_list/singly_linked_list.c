#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Node
{
    int data;               // Данные узла
    struct Node* next;      // Указатель на следующий узел
} Node;


// Сам список (с головой, хвостом и длиной)
typedef struct {
    Node* head; // Первый элемент
    Node* tail; // Последний элемент
    int size;   // Количество элементов
} LinkedList;


void init_List(LinkedList* list);           // Инициализация списка

Node* create_Node(int data);                // Создание нового узла

int get_Size(LinkedList* list);             // Получение длины списка


void add_First(Node** head, int data);      // Добавление элементов В начало списка
void add_First_to_List(LinkedList* list, int data);      // Добавление элементов В начало списка

void add_Last(Node** head, int data);       // Добавление элементов В конец  списка
void add_Last_to_List(LinkedList* list, int data);  // Добавление элементов В конец  списка

void add_At_Index(Node** head, int data, int index);      // Добавление элементов По индексу списка
void add_At_Index_to_List(LinkedList* list, int data, int index);      // Добавление элементов По индексу списка


void delete_First_to_List(LinkedList* list);                // Удаление первого элемента
void delete_Last_to_List(LinkedList* list);                 // Удаление последнего  элемента
void delete_By_Value(Node** head, int data);                // Удаление элементов По значению
void delete_By_Index(Node** head, int index);               // Удаление элементов По индексу
void delete_By_Index_to_List(LinkedList* list, int index);  // Удаление элементов По индексу

int get_At_Index(Node* head, int index);       // Получение элемента по индексу
int get_At_Index_to_List(LinkedList* list, int index);       // Получение элемента по индексу

void print_List(Node* head);                   // Печать списка
void print_List_to_List(LinkedList* list);                   // Печать списка



int main(void){

    Node* head = NULL;

    add_First(&head, 10);    // 10 -> NULL
    add_Last(&head, 20);     // 10 -> 20 -> NULL
    add_At_Index(&head, 15, 1); // 10 -> 15 -> 20 -> NULL

    printf("Элемент по индексу 1: %d\n", get_At_Index(head, 1)); // 15

    delete_By_Value(&head, 15); // 10 -> 20 -> NULL
    delete_By_Index(&head, 0);  // 20 -> NULL

    print_List(head); // 20 -> NULL



    LinkedList list;
    init_List(&list);

    add_First_to_List(&list, 10);
    add_Last_to_List(&list, 20);
    add_At_Index_to_List(&list, 15, 1);
    print_List_to_List(&list);

    printf("Element at index 1: %d\n", get_At_Index_to_List(&list, 1));
    printf("Size list: %d\n", get_Size(&list));

    delete_First_to_List(&list);
    delete_Last_to_List(&list);
    delete_By_Index_to_List(&list, 0);

    print_List_to_List(&list);

    return 0;
}



void init_List(LinkedList* list){
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return;
}


Node* create_Node(int data){
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node){
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}


int get_Size(LinkedList* list){
    return list->size;
}


void add_First(Node** head, int data){
    Node* new_node = create_Node(data);
    new_node->next = *head;
    *head = new_node;

    return;
}

void add_First_to_List(LinkedList* list, int data){
    Node* new_node = create_Node(data);
    new_node->next = list->head;
    list->head = new_node;
    if (list->tail == NULL) list->tail = new_node;
    
    list->size++;

    return;
}



void add_Last(Node** head, int data){
    // O(N)
    Node* new_node = create_Node(data);
    if (*head == NULL){
        *head = new_node;
        return;
    }
    Node* current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;
    return;
}

void add_Last_to_List(LinkedList* list, int data){
    // O(1), благодаря tail
    Node* new_node = create_Node(data);
    if (list->tail == NULL){
        list->head = new_node;
        list->tail = new_node;
    }
    else{
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;

    return;
}



void add_At_Index(Node** head, int data, int index){
    if (index < 0){
        fprintf(stderr, "The index can't be negative.\n");
        return;
    }
    if (index == 0){
        add_First(head, data);
        return;
    }
    Node* new_node = create_Node(data);
    Node* current = *head;
    for (int i = 0; current != NULL && i < index - 1; i++)
        current = current->next;
    if (current == NULL){
        fprintf(stderr, "Index off list\n");
        free(new_node);
        return;
    }
    new_node->next = current->next;
    current->next = new_node;

    return;
}

void add_At_Index_to_List(LinkedList* list, int data, int index){
    if (index < 0 || index > list->size){
        fprintf(stderr, "Incorrect index\n");
        return;
    }

    if (index == 0)
        add_First_to_List(list, data);       
    else if (index == list->size)
        add_Last_to_List(list, data);
    else{
        Node* new_node = create_Node(data);
        Node* current = list->head;

        for (int i = 0; i < index - 1; i++)
            current = current->next;

        new_node->next = current->next;
        current->next = new_node;
        list->size++;
    }
    
}


void delete_First_to_List(LinkedList* list){
    if (list->head == NULL) {
        fprintf(stderr, "The list is empty\n");
        return;
    }
    
    Node* temp = list->head;
    list->head = list->head->next;
    
    if (list->head == NULL) {  // Если список стал пустым
        list->tail = NULL;
    }
    
    free(temp);
    list->size--;

    return;
}

void delete_Last_to_List(LinkedList* list){
    if (list->head == NULL) {
        fprintf(stderr, "The list is empty\n");
        return;
    }
    
    if (list->head == list->tail) {  // Если в списке 1 элемент
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    } else {
        Node* current = list->head;
        while (current->next != list->tail) {
            current = current->next;
        }
        
        free(list->tail);
        current->next = NULL;
        list->tail = current;
    }
    
    list->size--;

    return;
}

void delete_By_Value(Node** head, int data){
    Node *temp = *head, *prev = NULL;
    if (temp != NULL && temp->data == data){
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != data){
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL){
        printf("Element not found");
        return;
    }
    prev->next = temp->next;
    free(temp);
    
    return;
}

void delete_By_Index(Node** head, int index){
    if (*head == NULL || index < 0){
        fprintf(stderr, "The list is empty or the index is incorrect\n");
        return;
    }
    Node* temp = *head;
    if(index == 0){
        *head = temp->next;
        free(temp);
        return;
    }

    for (int i = 0; temp != NULL && i < index - 1; i++)
        temp = temp->next;
    if (temp == NULL || temp->next == NULL){
        fprintf(stderr, "Index off list\n");
        return;
    }
    Node* next_node = temp->next->next;
    free(temp->next);
    temp->next = next_node;

    return;
}

void delete_By_Index_to_List(LinkedList* list, int index){
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Incorrect index\n");
        return;
    }
    
    if (index == 0) {
        delete_First_to_List(list);
    } else if (index == list->size - 1) {
        delete_Last_to_List(list);
    } else {
        Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        
        Node* temp = current->next;
        current->next = temp->next;
        free(temp);
        list->size--;
    }

    return;
}


int get_At_Index(Node* head, int index){
    Node* current = head;
    for (int i = 0; current != NULL && i < index; i++)
        current = current->next;
    
    if (current == NULL){
        fprintf(stderr, "Index off list\n");
        exit(1);
    }
    return current->data;
}

int get_At_Index_to_List(LinkedList* list, int index){
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


void print_List(Node* head){
    Node* current = head;
    while (current != NULL){
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
    return;
}

void print_List_to_List(LinkedList* list){
   Node* current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n"); 
}