#pragma once
#include <iostream>
#include <cstdlib>
#include <random>
#include <climits>
using namespace std;

enum RBColor
{
    RED,
    BLACK
};

class RBNode
{
public:
    long long data;
    RBColor color;
    RBNode *left;
    RBNode *right;
    RBNode *parent;
    RBNode(long long data)
        : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class Tree
{
public:
    RBNode *root;

    Tree() : root(nullptr) {}

    ~Tree()
    {
        deleteSubtree(root);
    }

    void deleteSubtree(RBNode *&node)
    {
        if (!node)
            return;
        deleteSubtree(node->left);
        deleteSubtree(node->right);
        delete node;
        node = nullptr;
    }

    void leftRotate(RBNode *x)
    {
        RBNode *y = x->right;
        x->right = y->left;
        if (y->left)
            y->left->parent = x;

        y->parent = x->parent;

        if (!x->parent)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(RBNode *x)
    {
        RBNode *y = x->left;
        x->left = y->right;
        if (y->right)
            y->right->parent = x;

        y->parent = x->parent;

        if (!x->parent)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    void insert(long long data)
    {
        RBNode *newRBNode = new RBNode(data);
        RBNode *y = nullptr;
        RBNode *x = root;

        while (x)
        {
            y = x;
            if (newRBNode->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        newRBNode->parent = y;

        if (!y)
            root = newRBNode;
        else if (newRBNode->data < y->data)
            y->left = newRBNode;
        else
            y->right = newRBNode;

        insertFix(newRBNode);
    }

    void insertFix(RBNode *z)
    {
        while (z->parent && z->parent->color == RED)
        {
            RBNode *grand = z->parent->parent;
            if (!grand)
                break; // safety check

            if (z->parent == grand->left)
            {
                RBNode *y = grand->right;
                if (y && y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    grand->color = RED;
                    z = grand;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    grand->color = RED;
                    rightRotate(grand);
                }
            }
            else
            {
                RBNode *y = grand->left;
                if (y && y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    grand->color = RED;
                    z = grand;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    grand->color = RED;
                    leftRotate(grand);
                }
            }
        }
        root->color = BLACK;
    }

    void deleteRBNode(long long data)
    {
        RBNode *z = searchHelper(root, data);
        if (!z)
            return;

        RBNode *y = z;
        RBNode *x;
        RBColor yOriginalColor = y->color;

        if (!z->left)
        {
            x = z->right;
            transplant(z, z->right);
        }
        else if (!z->right)
        {
            x = z->left;
            transplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z)
            {
                if (x)
                    x->parent = y;
            }
            else
            {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right)
                    y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            if (y->left)
                y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (yOriginalColor == BLACK)
            deleteFixUp(x);
    }

    void deleteFixUp(RBNode *x)
    {
        while (x != root && (!x || x->color == BLACK))
        {
            RBNode *w;
            if (x && x->parent && x == x->parent->left)
            {
                w = x->parent->right;
                if (w && w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if ((!w->left || w->left->color == BLACK) &&
                    (!w->right || w->right->color == BLACK))
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (!w->right || w->right->color == BLACK)
                    {
                        if (w->left)
                            w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->right)
                        w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else if (x && x->parent && x == x->parent->right)
            {
                w = x->parent->left;
                if (w && w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if ((!w->right || w->right->color == BLACK) &&
                    (!w->left || w->left->color == BLACK))
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (!w->left || w->left->color == BLACK)
                    {
                        if (w->right)
                            w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->left)
                        w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        if (x)
            x->color = BLACK;
    }

    void transplant(RBNode *u, RBNode *v)
    {
        if (!u->parent)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v)
            v->parent = u->parent;
    }

    RBNode *minimum(RBNode *RBNode)
    {
        while (RBNode->left)
            RBNode = RBNode->left;
        return RBNode;
    }

    void inorder(RBNode *RBNode)
    {
        if (!RBNode)
            return;
        inorder(RBNode->left);
        cout << RBNode->data << "(" << (RBNode->color == RED ? "R" : "B") << ") ";
        inorder(RBNode->right);
    }

    void display()
    {
        inorder(root);
        cout << '\n';
    }

    bool search(long long value)
    {
        return searchHelper(root, value) != nullptr;
    }

    RBNode *searchHelper(RBNode *RBNode, long long value)
    {
        if (!RBNode || RBNode->data == value)
            return RBNode;
        if (value < RBNode->data)
            return searchHelper(RBNode->left, value);
        else
            return searchHelper(RBNode->right, value);
    }

    long long predecessor(long long x)
    {
        RBNode *current = root;
        long long result = -1;
        while (current)
        {
            if (current->data == x)
                return x;
            if (current->data < x)
            {
                result = current->data;
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
        return result;
    }

    long long successor(long long x)
    {
        RBNode *current = root;
        long long result = -1;
        while (current)
        {
            if (current->data == x)
                return x;
            if (current->data > x)
            {
                result = current->data;
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        return result;
    }

    void rangeQuery(long long X, long long Y, vector<long long> &result)
    {
        rangeHelper(root, X, Y, result);
    }

    void rangeHelper(RBNode *RBNode, long long X, long long Y, vector<long long> &result)
    {
        if (!RBNode)
            return;
        if (X < RBNode->data)
            rangeHelper(RBNode->left, X, Y, result);
        if (X <= RBNode->data && RBNode->data <= Y)
            result.push_back(RBNode->data);
        if (RBNode->data < Y)
            rangeHelper(RBNode->right, X, Y, result);
    }

    void unionWith(Tree &other)
    {
        collectAndInsert(other.root);
    }

    void collectAndInsert(RBNode *RBNode)
    {
        if (!RBNode)
            return;
        collectAndInsert(RBNode->left);
        if (!this->search(RBNode->data))
            this->insert(RBNode->data);
        collectAndInsert(RBNode->right);
    }

    void generateRandomRBTree(long long nr_numere)
    {
        mt19937 rng(random_device{}());
        uniform_int_distribution<long long> dist(LONG_MIN, LONG_MAX);
        for (long long i = 0; i < nr_numere; ++i)
        {
            insert(dist(rng));
        }
    }

    // functie care returneaza numarul de elemente din arbore
    int countNodes() const
    {
        return countNodesHelper(root);
    }

    int countNodesHelper(RBNode *node) const
    {
        if (!node)
            return 0;
        return 1 + countNodesHelper(node->left) + countNodesHelper(node->right);
    }
};
