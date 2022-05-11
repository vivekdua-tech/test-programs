//
//  hashmap.c
//  test-Programs
//
//  Created by vidua on 2/29/20.
//  Copyright © 2020 Vivek Dua. All rights reserved.
//

#include <stdio.h>

#if 0

typedef struct {
    
    int size;
    int max;
    
    // element stored is in void *
    void **contents;
    
} darray;



darray *darray_create(size_t element_size, int initial_max);
int    darray_push   (darray *array, void *element);
void  *darray_pop    (darray *array);
void  *darray_get    (darray *array, int i);
void  *darray_remove (darray *array);

darray *darray_create(size_t elem_size, size_t initial_max) {
    darray *array = malloc(sizeof(darray));
    
    array->max = initial_max;
    array->contents = calloc(initial_max, sizeof(void *));
    array->element_size = elem_size;
    return array;
    
error:
    if (array) {
        free(array);
    }
    return NULL;
}

int darray_push(darray *array, void *el) {
    array->contents[array->end] = el;
    array->end++;
    
    if (darray_end(array) >= darray_max(array)) {
        return darray_expand(array);
    } else {
        return 0;
    }
}

void *darray_pop(darray *array) {
    
    


    
}



typedef int (*hashmap_compare) (void *a, void *b);
typedef int (*hashmap_hash) (void *key);


typedef struct {
    darray *buckets; // darray of buckets and each bucket is a darray of hashmapnodes
    hashmap_hash hash;
    hashmap_compare compare;
} hashmap;

typedef struct {
    void *key;
    void *data;
    uint32_t hash;
} hashmap_node;


typedef int (*hashmap_traverse_cb)(hashmap_node *node);


hashmap *hashmap_create(hashmap_compare compare,
                        hashmap_hash    hash_fn);
void hashmap_destroy(hashmap *map);
int  hashmap_set(hashmap *map, void *key, void *data);
void *hashmap_get(hashmap *map, void *key);
void *hashmap_delete(hashmap *map, void *key);



int hashmap_set (hashmap *map, void *key, void *data) {
    
    uint32_t hash = hash_key(void *data);
    int bucket = hash % DEFAULT_NUM_OF_BUCKETS;
    darray *bucket = darray_get(map->buckets, bucket_n);
    hashmap_node *node = calloc(1, sizeof(hashmap_node));
    node->key = key;
    node->data = data;
    darray_push(bucket, node);
    return 0;
}







int default_compare(void *a, void *b) {
    return 1;
}

int default_hash(void *a) {
    return 1;
}


// bucket[0] - darray* - array of hashmap_node
// bucket[1] - darray* - array of hashmap_node
// ..
// bucket[DEFAULT_NUM_BUCKETS - 1] - darray*


hashmap *hashmap_create(hashmap_compare compare_fn, hashmap_hash hash_fn) {
    
    hashmap *map = calloc(1, sizeof(hashmap));
    assert(map);
    map->compare = compare_fn == NULL ? default_compare : compare_fn;
    map->hash = hash_fn == NULL ? default_hash : hash_fn;
    map->buckets = darray_create(sizeof(darray*), 100);
    return map;
    
error:
    if (map) {
        hashmap_destroy(map);
    }
    return NULL;
}

#endif

int main() {
    
    int **temp = NULL;
    
    temp = (int **) calloc(sizeof(int *), 10);
    for (int i = 0; i < 10; i++) {
        temp[i] = calloc(sizeof(int), 10);
    }
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            temp[i][j] = 1;
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf(" %d", temp[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < 10; i++) {
        temp[i] = realloc(temp[i], 15 * sizeof(int));
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++) {
            printf(" %d", temp[i][j]);
        }
        printf("\n");
    }
    return 0;
}


















