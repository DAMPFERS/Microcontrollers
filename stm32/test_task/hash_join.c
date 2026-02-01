#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


// Структура для строки таблицы
typedef struct Row {
    int a;
    int b;
    struct Row* next; // Для обработки коллизий
} Row;


// Структура для хэш-таблицы
typedef struct HashTable {
    Row** buckets;  // Массив bucket'ов
    int size;       // Количество bucket'ов
} HashTable;


uint16_t hash(int key, int size);


HashTable* create_Table(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->buckets = (Row**)calloc(size, sizeof(Row*));
    return table;
}


// Добавление строки в хэш-таблицу
void insert_Row(HashTable* table, Row* row) {
    uint16_t index = hash(row->a, table->size);
    // Обработка коллизий: добавляем в начало списка
    row->next = table->buckets[index];
    table->buckets[index] = row;
}


// Построение хэш-таблицы для t2
HashTable* buid_HashTable(Row* t2, int t2_size) {
    HashTable* table = create_Table((int)(1 << 14));
    for (int i = 0; i < t2_size; i++) {
        Row* new_row = (Row*)malloc(sizeof(Row));
        new_row->a = t2[i].a;
        new_row->b = t2[i].b;
        new_row->next = NULL;
        insert_Row(table, new_row);
    }
    return table;
}



// Сканирование t1 и выполнение Hash Join
void hash_Join(Row* t1, int t1_size, HashTable* t2_table) {
    for (int i = 0; i < t1_size; i++) {
        uint16_t index = hash(t1[i].a, t2_table->size);
        Row* currrent = t2_table->buckets[index];
        while (currrent != NULL) {
            if (currrent->a == t1[i].a) {
                printf("t1: a=%d, b=%d | t2: a=%d, b=%d\n",
                    t1[i].a, t1[i].b, currrent->a, currrent->b);
            }
            currrent = currrent->next;
        }
        
    }
}

// Генерация тестовых данных 
void gen_Table(Row* t1, Row* t2, int size) {
    for (int i = 0; i < size; i++) {
        t1[i].a = i + 1;
        t1[i].b = (i + 1) % 100;
        t2[i].a = i + 1;
        t2[i].b = (i + 1) % 100;
    }
}





int main(void) {
    
    const int size = 10000;
    Row t1[size], t2[size];

    gen_Table(t1, t2, size);
    HashTable* t2_table = buid_HashTable(t2, size);

    hash_Join(t1, size, t2_table);

    for (int i = 0; i < t2_table->size; i++) {
        Row* current = t2_table->buckets[i];
        while (current != NULL) {
            Row* temp = current;
            current = current->next;
            free(temp);
        }
        
    }
    free(t2_table->buckets);
    free(t2_table);

    return 0;
}







uint16_t hash(int key, int size) {
    return key % size;
}
