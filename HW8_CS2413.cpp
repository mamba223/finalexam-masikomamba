#include <iostream>
using namespace std;

// Define a Node class to represent elements in the hash table
class Node {
private:
    int key;         // Key of the node
    int idx_next;    // Index of the next node in the chain

public:
    void Set_key(int x);      // Set the key of the node
    int Get_key();            // Get the key of the node
    void Set_index(int x);    // Set the index of the next node
    int Get_index();          // Get the index of the next node
    Node();                   // Constructor for the Node class
};

// Node constructor initializes key and idx_next to -1
Node::Node() {
    key = -1;
    idx_next = -1;
}

// Set the key value of the node
void Node::Set_key(int x) {
    key = x;
}

// Get the key value of the node
int Node::Get_key() {
    return key;
}

// Set the index of the next node in the chain
void Node::Set_index(int x) {
    idx_next = x;
}

// Get the index of the next node in the chain
int Node::Get_index() {
    return idx_next;
}

// Define a HashTable class to manage the hash table
class HashTable {
private:
    int size;       // Size of the hash table
    Node* table;    // Array to store the nodes

    int hash(int key);           // Hash function to determine the index
    void resizeAndRehash();      // Function to resize the table and rehash

public:
    void CreateTable(int divisor);  // Create the hash table with a given divisor
    int Search(int key);           // Search for a key in the table
    void Add(Node temp);           // Add an element to the table
    void Remove(int key);          // Remove an element from the table
    int Get_Size();                // Get the size of the table
    void PrintTable();             // Print the entire table
    void PrintChain(int key);      // Print a specific chain
    HashTable();                   // Constructor for the HashTable class
};

// HashTable constructor initializes table to NULL and size to 0
HashTable::HashTable() {
    table = NULL;
    size = 0;
}

// Create the hash table with a given divisor
void HashTable::CreateTable(int divisor) {
    size = divisor;
    table = new Node[size];

    // Initialize all cells with SID = -1 to indicate empty cells.
    for (int i = 0; i < size; i++) {
        table[i].Set_key(-1);
        table[i].Set_index(-1);
    }
}

// Hash function to determine the index for a given key
int HashTable::hash(int key) {
    return key % size;
}

// Add an element to the hash table
void HashTable::Add(Node temp) {
    int key = temp.Get_key();
    int index = hash(key);

    // Check if the cell is empty
    if (table[index].Get_key() == -1) {
        table[index] = temp;
        table[index].Set_index(-1);
        return;
    }
    // Handle collision by finding the last node in the chain
    int current = index;
    while (table[current].Get_index() != -1) {
        current = table[current].Get_index();
    }

    // Find the first available empty cell
    int newIndex = -1;
    for (int i = 1; i < size; i++) {
        int newIdx = (current + i) % size;
        if (table[newIdx].Get_key() == -1) {
            newIndex = newIdx;
            break;
        }
    }

    if (newIndex != -1) {
        table[current].Set_index(newIndex);
        table[newIndex] = temp;
        table[newIndex].Set_index(-1);
    }
    else {
        // If no empty cell is found, the table is full and needs resizing
        resizeAndRehash();
        Add(temp);
    }
}

// Resize the table and rehash its elements
void HashTable::resizeAndRehash() {
    int new_size = 2 * size;
    Node* new_table = new Node[new_size];

    // Initialize the new table as before
    for (int i = 0; i < new_size; i++) {
        new_table[i].Set_key(-1);
        new_table[i].Set_index(-1);
    }

    // Copy existing elements to the new table without rehashing
    for (int i = 0; i < size; i++) {
        new_table[i].Set_key(table[i].Get_key());
        new_table[i].Set_index(table[i].Get_index());
    }

    delete[] table; // Free the old table
    table = new_table;
    size = new_size;
}

// Search for a key in the table and return its index
int HashTable::Search(int key) {
    int index = hash(key);

    while (index != -1) {
        if (table[index].Get_key() == key) {
            return index;
        }
        index = table[index].Get_index();
    }

    return -1;
}

// Remove an element with a given key from the table
void HashTable::Remove(int key) {
    int index = hash(key);

    if (table[index].Get_key() == key) {
        // If the key to be removed is at the beginning of the chain
        int next = table[index].Get_index();
        if (next != -1) {
            table[index] = table[next];
            table[next].Set_index(-1);
        }
        else {
            table[index].Set_key(-1);
        }
    }
    else {
        int prev = index;
        int current = table[index].Get_index();
        while (current != -1) {
            if (table[current].Get_key() == key) {
                table[prev].Set_index(table[current].Get_index());
                table[current].Set_index(-1);
                break;
            }
            prev = current;
            current = table[current].Get_index();
        }
    }
}

// Get the size of the table
int HashTable::Get_Size() {
    return size;
}

// Print the entire hash table
void HashTable::PrintTable() {
    for (int i = 0; i < size; i++) {
        cout << table[i].Get_key() << '\n';
    }
}

// Print a specific chain of nodes starting with the given key
void HashTable::PrintChain(int key) {
    int temp = hash(key);
    while (temp != -1) {
        cout << table[temp].Get_key() << '\n';
        temp = table[temp].Get_index();
    }
}

// Main function
int main() {
    int mode, temp;
    // Initialize keys and divisor
    int key;
    int key_chain;
    int divisor;
    Node Student;
    HashTable x;

    // Read input values
    cin >> mode >> key >> key_chain >> divisor;

    // Create the hash table
    x.CreateTable(divisor);

    // Add elements to the table
    while (cin >> temp) {
        Student.Set_key(temp);
        x.Add(Student);
    }

    // Perform operations based on the selected mode
    if (mode == 0) {
        // Test the "Add" function and resizing and rehashing
        x.PrintTable();
    }
    else if (mode == 1) {
        // Test if the chains are correct
        x.PrintChain(key_chain);
    }
    else if (mode == 2) {
        // Test the "Search" function
        cout << x.Search(key);
    }
    else if (mode == 3) {
        // Test the "Remove" function and print the updated table and chain
        x.Remove(key);
        x.PrintTable();
        x.PrintChain(key);
    }
    return 0;
}
