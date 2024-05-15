#pragma once

#include "../header.h"


class CarTree {
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

public:
    CarTree();
    ~CarTree();
    void deleteTree(CarTree::Node *cur);
    static void render(QGraphicsScene *scene, Node *root);
    void delAllTree();
    void clickDelete(Node *cur, int64_t x, int64_t y);
    Node *contains(int64_t k);
    void insert(CarTree::Node*& t, CarTree::Node* it);
    void insert(int64_t key, int64_t prior);
    void split(CarTree::Node* t, int key, CarTree::Node* &lhs, CarTree::Node*& rhs);
    void merge(CarTree::Node*& t, CarTree::Node* left, CarTree::Node* right);
    void remove(Node*& t, int64_t key);
    Node *getRoot();
    void deleteNode(int64_t data);
};

