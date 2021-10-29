#include <iostream>
#include <vector>
#include <cmath>

unsigned int INT_MAX_2 = 4294967294;

using namespace std;

struct Node {
    unsigned int value;
    int key;
    Node* next;
};

bool push_back(Node** head, unsigned int value, int key)
{
    if (*head == NULL) {
        *head = new Node;
        (*head)->value = value;
        (*head)->key = key;
        (*head)->next = NULL;
        return false;
    }

    Node* p_node = *head;
    while (p_node->next != NULL) {
        if (p_node->key == key)
        {
            break;
        }
        p_node = p_node->next;
    }

    if (p_node->key == key)
    {
        p_node->value = value;
        return true;
    }

    Node* new_node = new Node;
    p_node->next = new_node;
    new_node->value = value;
    new_node->key = key;
    new_node->next = NULL;
    return false;
}

unsigned int list_pop(Node** head, int key) {
    Node* p_node = *head;
    Node* tmp = *head;
    if (!*head)
    {
        return INT_MAX_2;
    }

    while (p_node->key != key)
    {
        if (p_node->next == NULL) return INT_MAX_2;
        tmp = p_node;
        p_node = p_node->next;
    }
    unsigned int val;
    if (p_node == *head) {
        val = p_node->value;
        tmp = p_node;
        *head = tmp->next;
        delete p_node;
        return val;
    }

    tmp->next = p_node->next;
    val = p_node->value;
    delete p_node;
    return val;
}

unsigned int list_get(Node* head, int key) {
    Node* p_node = head;
    Node* tmp = head;

    if (head == NULL) return INT_MAX_2;

    while (p_node->key != key)
    {
        if (p_node->next == NULL) return INT_MAX_2;
        tmp = p_node;
        p_node = p_node->next;
    }
    return p_node->value;
}

void clear_list(Node** head) {
    if (*head == NULL) return;

    Node* old_node = *head;
    Node* new_node = (*head)->next;

    while (new_node != NULL)
    {
        delete old_node;
        old_node = new_node;
        new_node = old_node->next;
    }

    delete old_node;
    *head = NULL;
}

unsigned int h(unsigned int size, int index) {
    return (index > 0 ? index : -index) % size;
}

struct HashTable
{
    HashTable() : HashTable{64}
    {}

    HashTable(int size) : size(size)
    {
        table = new Node * [size];
        for (size_t i = 0; i < size; i++)
        {
            table[i] = NULL;
        }
        num = 0;
    }

    ~HashTable()
    {
        for (size_t i = 0; i < size; i++)
        {
            clear_list(&table[i]);
        }
        delete[] table;
    }

    void add(int key, unsigned int value) {
        unsigned int hash;
        hash = h(size, key);
        bool f = push_back(&table[hash], value, key);
        if (!f) num++;
        check_reallocate();
    }

    unsigned int pop(int key) {
        unsigned int hash;
        unsigned int res;
        hash = h(size, key);
        res = list_pop(&table[hash], key);
        if (res != INT_MAX_2)
        {
            num--;
        }
        return res;
    }

    unsigned int get(int key) {
        unsigned int hash;
        hash = h(size, key);
        return list_get(table[hash], key);
    }

    void check_reallocate() {
        if ((double)num / (double)size < 0.5) return;

        size_t new_size = 2 * size;
        Node** new_table = new Node * [new_size];
        for (size_t i = 0; i < new_size; i++)
        {
            new_table[i] = NULL;
        }
        size_t new_h_key = new_size - 1;
        int new_num = 0;

        for (size_t i = 0; i < size; i++)
        {
            while (table[i] != NULL)
            {
                unsigned int new_value;
                int new_key;
                new_key = table[i]->key;
                new_value = this->pop(new_key);

                unsigned int hash;
                hash = h(new_size, new_key);
                push_back(&new_table[hash], new_value, new_key);
                new_num++;
            }
        }

        for (size_t i = 0; i < size; i++)
        {
            clear_list(&table[i]);
        }
        delete[] table;

        size = new_size;
        num = new_num;
        table = new_table;
    }

    size_t size;
    int num;
    Node** table;
};

int main() {
    /*bool f = true;
    for (int size = 2000001; size < 3000000; size += 1000)
    {
        for (int ind = -2000000; ind < 2000000; ind += 1)
        {
            int tmp = h(size, ind);
            if (tmp < 0 or tmp > size - 1)
            {
                f = false;
                break;
            }
            std::cout << size << ' ' << ind << ' ' << tmp << '\n';
            if (f == false) break;
        }
    }*/

    int n;
    std::cin >> n;
    vector<HashTable> f(n);

    int m;
    std::cin >> m;
    for (size_t i = 0; i < m; i++)
    {
        int index;
        char op;
        int key;
        unsigned int value;
        std::cin >> index >> op >> key >> value;
        if (op == '+')
        {
            f[index].add(key, value);
        }
        else if (op == '-')
        {
            f[index].pop(key);
        }
        else if (op == '?')
        {
            unsigned int tmp = f[index].get(key);
            if (tmp != INT_MAX_2)
            {
                std::cout << tmp << '\n';
            }
            else
            {
                cout << value << '\n';
            }
        }
    }
    return 0;
}