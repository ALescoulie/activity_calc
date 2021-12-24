//
// Created by Alia Lescoulie on 12/23/21.
//

#include <assert.h>
#include <AppleTextureEncoder.h>
#include "hash.h"

void test_table_create() {
    int i;
    HashTable *table = table_create(10);

    for (i = 0; table->capacity > i; i++) {
        assert(table->data[i].key == 0);
    }

    assert(table->capacity == 10);
    table_destroy(table);
}

void test_add_get0() {
    HashTable *table = table_create(10);
    table_add(table, 1.011, "H");
    assert(get_load_factor(table->size, table->capacity) == 0.1);
    assert(table_get(table, "H") == 1.011);
    table_destroy(table);
}

void test_add_get1() {
    HashTable *table = table_create(10);
    table_add(table, 1.011, "H");
    assert(get_load_factor(table->size, table->capacity) == 0.1);
    assert(table_get(table, "H") == 1.011);
    assert(table_get(table, "C") == 1);
    table_destroy(table);
}

void test_table_expand() {
    HashTable *table = table_create(2);
    table_add(table, 1.011, "H");
    table_add(table, 4.00, "He");
    assert(table->capacity == 5);
    assert(table_get(table, "H") == 1.011);
    assert(table_get(table, "He") == 4.00);
    table_destroy(table);
}

void test_table_remove() {
    HashTable *table = table_create(10);
    table_add(table, 1.011, "H");
    table_add(table, 4.00, "He");
    table_remove(table, "He");
    assert(table_get(table, "H") == 1.011);
    assert(table_get(table, "He") == 1);
    table_destroy(table);
}

int main() {
    test_table_create();
    test_add_get0();
    test_add_get1();
    test_table_expand();
    test_table_remove();
    return 0;
}
