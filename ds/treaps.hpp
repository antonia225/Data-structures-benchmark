#pragma once
#include <iostream>
#include <random>
#include <memory>
#include <vector>
using namespace std;

mt19937 rng(random_device{}());

struct Treap
{
    long long key, priority;
    shared_ptr<Treap> left, right;
    Treap(long long k) : key(k), priority(rng()), left(nullptr), right(nullptr) {}
};

using ptr_Treap = shared_ptr<Treap>;

// Split treap into two treaps
// l contains all elements < key
// r contains all elements >= key
void split(ptr_Treap t, long long key, ptr_Treap &l, ptr_Treap &r)
{
    if (!t)
        l = r = nullptr;

    else if (key < t->key)
    {
        split(t->left, key, l, t->left);
        r = t;
    }
    else
    {
        split(t->right, key, t->right, r);
        l = t;
    }
}

// Merge two treaps assuming both are already sorted
// and that there are no duplicate elements
// Merge two treaps: l contains < r, r contains >= l
ptr_Treap merge(ptr_Treap l, ptr_Treap r)
{
    if (!l || !r)
        return l ? l : r;

    if (l->priority > r->priority)
    {
        l->right = merge(l->right, r);
        return l;
    }

    else
    {
        r->left = merge(l, r->left);
        return r;
    }
}

// Check if an element exists in the treap
// Returns true if key exists in the treap, false otherwise
bool find(ptr_Treap t, long long key)
{
    while (t)
    {
        if (t->key == key)
            return true;
        t = (key < t->key) ? t->left : t->right;
    }
    return false;
}

// Insert an element into the treap
// Returns the resulting treap
// If the element already exists, no duplicate will be added
// and the treap will remain unchanged
ptr_Treap insert(ptr_Treap t, long long number)
{
    ptr_Treap item = make_shared<Treap>(number);

    if (!t)
        return item;

    if (item->priority > t->priority)
    {
        split(t, item->key, item->left, item->right);
        return item;
    }
    else if (item->key < t->key)
        t->left = insert(t->left, number);

    else if (item->key > t->key)
        t->right = insert(t->right, number);

    return t;
}

// Delete an element from the treap
// Returns the resulting treap
// If the element does not exist, the treap will remain unchanged
ptr_Treap erase(ptr_Treap t, long long key)
{
    if (!t)
        return nullptr;

    // If the key equals the current key, remove the node
    // and merge the left and right subtrees
    if (t->key == key)
        return merge(t->left, t->right);

    else if (key < t->key)
        t->left = erase(t->left, key);

    else
        t->right = erase(t->right, key);

    return t;
}

// Returns the largest element in the treap with value <= key
long long floor(ptr_Treap t, long long key)
{
    long long res = LONG_MIN;
    while (t)
        if (t->key <= key)
        {
            res = t->key;
            t = t->right;
        }
        else
            t = t->left;

    return res;
}

// Returns the smallest element in the treap with value >= key
long long ceil(ptr_Treap t, long long key)
{
    long long res = -1;
    while (t)
        if (t->key >= key)
        {
            res = t->key;
            t = t->left;
        }
        else
            t = t->right;

    return res;
}

// Returns all elements in the treap in the range [x, y]
// Appends elements to the output vector out
void range(ptr_Treap t, long long x, long long y, vector<long long> &out)
{
    if (!t)
        return;

    // left
    if (x < t->key)
        range(t->left, x, y, out);

    // current node
    if (x <= t->key && t->key <= y)
        out.push_back(t->key);

    // right
    if (t->key < y)
        range(t->right, x, y, out);
}

// Union of two treaps
ptr_Treap reunion(ptr_Treap a, ptr_Treap b)
{
    if (!a || !b)
        return a ? a : b;

    if (a->priority < b->priority)
        swap(a, b);

    b = erase(b, a->key);

    ptr_Treap l, r;
    split(b, a->key, l, r);

    a->left = reunion(a->left, l);
    a->right = reunion(a->right, r);
    return a;
}

// Returns the number of nodes in the treap
int size(ptr_Treap t)
{
    if (!t)
        return 0;

    return 1 + size(t->left) + size(t->right);
}

ptr_Treap generare_random_treap(int nr_numere)
{
    ptr_Treap treap = nullptr;
    for (int i = 0; i < nr_numere; i++)
        treap = insert(treap, rng());

    return treap;
}
