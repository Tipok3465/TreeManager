#pragma once

#include "../header.h"


class RBTree {
public:
    enum Color { RED, BLACK };
    struct Node {
        int64_t value;
        Color color;
        Node *left;
        Node *right;
        Node *parent;
        int x, y;
        void setPos(int x, int y);

    };

private:
    Node *root;
    Node* find(Node *node, int64_t key);
    void fixDelete(Node *x);
    void rbTransplant(Node *u, Node *v);
    void remove(Node *node, int64_t key);
    void fixInsert(Node *k);
    static void drawTree(Node *x, QGraphicsScene *&scene);

public:
    RBTree();
    ~RBTree();
    void deleteTree(Node* cur);
    Node* contains(int64_t k);
    void clickDelete(Node *cur, int x, int y);
    static void render(QGraphicsScene *scene, Node *_root);
    void delAllTree();
    Node *maximum(Node *node);
    void leftRotate(Node *x);
    void rightRotate(Node *x);
    void insert(int64_t key);
    Node *getRoot();
    void deleteNode(int64_t data);

};
