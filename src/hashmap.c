// A hashmap (or hash table) in C is typically implemented using an array of linked lists, where each array index represents a "bucket." 
// The key is processed by a hash function to determine which bucket it belongs to. 
// Collisions (multiple keys hashing to the same bucket) are handled by storing the key-value pairs in a linked list at that bucket.
// Here's a simplified example of a hashmap implementation in C using separate chaining for collision resolution: 
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Structure for a key-value pair node in the linked list
typedef struct Node {
    char* key;
    char* value;
    struct Node* next;
} Node;

// Structure for the hash map
typedef struct HashMap {
    Node* table[TABLE_SIZE];
} HashMap;

// Simple hash function (for demonstration)
unsigned int hash(const char* key) {
    unsigned int hash_val = 0;
    while (*key != '\0') {
        hash_val = (hash_val * 31) + (*key); // Simple polynomial rolling hash
        key++;
    }
    return hash_val % TABLE_SIZE;
}

// Function to create a new node
Node* create_node(const char* key, const char* value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    // new_node->key = strdup(key); // Duplicate key string
    // new_node->value = strdup(value); // Duplicate value string
    new_node->next = NULL;
    return new_node;
}

// Function to initialize the hash map
void init_hash_map(HashMap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i] = NULL;
    }
}

// Function to insert a key-value pair into the hash map
void insert(HashMap* map, const char* key, const char* value) {
    unsigned int index = hash(key);
    Node* new_node = create_node(key, value);

    // If bucket is empty, add the new node
    if (map->table[index] == NULL) {
        map->table[index] = new_node;
    } else {
        // Traverse the linked list to handle collisions (separate chaining)
        Node* current = map->table[index];
        while (current != NULL) {
            // If key already exists, update its value
            if (strcmp(current->key, key) == 0) {
                free(current->value); // Free old value
            //    current->value = strdup(value); // Update with new value
                free(new_node->key); // Free unused key from new_node
                free(new_node->value); // Free unused value from new_node
                free(new_node); // Free the new_node itself
                return;
            }
            if (current->next == NULL) {
                break; // Reached end of list
            }
            current = current->next;
        }
        current->next = new_node; // Add to end of list
    }
}

// Function to retrieve a value from the hash map
char* get(HashMap* map, const char* key) {
    unsigned int index = hash(key);
    Node* current = map->table[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL; // Key not found
}

// Function to free memory used by the hash map
void free_hash_map(HashMap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = map->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
}

int main() {
    HashMap my_map;
    init_hash_map(&my_map);

    insert(&my_map, "apple", "red");
    insert(&my_map, "banana", "yellow");
    insert(&my_map, "grape", "purple");
    insert(&my_map, "apple", "green"); // Update value for "apple"

    printf("Value of apple: %s\n", get(&my_map, "apple"));
    printf("Value of banana: %s\n", get(&my_map, "banana"));
    printf("Value of grape: %s\n", get(&my_map, "grape"));
    printf("Value of orange: %s\n", get(&my_map, "orange")); // Key not found

    free_hash_map(&my_map); // Clean up memory

    return 0;
}
