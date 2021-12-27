//
// Created by Alia Lescoulie on 12/22/21.
//

#include <stdlib.h>
#include <string.h>
#include "hash.h"

HashTable *table_create(unsigned int capacity) {
    int i;
    HashNode *data = malloc(sizeof(HashNode) * capacity);
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));

    for (i = 0; capacity > i; i++) {
        data[i].key = 0;
    }

    table->data = data;
    table->size = 0;
    table->capacity = capacity;
    return table;
}

double get_load_factor(unsigned int size, unsigned int capacity) {
    return (double)size / (double)capacity;
}

int get_hash(char *key) {
    int len = strlen(key);
    unsigned int hash = 0;
    unsigned int i;

    for (i = 0; len > i; i++) {
        hash = hash * 31 + *(key + i);
    }

    return hash;
}

void table_add(HashTable *table, double value, char *key) {
    int hash = get_hash(key);
    double load = get_load_factor(table->size + 1, table->capacity);
    int i = 1;
    if (load > 0.7) {
        table_expand(table);
        table_add(table, value, key);
    }
    if (table->data[hash % table->capacity].key == 0 || table->data[hash % table->capacity].key == key) {
        table->data[hash % table->capacity].key = key;
        table->data[hash % table->capacity].value = value;
        table->size += 1;
    } else {
        while (table->data[(hash + i) % table->capacity].key != 0) {
            i = (i + 1) * (i + 1);
        }
        table->data[(hash + i) % table->capacity].key = key;
        table->data[(hash + i) % table->capacity].value = value;
        table->size += 1;
    }
}

void table_expand(HashTable* table) {
    HashTable *new_table = table_create((table->capacity * 2) + 1);
    int i;
    for (i = 0; table->capacity > i; i++) {
        if (table->data[i].key != 0) {
            table_add(new_table, table->data[i].value, table->data[i].key);
        }
    }
    table_destroy(table);
    *table = *new_table;
}

int table_remove(HashTable* table, char* key) {
    int i = 1;
    int x = 0;
    int hash = get_hash(key);
    if (table->data[hash % table->capacity].key == key) {
        table->data[hash % table->capacity].key = 0;
        table->size -= 1;
        return 0;
    } else if (table->data[hash % table->capacity].key != 0) {
        while (table->data[(hash + i) % table->capacity].key != key && x < table->capacity) {
            i = (i + 1) * (i + 1);
            x++;
        }
        if (table->data[(hash + i) % table->capacity].key == key) {
            table->data[(hash + i) % table->capacity].key = 0;
            table->size -= 1;
            return 0;
        } else {
            return 1;
        }
    } else {
        return 1;
    }
}

double table_get(HashTable* table, char* key) {
    int i = 1;
    int x = 0;
    int hash = get_hash(key);
    if (table->data[hash % table->capacity].key == key) {
        return table->data[hash % table->capacity].value;
    } else if (table->data[hash % table->capacity].key != 0) {
        while (table->data[(hash + i) % table->capacity].key != key && x < table->capacity) {
            i = (i + 1) * (i + 1);
            x++;
        }
        if (table->data[(hash + i) % table->capacity].key == key) {
            return table->data[(hash + i) % table->capacity].value;
        } else {
            return 1;
        }
    } else {
        return 1;
    }
}

void *table_destroy(HashTable* table) {
    free(table->data);
    free(table);
    return (void*)table;
}
