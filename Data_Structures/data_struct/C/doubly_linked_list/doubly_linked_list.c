#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;               // Данные
    struct Node* next;      // Указатель на следующий узел
    struct Node* prev;      // Указатель на предыдущий узел
} Node;


typedef struct {
    Node* head;
    Node* tail;
    int size;
} DoublyLinkedList;




void init_List(DoublyLinkedList* list);     // Инициализация списка
Node* create_Node(int data);                //Создание нового узла

void add_First(DoublyLinkedList* list, int data);       // В начало списка (O(1))
void add_Last(DoublyLinkedList* list, int data);        // В конец списка (O(1))
void add_At_Index(DoublyLinkedList* list, int data, int index);     // По индексу

void delete_First(DoublyLinkedList* list);                          // Удаление первого элемента 
void delete_Last(DoublyLinkedList* list);                           // Удаление последнего элемента 
void delete_At_Index(DoublyLinkedList* list, int index);            // Удаление по индексу


int get_At_Index(DoublyLinkedList* list, int index);                // Получение элемента по индексу


void print_Forward(DoublyLinkedList* list);                         // Печать списка в прямом
void print_Backward(DoublyLinkedList* list);                        // Печать списка в обратном порядке



int main(void){
    DoublyLinkedList list;
    init_List(&list);

    add_First(&list, 10);
    add_Last(&list, 20);
    add_At_Index(&list, 15, 1);

    printf("Printing in direct order:\n");
    print_Forward(&list);

    printf("Printing in reverse order:\n");
    print_Backward(&list);

    delete_At_Index(&list, 1);
    print_Forward(&list);

    return 0;
}


void init_List(DoublyLinkedList* list){
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
    new_node->prev = NULL;

    return new_node;
}


void add_First(DoublyLinkedList* list, int data){
    Node* new_node = create_Node(data);

    if (list->head == NULL){
        list->head = new_node;
        list->tail = new_node;
    }
    else {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
    list->size++;
    
    return;
}

void add_Last(DoublyLinkedList* list, int data){
    Node* new_node = create_Node(data);

    if (list->tail == NULL){
        list->head = new_node;
        list->tail = new_node;
    }
    else{
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
    
    return;
}

void add_At_Index(DoublyLinkedList* list, int data, int index){
    if (index < 0 || index > list->size) {
        fprintf(stderr, "Incorrect index\n");
        return;
    }
    
    if (index == 0)
        add_First(list, data);
    else if (index == list->size)
        add_Last(list, data);
    else{
        Node* new_node = create_Node(data);
        Node* current;

        if (index <= list->size / 2){
            current = list->head;
            for (int i = 0; i < index - 1; i++)
                current = current->next;
        }
        else{
            current = list->tail;
            for (int i = list->size; i > index - 1; i--)
                current = current->prev;
        }
        new_node->next = current->next;
        new_node->prev = current;
        current->next->prev = new_node;
        current->next = new_node;

        list->size++;
    }

    return;
}




void delete_First(DoublyLinkedList* list){
    if (list->head == NULL) {
        fprintf(stderr, "The list is empty\n");
        return;
    }

    Node* temp = list->head;
    list->head = list->head->next;

    if (list->head == NULL) // Если список стал пустым
        list->tail = NULL;
    else 
        list->head->prev = NULL;

    free(temp);
    list->size--;
    
}

void delete_Last(DoublyLinkedList* list){
    if (list->head == NULL) {
        fprintf(stderr, "The list is empty\n");
        return;
    }

    Node* temp = list->tail;
    list->tail = list->tail->prev;

    if (list->tail == NULL) // Если список стал пустым
        list->head = NULL;
    else
        list->tail->next = NULL;

    free(temp);
    list->size--;
} 

void delete_At_Index(DoublyLinkedList* list, int index){
    if (index < 0 || index > list->size) {
        fprintf(stderr, "Incorrect index\n");
        return;
    }

    if (index == 0)
        delete_First(list);
    else if (index == list->size - 1)
        delete_Last(list);
    else{

        Node* current;

        if (index <= list->size / 2){
            current = list->head;
            for (int i = 0; i < index; i++)
                current = current->next;
        }
        else{
            current = list->tail;
            for (int i = list->size - 1; i > index; i--)
                current = current->prev;
        }
        
        current->prev->next = current->next;
        current->next->prev = current->prev;

        free(current);
        list->size--;
    }

    return;
}



int get_At_Index(DoublyLinkedList* list, int index){
    if (index < 0 || index > list->size) {
        fprintf(stderr, "Incorrect index\n");
        exit(1);
    }

    Node* current;

    if (index <= list->size / 2){
            current = list->head;
            for (int i = 0; i < index; i++)
                current = current->next;
        }
        else{
            current = list->tail;
            for (int i = list->size - 1; i > index; i--)
                current = current->prev;
        }
    
    return current->data;
}



void print_Forward(DoublyLinkedList* list){
    Node* current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
    return;
}

void print_Backward(DoublyLinkedList* list){
    Node* current = list->tail;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->prev;
    }
    printf("NULL\n");
    return;
} 