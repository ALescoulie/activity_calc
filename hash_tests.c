//
// Created by Alia Lescoulie on 12/23/21.
//

#include <assert.h>
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

void test_table_remove1() {
    HashTable *table = table_create(10);
    table_remove(table, "H");
    table_add(table, 1.011, "H");
    table_remove(table, "He");
    table_destroy(table);
}

void test_collision() {
    int code1[] = {1, 0};
    int code2[] = {11, 0};
    int code3[] = {21, 0};
    char* str1 = (char*)code1;
    char* str2 = (char*)code2;
    char* str3 = (char*)code3;
    HashTable *table = table_create(10);
    table_add(table, 1.011, str1);
    table_add(table, 4.00, str2);
    table_add(table, 6.94, str3);
    assert(table_get(table, str1) == 1.011);
    assert(table_get(table, str2) == 4.00);
    assert(table_get(table, str3) == 6.94);
    table_remove(table, str3);
    table_remove(table, str3);
    table_remove(table, str2);
    assert(table->size == 1);
    assert(table_get(table, str1) == 1.011);
    assert(table_get(table, str2) == 1);
    table_destroy(table);
}


int main() {
    test_table_create();
    test_add_get0();
    test_add_get1();
    test_table_expand();
    test_table_remove();
    test_collision();
    test_table_remove1();
    return 0;
}
