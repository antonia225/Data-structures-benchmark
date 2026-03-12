#pragma once
#include <random>
#include <vector>
#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;

template <typename T>
struct Node
{
    T value;
    int level;
    vector<Node *> next;

    Node(T value, int level = 0)
        : value(value), level(level), next(level + 1, nullptr) {}
};

template <typename T>
struct SkipList
{
    Node<T> *head;
    Node<T> *tail;
    short int max_level;
    mt19937 rng;
    uniform_int_distribution<int> random;

    SkipList()
    {
        head = new Node<T>(numeric_limits<T>::lowest());
        tail = new Node<T>(numeric_limits<T>::max());
        head->next[0] = tail;
        max_level = 0;
    }

    short int random_level()
    {
        mt19937 rng(random_device{}());
        uniform_int_distribution<int> random(0, 1);
        short int level = 0;
        while (random(rng) % 2 && level < max_level + 1)
        {
            level++;
        }
        return level;
    }

    void insert(T value)
    {
        if (search(value) != nullptr)
        {
            return;
        }
        short int node_level = random_level();
        if (node_level > max_level)
        {
            max_level = node_level;
            head->next.resize(node_level + 1, tail);
            tail->next.resize(node_level + 1, nullptr);
        }
        vector<Node<T>*> update(max_level + 2);
        Node<T> *current = head;
        for (short int i = max_level; i >= 0; i--)
        {
            while (current->next[i] != nullptr && current->next[i]->value <= value)
            {
                current = current->next[i];
            }
            update[i] = current;
        }

        Node<T> *new_node = new Node<T>(value, node_level);

        for (short int i = 0; i <= node_level; i++)
        {
            new_node->next[i] = update[i]->next[i];
            update[i]->next[i] = new_node;
        }
    }

    void delete_value(T value)
    {
        vector<Node<T>*> update(max_level + 1);
        Node<T> *current = head;

        for (short int i = max_level; i >= 0; i--)
        {
            while (current->next[i] != nullptr && current->next[i]->value < value)
            {
                current = current->next[i];
            }
            update[i] = current;
        }
        current = current->next[0];
        if (current != nullptr && current->value == value)
        {
            for (short int i = 0; i <= max_level; i++)
            {
                if (update[i]->next[i] != current)
                    break;
                update[i]->next[i] = current->next[i];
            }
            delete current;
        }
    }

    Node<T> *search(T value)
    {
        Node<T> *current = head;

        for (short int i = max_level; i >= 0; i--)
        {
            while (current->next[i] != nullptr && current->next[i]->value <= value)
            {
                if (current->next[i]->value == value)
                    return current->next[i];
                current = current->next[i];
            }
        }
        return nullptr;
    }

    T lowest_greater_than(T x)
    {
        Node<T> *current = head;
        for (short int i = max_level; i >= 0; i--)
        {
            while (current->next[i] != nullptr && current->next[i]->value <= x)
            {
                if (current->next[i]->value == x)
                    if (current->next[i]->next[0] != tail)
                        return current->next[i]->next[0]->value;
                current = current->next[i];
            }
        }
        if (current->next[0]->value > x && current->next[0] != tail)
            return current->next[0]->value;
        // value if it does not find a greater value
        return head->value;
    }

    T largest_lower_by(T x)
    {
        Node<T> *current = head;
        for (short int i = max_level; i >= 0; i--)
        {
            while (current->next[i] != nullptr && current->next[i]->value < x)
                current = current->next[i];
        }
        if (current != head)
            return current->value;
        // value if it does not find a lower value
        return head->value;
    }

    vector<T> Interval(T x, T y)
    {
        Node<T> *current = head;
        vector<T> interval;
        for (short int i = max_level; i >= 0; i--)
        {
            while (current->next[i] != nullptr && current->next[i]->value < x)
                current = current->next[i];
        }
        current = current->next[0];
        while (current->value <= y)
        {
            interval.push_back(current->value);
            current = current->next[0];
        }
        return interval;
    }

    T search_delete_max_element()
    {
        Node<T> *current = head;
        vector<Node<T>*> update(max_level + 1);
        for (short int i = max_level; i >= 0; i--)
        {
            while (current->next[i] != nullptr && current->next[i]->next[i] != nullptr && current->next[i]->next[i] != tail)
                current = current->next[i];
            update[i] = current;
        }
        if (current->next[0] != tail)
        {
            current = current->next[0];
            T val = current->value;
            for (short int i = 0; i <= current->level; i++)
            {
                update[i]->next[i] = current->next[i];
            }
            delete current;
            return val;
        }
        else
        {
            return head->value;
        }
    }

    SkipList<T> union_list(const SkipList<T> &other) const
    {
        SkipList<T> result;

        Node<T> *current1 = this->head->next[0];
        Node<T> *current2 = other.head->next[0];
        Node<T> *current3 = result.head;

        while (current1 != this->tail || current2 != other.tail)
        {
            short int level = result.random_level();
            if (level > result.max_level)
            {
                result.max_level = level;
                result.head->next.resize(level + 1, result.tail);
                result.tail->next.resize(level + 1, nullptr);
            }
            if (current1->value < current2->value && current1 != this->tail)
            {
                Node<T> *next_node = new Node<T>(current1->value, level);
                current3->next[0] = next_node;
                current3 = next_node;
                current1 = current1->next[0];
            }
            else if (current1->value == current2->value && current1 != this->tail && current2 != other.tail)
            {
                Node<T> *next_node = new Node<T>(current2->value, level);
                current3->next[0] = next_node;
                current3 = next_node;
                current1 = current1->next[0];
                current2 = current2->next[0];
            }
            else if (current2 != other.tail)
            {
                Node<T> *next_node = new Node<T>(current2->value, level);
                current3->next[0] = next_node;
                current3 = next_node;
                current2 = current2->next[0];
            }
        }
        current3->next[0] = result.tail;
        for (int i = 1; i <= result.max_level; i++)
        {
            Node<T> *current = result.head;
            Node<T> *update = current;
            while (update != result.tail)
            {
                update = update->next[i - 1];
                if (update->level >= i)
                {
                    current->next[i] = update;
                    current = update;
                }
            }
            current->next[i] = result.tail;
        }
        return result;
    }

    /// functie care afiseaza skip-listul
    void print_list()
    {
        for (int i = 0; i <= max_level; i++)
        {
            cout << "Level " << i << " ";
            Node<T> *current = head->next[i];
            while (current != tail)
            {
                cout << current->value << " ";
                current = current->next[i];
            }
            cout << endl;
        }
    }

    SkipList<T> generare_random_skiplist(int nr_numere)
    {
        SkipList<T> skiplist;
        for (int i = 0; i < nr_numere; i++)
        {
            T value = static_cast<T>(rng()); // Generare numar aleator
            skiplist.insert(value);
        }
        return skiplist;
    }

    // functie care returneaza numarul de elemente din skip-list
    int size() const
    {
        int count = 0;
        Node<T> *current = head->next[0];
        while (current)
        {
            ++count;
            current = current->next[0];
        }
        return count;
    }
};
