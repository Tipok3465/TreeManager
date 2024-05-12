#pragma once

#include "../header.h"


class Treap {
public:
    struct Node {
        int64_t value;
        int64_t priority;
        Node *parent = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
        int x, y;

        void setPos(int64_t x, int64_t y);
    };

private:
    Node *root;
    Node *find(Node *node, int64_t key);
    void moveUp(Node *x);

public:
    Treap();
    static void render(QGraphicsScene *scene, Node *root);
    void clickDelete(Node *cur, int64_t x, int64_t y);
    Node *contains(int64_t k);
//    static Node *minimum(Node *node);
//    static Node *maximum(Node *node);
    void insert(Treap::Node*& t, Treap::Node* it);
    void insert(int64_t key, int64_t prior);
    void split(Treap::Node* t, int key, Treap::Node* &lhs, Treap::Node*& rhs);
    void merge(Treap::Node*& t, Treap::Node* left, Treap::Node* right);
    void remove(Node*& t, int key);
    Node *getRoot();
    void deleteNode(int64_t data);
};

