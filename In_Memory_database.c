#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int TABLE_SIZE = 16;

struct member {
    int key;
    int value;
};

// simple modulo hash function
int hash(int val) {
    return val % TABLE_SIZE;
}

// INSERT or UPDATE (SET)
int insert(struct member **space, int *space_size, int key, int val) {
    int position = hash(key);
    int list_size = space_size[position];
    struct member *list = space[position];

    // check if key already exists → update
    for (int i = 0; i < list_size; i++) {
        if (list[i].key == key) {
            list[i].value = val;
            return 1; // updated
        }
    }

    // else insert into empty slot
    for (int i = 0; i < list_size; i++) {
        if (list[i].key <= 0) {  // empty slot
            list[i].key = key;
            list[i].value = val;
            return 0; // inserted
        }
    }
    return -1; // no space
}

// RETRIEVE (GET)
int retrieve(struct member **space, int *space_size, int key) {
    int hashed_value = hash(key);
    for (int i = 0; i < space_size[hashed_value]; i++) {
        if (space[hashed_value][i].key == key) {
            return space[hashed_value][i].value;
        }
    }
    return -1; // not found
}

// DELETE (DEL)
int delete_key(struct member **space, int *space_size, int key) {
    int hashed_value = hash(key);
    for (int i = 0; i < space_size[hashed_value]; i++) {
        if (space[hashed_value][i].key == key) {
            space[hashed_value][i].key = -1;
            space[hashed_value][i].value = -1;
            return 1; // deleted
        }
    }
    return 0; // not found
}

// EXISTS
int exists(struct member **space, int *space_size, int key) {
    int hashed_value = hash(key);
    for (int i = 0; i < space_size[hashed_value]; i++) {
        if (space[hashed_value][i].key == key) {
            return 1;
        }
    }
    return 0;
}

// Initialize table
struct member ** init() {
    struct member ** space;
    space = (struct member **) malloc(TABLE_SIZE * sizeof(struct member *));
    return space;
}

// Initialize lists
int * init_list(struct member **space) {
    int * space_size;
    space_size = (int *) malloc(TABLE_SIZE * sizeof(int));
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct member* list;
        list = (struct member *) malloc(2 * sizeof(struct member));
        for (int j = 0; j < 2; j++) {
            list[j].key = -1;
            list[j].value = -1;
        }
        space[i] = list;
        space_size[i] = 2;
    }
    return space_size;
}

int main() {
    struct member ** space = init();
    int * space_size = init_list(space);

    // Insert
    insert(space, space_size, 110, 1);
    insert(space, space_size, 126, 2);

    // Retrieve
    printf("GET 110 => %d\n", retrieve(space, space_size, 110));
    printf("GET 126 => %d\n", retrieve(space, space_size, 126));

    // Exists
    printf("EXISTS 110 => %d\n", exists(space, space_size, 110));
    printf("EXISTS 500 => %d\n", exists(space, space_size, 500));

    // Delete
    printf("DEL 110 => %d\n", delete_key(space, space_size, 110));
    printf("GET 110 => %d\n", retrieve(space, space_size, 110));
    printf("EXISTS 110 => %d\n", exists(space, space_size, 110));

    return 0;
}
