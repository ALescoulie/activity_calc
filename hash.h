//
// Created by Alia Lescoulie on 12/22/21.
//

typedef struct HashNode {
    char* key;
    double value;
} HashNode;

typedef struct HashTable {
    HashNode* data;
    unsigned int size;
    unsigned int capacity;
} HashTable;


HashTable *table_create(unsigned int);
double get_load_factor(unsigned int, unsigned int);
int get_hash(char*);
void table_add(HashTable *, double, char*);
void table_expand(HashTable *);
int table_remove(HashTable *, char*);
double table_get(HashTable *, char*);
void *table_destroy(HashTable *);
